//! Database operations for storing game data

use anyhow::Result;
use rusqlite::{Connection, params};
use tracing::info;

/// Initialize the game database schema
pub fn initialize_database(conn: &Connection) -> Result<()> {
    info!("Initializing database schema...");
    
    // Commodity prices table
    conn.execute(
        "CREATE TABLE IF NOT EXISTS commodity_prices (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            commodity_id TEXT NOT NULL,
            port_id TEXT NOT NULL,
            price REAL NOT NULL,
            currency TEXT NOT NULL DEFAULT 'USD',
            unit TEXT NOT NULL,
            last_updated TEXT NOT NULL,
            source TEXT NOT NULL
        )",
        [],
    )?;
    
    // Weather data table
    conn.execute(
        "CREATE TABLE IF NOT EXISTS weather_data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            latitude REAL NOT NULL,
            longitude REAL NOT NULL,
            forecast_time TEXT NOT NULL,
            wind_speed REAL NOT NULL,
            wave_height REAL NOT NULL,
            visibility REAL NOT NULL,
            is_storm INTEGER NOT NULL DEFAULT 0,
            conditions TEXT,
            fetched_at TEXT NOT NULL
        )",
        [],
    )?;
    
    // Port data table
    conn.execute(
        "CREATE TABLE IF NOT EXISTS ports (
            port_id TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            country TEXT,
            latitude REAL NOT NULL,
            longitude REAL NOT NULL,
            max_ship_size INTEGER,
            services TEXT,
            last_updated TEXT
        )",
        [],
    )?;
    
    // Game state table
    conn.execute(
        "CREATE TABLE IF NOT EXISTS game_state (
            key TEXT PRIMARY KEY,
            value TEXT NOT NULL,
            updated_at TEXT NOT NULL
        )",
        [],
    )?;
    
    // Create indices for faster lookups
    conn.execute(
        "CREATE INDEX IF NOT EXISTS idx_commodity_prices_lookup 
         ON commodity_prices(commodity_id, port_id)",
        [],
    )?;
    
    conn.execute(
        "CREATE INDEX IF NOT EXISTS idx_weather_location 
         ON weather_data(latitude, longitude)",
        [],
    )?;
    
    info!("Database schema initialized successfully");
    Ok(())
}

/// Insert or update commodity price
pub fn upsert_commodity_price(
    conn: &Connection,
    commodity_id: &str,
    port_id: &str,
    price: f64,
    currency: &str,
    unit: &str,
    last_updated: &str,
    source: &str,
) -> Result<()> {
    conn.execute(
        "INSERT OR REPLACE INTO commodity_prices 
         (commodity_id, port_id, price, currency, unit, last_updated, source)
         VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7)",
        params![commodity_id, port_id, price, currency, unit, last_updated, source],
    )?;
    
    Ok(())
}

/// Get commodity price for a specific port
pub fn get_commodity_price(
    conn: &Connection,
    commodity_id: &str,
    port_id: &str,
) -> Result<Option<(f64, String, String, String)>> {
    let mut stmt = conn.prepare(
        "SELECT price, currency, unit, last_updated 
         FROM commodity_prices 
         WHERE commodity_id = ?1 AND port_id = ?2"
    )?;
    
    let result = stmt.query_row(params![commodity_id, port_id], |row| {
        Ok((
            row.get::<_, f64>(0)?,
            row.get::<_, String>(1)?,
            row.get::<_, String>(2)?,
            row.get::<_, String>(3)?,
        ))
    });
    
    match result {
        Ok(row) => Ok(Some(row)),
        Err(rusqlite::Error::QueryReturnedNoRows) => Ok(None),
        Err(e) => Err(e.into()),
    }
}

/// Insert weather data
pub fn insert_weather_data(
    conn: &Connection,
    latitude: f64,
    longitude: f64,
    forecast_time: &str,
    wind_speed: f64,
    wave_height: f64,
    visibility: f64,
    is_storm: bool,
    conditions: &str,
) -> Result<()> {
    conn.execute(
        "INSERT INTO weather_data 
         (latitude, longitude, forecast_time, wind_speed, wave_height, visibility, is_storm, conditions, fetched_at)
         VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, datetime('now'))",
        params![latitude, longitude, forecast_time, wind_speed, wave_height, visibility, is_storm as i32, conditions],
    )?;
    
    Ok(())
}

/// Insert port data
pub fn insert_port(
    conn: &Connection,
    port_id: &str,
    name: &str,
    country: &str,
    latitude: f64,
    longitude: f64,
    max_ship_size: i32,
    services: &str,
) -> Result<()> {
    conn.execute(
        "INSERT OR REPLACE INTO ports 
         (port_id, name, country, latitude, longitude, max_ship_size, services, last_updated)
         VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7, datetime('now'))",
        params![port_id, name, country, latitude, longitude, max_ship_size, services],
    )?;
    
    Ok(())
}

/// Save game state
pub fn save_game_state(conn: &Connection, key: &str, value: &str) -> Result<()> {
    conn.execute(
        "INSERT OR REPLACE INTO game_state (key, value, updated_at)
         VALUES (?1, ?2, datetime('now'))",
        params![key, value],
    )?;
    
    Ok(())
}

/// Load game state
pub fn load_game_state(conn: &Connection, key: &str) -> Result<Option<String>> {
    let mut stmt = conn.prepare("SELECT value FROM game_state WHERE key = ?1")?;
    
    let result = stmt.query_row(params![key], |row| {
        row.get::<_, String>(0)
    });
    
    match result {
        Ok(value) => Ok(Some(value)),
        Err(rusqlite::Error::QueryReturnedNoRows) => Ok(None),
        Err(e) => Err(e.into()),
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use rusqlite::Connection;
    
    #[test]
    fn test_initialize_database() {
        let conn = Connection::open_in_memory().unwrap();
        initialize_database(&conn).unwrap();
        
        // Verify tables exist
        let mut stmt = conn.prepare("SELECT name FROM sqlite_master WHERE type='table'").unwrap();
        let tables: Vec<String> = stmt.query_map([], |row| row.get(0)).unwrap()
            .filter_map(|r| r.ok()).collect();
        
        assert!(tables.contains(&"commodity_prices".to_string()));
        assert!(tables.contains(&"weather_data".to_string()));
        assert!(tables.contains(&"ports".to_string()));
        assert!(tables.contains(&"game_state".to_string()));
    }
}
