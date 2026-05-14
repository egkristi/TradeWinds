//! Port data fetching and management

use anyhow::Result;
use serde::{Deserialize, Serialize};
use tracing::info;
use std::path::Path;
use tokio::fs;

/// Port information
#[derive(Debug, Deserialize, Serialize, Clone)]
pub struct PortData {
    pub port_id: String,
    pub name: String,
    pub country: String,
    pub latitude: f64,
    pub longitude: f64,
    pub max_ship_size: i32,
    pub services: Vec<String>,
    pub facilities: Vec<String>,
}

/// Build port data from various sources
pub async fn fetch_port_data(output_dir: &str) -> Result<()> {
    let output_path = Path::new(output_dir);
    fs::create_dir_all(output_path).await?;
    
    info!("Building port database...");
    
    // Sample ports - in production, this would fetch from UN/LOCODE or similar
    let ports = vec![
        PortData {
            port_id: "OSLO".to_string(),
            name: "Oslo".to_string(),
            country: "Norway".to_string(),
            latitude: 59.9139,
            longitude: 10.7522,
            max_ship_size: 50000,
            services: vec!["Refuel".to_string(), "Repair".to_string(), "Shipyard".to_string()],
            facilities: vec!["Container Terminal".to_string(), "Bulk Cargo".to_string()],
        },
        PortData {
            port_id: "ROTTERDAM".to_string(),
            name: "Rotterdam".to_string(),
            country: "Netherlands".to_string(),
            latitude: 51.9225,
            longitude: 4.47917,
            max_ship_size: 400000,
            services: vec!["Refuel".to_string(), "Repair".to_string(), "Shipyard".to_string(), "Dry Dock".to_string()],
            facilities: vec!["Container Terminal".to_string(), "Bulk Cargo".to_string(), "Oil Terminal".to_string()],
        },
        PortData {
            port_id: "SINGAPORE".to_string(),
            name: "Singapore".to_string(),
            country: "Singapore".to_string(),
            latitude: 1.2644,
            longitude: 103.8220,
            max_ship_size: 400000,
            services: vec!["Refuel".to_string(), "Repair".to_string(), "Shipyard".to_string()],
            facilities: vec!["Container Terminal".to_string(), "Transshipment".to_string()],
        },
        PortData {
            port_id: "SHANGHAI".to_string(),
            name: "Shanghai".to_string(),
            country: "China".to_string(),
            latitude: 31.2304,
            longitude: 121.4737,
            max_ship_size: 400000,
            services: vec!["Refuel".to_string(), "Repair".to_string()],
            facilities: vec!["Container Terminal".to_string(), "Bulk Cargo".to_string()],
        },
    ];
    
    // Save to JSON
    let json_data = serde_json::to_string_pretty(&ports)?;
    let file_path = output_path.join("ports.json");
    fs::write(&file_path, json_data).await?;
    
    info!("Saved {} ports to {:?}", ports.len(), file_path);
    info!("Port data fetching complete");
    
    Ok(())
}

/// Load port data from file
pub fn load_port_data(file_path: &str) -> Result<Vec<PortData>> {
    let data = std::fs::read_to_string(file_path)?;
    let ports: Vec<PortData> = serde_json::from_str(&data)?;
    Ok(ports)
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_port_data_serialization() {
        let port = PortData {
            port_id: "TEST".to_string(),
            name: "Test Port".to_string(),
            country: "Testland".to_string(),
            latitude: 50.0,
            longitude: 10.0,
            max_ship_size: 10000,
            services: vec!["Refuel".to_string()],
            facilities: vec![],
        };
        
        let json = serde_json::to_string(&port).unwrap();
        let deserialized: PortData = serde_json::from_str(&json).unwrap();
        
        assert_eq!(deserialized.port_id, "TEST");
        assert_eq!(deserialized.name, "Test Port");
    }
}
