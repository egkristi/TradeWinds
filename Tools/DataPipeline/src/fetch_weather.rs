//! Weather data fetching from Open-Meteo

use anyhow::Result;
use reqwest::Client;
use serde::{Deserialize, Serialize};
use tracing::{info, warn};
use std::path::Path;
use tokio::fs;

/// Open-Meteo marine weather response
#[derive(Debug, Deserialize, Serialize)]
pub struct OpenMeteoResponse {
    pub latitude: f64,
    pub longitude: f64,
    pub generationtime_ms: f64,
    pub utc_offset_seconds: i32,
    pub timezone: String,
    pub timezone_abbreviation: String,
    pub hourly: HourlyData,
}

#[derive(Debug, Deserialize, Serialize)]
pub struct HourlyData {
    pub time: Vec<String>,
    pub wave_height: Vec<f64>,
    pub wave_period: Vec<f64>,
    pub wave_direction: Vec<f64>,
    pub wind_speed_10m: Vec<f64>,
    pub wind_direction_10m: Vec<f64>,
    pub temperature_2m: Vec<f64>,
    pub visibility: Option<Vec<f64>>,
}

/// Major port coordinates for weather fetching
pub const MAJOR_PORTS: &[(&str, f64, f64)] = &[
    ("ROTTERDAM", 51.9225, 4.47917),
    ("SINGAPORE", 1.2644, 103.8220),
    ("SHANGHAI", 31.2304, 121.4737),
    ("LOS_ANGELES", 33.7405, -118.2720),
    ("HAMBURG", 53.5511, 9.9937),
    ("ANTWERP", 51.2194, 4.4025),
    ("DUBAI", 25.2048, 55.2708),
    ("OSLO", 59.9139, 10.7522),
];

/// Fetch weather data for major ports
pub async fn fetch_weather_data(output_dir: &str) -> Result<()> {
    let client = Client::new();
    let output_path = Path::new(output_dir);
    fs::create_dir_all(output_path).await?;
    
    info!("Fetching weather data for {} major ports", MAJOR_PORTS.len());
    
    for (port_name, lat, lon) in MAJOR_PORTS {
        info!("Fetching weather for {} ({}, {})", port_name, lat, lon);
        
        let url = format!(
            "https://marine-api.open-meteo.com/v1/marine?latitude={}&longitude={}&hourly=wave_height,wave_period,wave_direction,wind_speed_10m,wind_direction_10m,temperature_2m&forecast_days=7",
            lat, lon
        );
        
        match client.get(&url).send().await {
            Ok(response) => {
                if response.status().is_success() {
                    let data = response.text().await?;
                    
                    let file_path = output_path.join(format!("{}_weather.json", port_name.to_lowercase()));
                    fs::write(&file_path, data).await?;
                    
                    info!("Saved {} weather to {:?}", port_name, file_path);
                } else {
                    warn!("Failed to fetch {} weather: HTTP {}", port_name, response.status());
                }
            }
            Err(e) => {
                warn!("Error fetching {} weather: {}", port_name, e);
            }
        }
        
        // Rate limiting
        tokio::time::sleep(tokio::time::Duration::from_millis(300)).await;
    }
    
    info!("Weather data fetching complete");
    Ok(())
}

/// Parse Open-Meteo response
pub fn parse_openmeteo_response(data: &str) -> Result<OpenMeteoResponse> {
    let response: OpenMeteoResponse = serde_json::from_str(data)?;
    Ok(response)
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_parse_openmeteo_response() {
        let sample_data = r#"{
            "latitude": 51.9225,
            "longitude": 4.47917,
            "generationtime_ms": 1.2,
            "utc_offset_seconds": 0,
            "timezone": "GMT",
            "timezone_abbreviation": "GMT",
            "hourly": {
                "time": ["2024-01-01T00:00", "2024-01-01T01:00"],
                "wave_height": [1.5, 1.6],
                "wave_period": [5.0, 5.1],
                "wave_direction": [180.0, 185.0],
                "wind_speed_10m": [10.5, 11.0],
                "wind_direction_10m": [270.0, 275.0],
                "temperature_2m": [15.0, 15.5]
            }
        }"#;
        
        let result = parse_openmeteo_response(sample_data).unwrap();
        assert!((result.latitude - 51.9225).abs() < 0.001);
        assert_eq!(result.hourly.wave_height.len(), 2);
    }
}
