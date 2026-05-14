#!/usr/bin/env python3
"""
Argosy Tides - Quick Data Fetcher Prototype

This is a Python prototype for quickly fetching real-world data.
For production use, see Tools/DataPipeline (Rust implementation).

Usage:
    python fetch_data_prototype.py --commodities
    python fetch_data_prototype.py --weather
    python fetch_data_prototype.py --all
"""

import argparse
import json
import requests
from pathlib import Path
from datetime import datetime

# World Bank commodity API
WORLDBANK_BASE = "https://api.worldbank.org/v2/commodity"

# Open-Meteo marine API
OPENMETEO_BASE = "https://marine-api.open-meteo.com/v1/marine"

# Sample port coordinates
MAJOR_PORTS = {
    "OSLO": (59.9139, 10.7522),
    "ROTTERDAM": (51.9225, 4.47917),
    "SINGAPORE": (1.2644, 103.8220),
    "SHANGHAI": (31.2304, 121.4737),
    "LOS_ANGELES": (33.7405, -118.2720),
}


def fetch_commodity_prices(output_dir: str):
    """Fetch commodity prices from World Bank API"""
    print(f"Fetching commodity prices from World Bank...")
    
    commodities = [
        "CRUDE_BRENT", "CRUDE_WTI", "NATGAS", "COAL",
        "WHEAT", "CORN", "RICE", "SOYBEAN", "SUGAR", "COFFEE"
    ]
    
    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)
    
    for code in commodities:
        try:
            url = f"{WORLDBANK_BASE}/{code}?format=json&per_page=100"
            response = requests.get(url, timeout=10)
            
            if response.status_code == 200:
                data = response.json()
                output_file = output_path / f"{code.lower()}_prices.json"
                
                with open(output_file, 'w') as f:
                    json.dump(data, f, indent=2)
                
                print(f"  ✓ {code}: Saved to {output_file}")
            else:
                print(f"  ✗ {code}: HTTP {response.status_code}")
                
        except Exception as e:
            print(f"  ✗ {code}: {e}")
    
    print("Commodity price fetching complete.\n")


def fetch_weather_data(output_dir: str):
    """Fetch weather data from Open-Meteo"""
    print(f"Fetching weather data from Open-Meteo...")
    
    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)
    
    for port_name, (lat, lon) in MAJOR_PORTS.items():
        try:
            url = (
                f"{OPENMETEO_BASE}?latitude={lat}&longitude={lon}"
                f"&hourly=wave_height,wave_period,wind_speed_10m&forecast_days=7"
            )
            response = requests.get(url, timeout=10)
            
            if response.status_code == 200:
                data = response.json()
                output_file = output_path / f"{port_name.lower()}_weather.json"
                
                with open(output_file, 'w') as f:
                    json.dump(data, f, indent=2)
                
                print(f"  ✓ {port_name}: Saved to {output_file}")
            else:
                print(f"  ✗ {port_name}: HTTP {response.status_code}")
                
        except Exception as e:
            print(f"  ✗ {port_name}: {e}")
    
    print("Weather data fetching complete.\n")


def fetch_all():
    """Fetch all data"""
    output_dir = "output/prototype"
    print("=" * 60)
    print("Argosy Tides - Data Fetcher Prototype")
    print("=" * 60)
    print()
    
    fetch_commodity_prices(output_dir)
    fetch_weather_data(output_dir)
    
    print("All data fetching complete!")
    print(f"Output directory: {output_dir}")


def main():
    parser = argparse.ArgumentParser(
        description="Argosy Tides - Quick Data Fetcher Prototype"
    )
    
    parser.add_argument(
        "--commodities",
        action="store_true",
        help="Fetch commodity prices only"
    )
    
    parser.add_argument(
        "--weather",
        action="store_true",
        help="Fetch weather data only"
    )
    
    parser.add_argument(
        "--all",
        action="store_true",
        help="Fetch all data"
    )
    
    args = parser.parse_args()
    
    if args.commodities:
        fetch_commodity_prices("output/prototype")
    elif args.weather:
        fetch_weather_data("output/prototype")
    elif args.all or True:  # Default to --all
        fetch_all()
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
