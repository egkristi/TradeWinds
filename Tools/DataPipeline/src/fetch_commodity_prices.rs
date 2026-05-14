//! Commodity price fetching from World Bank and other sources

use anyhow::Result;
use reqwest::Client;
use serde::{Deserialize, Serialize};
use tracing::{info, warn};
use std::path::Path;
use tokio::fs;

/// World Bank commodity price response
#[derive(Debug, Deserialize, Serialize)]
pub struct WorldBankResponse {
    pub page: i32,
    pub pages: i32,
    pub per_page: i32,
    pub total: i32,
    pub sourceid: String,
    pub sourcename: String,
    pub data: Vec<CommodityDataPoint>,
}

#[derive(Debug, Deserialize, Serialize, Clone)]
pub struct CommodityDataPoint {
    #[serde(rename = "ref_date")]
    pub ref_date: String,
    
    #[serde(rename = "value")]
    pub value: f64,
    
    #[serde(rename = "unit")]
    pub unit: String,
    
    pub commodity: String,
}

/// Fetch all commodities from World Bank API
pub async fn fetch_all_commodities(output_dir: &str) -> Result<()> {
    let client = Client::new();
    
    // List of World Bank commodity codes
    let commodity_codes = vec![
        "CRUDE_BRENT",    // Crude Oil (Brent)
        "CRUDE_WTI",      // Crude Oil (WTI)
        "NATGAS",         // Natural Gas
        "COAL",           // Coal
        "WHEAT",          // Wheat
        "CORN",           // Corn
        "RICE",           // Rice
        "SOYBEAN",        // Soybeans
        "SUGAR",          // Sugar
        "COFFEE",         // Coffee
        "COTTON",         // Cotton
        "ALUMINUM",       // Aluminum
        "COPPER",         // Copper
        "IRON",           // Iron Ore
        "GOLD",           // Gold
        "SILVER",         // Silver
    ];
    
    let output_path = Path::new(output_dir);
    fs::create_dir_all(output_path).await?;
    
    for code in commodity_codes {
        info!("Fetching commodity: {}", code);
        
        let url = format!(
            "https://api.worldbank.org/v2/commodity/{}?format=json&per_page=100",
            code
        );
        
        match client.get(&url).send().await {
            Ok(response) => {
                if response.status().is_success() {
                    let data = response.text().await?;
                    
                    // Save to file
                    let file_path = output_path.join(format!("{}_prices.json", code.to_lowercase()));
                    fs::write(&file_path, data).await?;
                    
                    info!("Saved {} to {:?}", code, file_path);
                } else {
                    warn!("Failed to fetch {}: HTTP {}", code, response.status());
                }
            }
            Err(e) => {
                warn!("Error fetching {}: {}", code, e);
            }
        }
        
        // Rate limiting - be nice to the API
        tokio::time::sleep(tokio::time::Duration::from_millis(500)).await;
    }
    
    info!("Commodity price fetching complete");
    Ok(())
}

/// Parse World Bank response
pub fn parse_worldbank_response(data: &str) -> Result<Vec<CommodityDataPoint>> {
    let responses: Vec<WorldBankResponse> = serde_json::from_str(data)?;
    
    if responses.len() >= 2 {
        Ok(responses[1].data.clone())
    } else {
        Ok(vec![])
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_parse_worldbank_response() {
        let sample_data = r#"[{"page":1,"pages":1,"per_page":100,"total":10,"sourceid":"1","sourcename":"Commodity Price Data"},{"data":[{"ref_date":"2024-01-01","value":70.5,"unit":"USD","commodity":"CRUDE_BRENT"}]}]"#;
        
        let result = parse_worldbank_response(sample_data).unwrap();
        assert_eq!(result.len(), 1);
        assert_eq!(result[0].commodity, "CRUDE_BRENT");
        assert!((result[0].value - 70.5).abs() < 0.01);
    }
}
