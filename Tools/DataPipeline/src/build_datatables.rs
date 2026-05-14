//! Build all data tables

use anyhow::Result;
use tracing::info;
use crate::fetch_commodity_prices;
use crate::fetch_weather;
use crate::fetch_port_data;

/// Build all data tables
pub async fn build_all(output_dir: &str) -> Result<()> {
    info!("Building all data tables...");
    
    // Fetch commodity prices
    info!("Step 1: Fetching commodity prices");
    fetch_commodity_prices::fetch_all_commodities(output_dir).await?;
    
    // Fetch weather data
    info!("Step 2: Fetching weather data");
    fetch_weather::fetch_weather_data(output_dir).await?;
    
    // Fetch port data
    info!("Step 3: Fetching port data");
    fetch_port_data::fetch_port_data(output_dir).await?;
    
    info!("All data tables built successfully");
    Ok(())
}
