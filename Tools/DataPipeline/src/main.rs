//! Argosy Tides Data Pipeline
//! 
//! Fetches real-world data from various APIs and processes it for game use.
//! 
//! Data sources:
//! - World Bank Commodity Prices
//! - Trading Economics
//! - Open-Meteo Weather
//! - Port data

mod fetch_commodity_prices;
mod fetch_weather;
mod fetch_port_data;
mod build_datatables;
mod update_game_data;
mod db;

use anyhow::Result;
use clap::Parser;
use tracing::{info, error};
use tracing_subscriber::{layer::SubscriberExt, util::SubscriberInitExt};

/// Argosy Tides Data Pipeline CLI
#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// Command to execute
    #[command(subcommand)]
    command: Commands,

    /// Output directory for processed data
    #[arg(short, long, default_value = "output")]
    output_dir: String,

    /// Enable verbose logging
    #[arg(short, long)]
    verbose: bool,
}

#[derive(clap::Subcommand, Debug)]
enum Commands {
    /// Fetch commodity prices from World Bank
    FetchCommodities,
    
    /// Fetch weather data from Open-Meteo
    FetchWeather,
    
    /// Fetch port data
    FetchPorts,
    
    /// Build all data tables
    BuildAll,
    
    /// Update game data in SQLite
    UpdateGame {
        /// Path to game SQLite database
        #[arg(short, long)]
        db_path: String,
    },
}

#[tokio::main]
async fn main() -> Result<()> {
    let args = Args::parse();

    // Initialize logging
    tracing_subscriber::registry()
        .with(
            tracing_subscriber::EnvFilter::try_from_default_env()
                .unwrap_or_else(|_| {
                    if args.verbose {
                        "data_pipeline=debug".into()
                    } else {
                        "data_pipeline=info".into()
                    }
                }),
        )
        .with(tracing_subscriber::fmt::layer())
        .init();

    info!("Starting Argosy Tides Data Pipeline");
    info!("Output directory: {}", args.output_dir);

    match args.command {
        Commands::FetchCommodities => {
            info!("Fetching commodity prices...");
            fetch_commodity_prices::fetch_all_commodities(&args.output_dir).await?;
        }
        
        Commands::FetchWeather => {
            info!("Fetching weather data...");
            fetch_weather::fetch_weather_data(&args.output_dir).await?;
        }
        
        Commands::FetchPorts => {
            info!("Fetching port data...");
            fetch_port_data::fetch_port_data(&args.output_dir).await?;
        }
        
        Commands::BuildAll => {
            info!("Building all data tables...");
            build_datatables::build_all(&args.output_dir).await?;
        }
        
        Commands::UpdateGame { db_path } => {
            info!("Updating game data in {}", db_path);
            update_game_data::update_game_database(&db_path).await?;
        }
    }

    info!("Data pipeline completed successfully");
    Ok(())
}
