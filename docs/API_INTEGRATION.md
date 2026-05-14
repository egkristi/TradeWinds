# TradeWinds — Real-World Data Integration Guide

> **Version:** 1.0  > **Date:** 2026-05-14  
> **Jira:** MUNIN-70  

---

## Overview

TradeWinds uses real-world data to power its economy, weather, and geography. This document describes all data sources, their APIs, update frequencies, and integration strategies.

---

## 1. Commodity Prices

### 1.1 Baltic Exchange (Freight Indices)

**API:** Baltic Exchange API (requires subscription)  
**Data:** Baltic Dry Index (BDI), Baltic Capesize Index (BCI), Baltic Panamax Index (BPI), Baltic Supramax Index (BSI), Baltic Clean Tanker Index (BCTI), Baltic Dirty Tanker Index (BDTI)  
**Update:** Daily (market days)  
**Use:** Freight rates for calculating shipping costs  
**Cost:** $$$ (subscription required)  
**Free Alternative:** No direct free alternative — use World Bank proxies

### 1.2 World Bank Commodity Price Data

**API:** `https://api.worldbank.org/v2/commodity`  
**Data:** 60+ commodities including energy, agriculture, metals, fertilizers  
**Update:** Monthly  
**Use:** Base commodity prices for modern mode  
**Cost:** FREE  
**License:** Creative Commons Attribution 4.0  

**Example request:**
```bash
curl "https://api.worldbank.org/v2/commodity/CRUDE_BRENT?format=json"
```

### 1.3 Trading Economics

**API:** `https://api.tradingeconomics.com/commodities`  
**Data:** Real-time and historical commodity prices  
**Update:** Hourly  
**Use:** Real-time price feeds for modern mode  
**Cost:** FREE tier (100 requests/day) / Paid ($99+/month)  
**Registration:** Required (free API key)

**Example:**
```bash
curl -X GET "https://api.tradingeconomics.com/commodities?c=guest:guest"
```

### 1.4 IMF Primary Commodity Prices

**API:** `https://www.imf.org/external/datamapper/api/v1/PCPS`  
**Data:** Broad basket of commodity prices  
**Update:** Monthly  
**Use:** Historical trends, global averages  
**Cost:** FREE  
**License:** IMF Data Terms of Use

### 1.5 UN Comtrade Database

**API:** `https://comtrade.un.org/api/`  
**Data:** Global trade flows by commodity, country, year  
**Update:** Annual  
**Use:** Trade volume data, port importance ranking  
**Cost:** FREE  
**Registration:** Recommended

---

## 2. Weather Data

### 2.1 Open-Meteo (Primary — Free, No Key)

**API:** `https://api.open-meteo.com/v1/forecast`  
**Data:** Temperature, wind, precipitation, wave height, visibility  
**Update:** Hourly forecasts, 16 days ahead  
**Use:** Route planning, storm avoidance, fuel calculation  
**Cost:** FREE (open data)  
**License:** CC BY 4.0  
**Rate limit:** 10,000 requests/day (generous)

**Example — weather at lat=56.0, lon=10.0 (Baltic Sea):**
```bash
curl "https://api.open-meteo.com/v1/forecast?latitude=56.0&longitude=10.0&hourly=temperature_2m,wind_speed_10m,wind_direction_10m&timezone=auto"
```

**Marine weather:**
```bash
curl "https://marine-api.open-meteo.com/v1/forecast?latitude=56.0&longitude=10.0&hourly=wave_height,wind_wave_direction,wind_wave_height"
```

### 2.2 NOAA Marine Weather

**API:** `https://marine.weather.gov/MapClick.php`  
**Data:** US coastal and offshore marine forecasts  
**Update:** Every 6 hours  
**Use:** North American waters  
**Cost:** FREE  
**License:** Public domain (US government)

### 2.3 ECMWF (European Centre for Medium-Range Weather Forecasts)

**API:** `https://api.ecmwf.int/v1`  
**Data:** Global weather model, best-in-class accuracy  
**Update:** Daily  
**Use:** Global weather, professional-grade  
**Cost:** FREE for non-commercial / academic  
**License:** ECMWF Terms  
**Registration:** Required

### 2.4 Copernicus Marine Service

**API:** `https://marine.copernicus.eu/`  
**Data:** Ocean currents, sea surface temperature, salinity, sea ice  
**Update:** Daily / near real-time  
**Use:** Route optimization, fuel calculation, ice routing  
**Cost:** FREE for research/education / Paid for commercial  
**Registration:** Required

### 2.5 NSIDC (National Snow and Ice Data Center)

**API:** `https://nsidc.org/data/`  
**Data:** Arctic/Antarctic ice extent, concentration, thickness  
**Update:** Daily  
**Use:** Ice routing, seasonal route planning  
**Cost:** FREE  
**License:** NASA / NSIDC

---

## 3. Port Data

### 3.1 World Port Index (NGA/NIMA)

**Source:** `https://msi.nga.mil/Publications/WPI`  
**Data:** ~3,700 ports with lat/lon, facilities, depths, pilotage requirements  
**Update:** Periodically  
**Use:** Port locations, basic attributes  
**Cost:** FREE  
**License:** Public domain (US government)

### 3.2 MarineTraffic / VesselFinder (AIS Data)

**API:** MarineTraffic API (requires key)  
**Data:** Real-time ship positions, port calls, port traffic  
**Update:** Near real-time  
**Use:** Port congestion, traffic density, realistic ship counts  
**Cost:** $ (subscription tiers)  
**Free Alternative:** Limited API calls on free tier

### 3.3 UNCTAD Liner Shipping Index

**Source:** `https://unctad.org/topic/transport-and-trade-logistics/liner-shipping`  
**Data:** Port connectivity, shipping lane data, container throughput  
**Update:** Annual  
**Use:** Port importance, route viability  
**Cost:** FREE  
**License:** UN open data

### 3.4 Lloyd's List Intelligence

**Source:** `https://lloydslist.maritimeintelligence.informa.com/`  
**Data:** Port throughput, congestion, fees, facilities  
**Update:** Daily/weekly  
**Use:** Premium port data  
**Cost:** $$$ (subscription)  
**Free Alternative:** Manual port authority websites

### 3.5 Port Authority Websites

Many port authorities publish:
- Port fees and tariffs
- Facility lists
- Depth restrictions
- Contact information

**Approach:** Web scraping (respect robots.txt) or manual curation

---

## 4. Ship Data

### 4.1 IMO GISIS (Global Integrated Shipping Information System)

**Source:** `https://gisis.imo.org/`  
**Data:** Ship registry, specifications, classification  
**Update:** Continuous  
**Use:** Real ship specifications  
**Cost:** FREE (public search)  
**License:** IMO terms

### 4.2 Clarksons Research

**Source:** `https://sin.clarksons.com/`  
**Data:** Fleet data, valuations, newbuilding orders  
**Update:** Daily  
**Use:** Ship valuations, market trends  
**Cost:** $$$ (subscription)  
**Free Alternative:** Limited public data

### 4.3 VesselValue

**Source:** `https://www.vesselsvalue.com/`  
**Data:** Ship valuations, fleet tracking  
**Update:** Daily  
**Use:** Ship pricing for game economy  
**Cost:** $ (free trial available)

---

## 5. Historical Data

### 5.1 CLIWOC (Climatological Database for the World's Oceans)

**Source:** `https://www.ceda.ac.uk/`  
**Data:** 1750–1850 ship logs, weather observations  
**Update:** Static dataset  
**Use:** Age of Sail weather, routes, historical accuracy  
**Cost:** FREE  
**License:** Open data

### 5.2 Slave Voyages Database

**Source:** `https://www.slavevoyages.org/`  
**Data:** 36,000+ trans-Atlantic slave voyages (1526–1866)  
**Update:** Static  
**Use:** Historical routes (ethical handling required)  
**Cost:** FREE  
**License:** CC BY-NC 4.0  
**Note:** Include historical accuracy toggle + educational context

### 5.3 East India Company Records

**Source:** British Library / various archives  
**Data:** Trade routes, commodity prices, port records (1600–1850)  
**Use:** Age of Sail commodity pricing, port importance  
**Cost:** FREE (public domain)  
**Access:** Digitization projects, academic access

---

## 6. Geospatial Data

### 6.1 Natural Earth

**Source:** `https://www.naturalearthdata.com/`  
**Data:** Cultural (ports, cities), physical (coastlines, bathymetry), raster (relief)  
**Use:** World map base layer  
**Cost:** FREE  
**License:** Public domain

### 6.2 OpenStreetMap (OSM)

**API:** Overpass API  
**Data:** Port locations, facilities, roads, rail connections  
**Use:** Port detail, infrastructure connections  
**Cost:** FREE  
**License:** ODbL (Open Database License)

### 6.3 GEBCO (General Bathymetric Chart of the Oceans)

**Source:** `https://www.gebco.net/`  
**Data:** Ocean depth data  
**Use:** Route planning (shallow water avoidance)  
**Cost:** FREE  
**License:** Open data

---

## 7. Data Pipeline Architecture

```
┌─────────────────────────────────────────────────────────┐
│                    DATA SOURCES                          │
│  Commodities  │  Weather  │  Ports  │  Ships  │  History │
└──────────────────┬────────────────────────────────────────┘
                   │
        ┌──────────┴──────────┐
        │   Python Fetchers   │  (Tools/DataPipeline/)
        │                     │
        │  • fetch_prices.py  │
        │  • fetch_weather.py │
        │  • fetch_ports.py   │
        │  • fetch_history.py │
        └──────────┬──────────┘
                   │
        ┌──────────┴──────────┐
        │  Data Validation    │
        │  • Sanity checks     │
        │  • Outlier detection │
        │  • Source fallback   │
        └──────────┬──────────┘
                   │
        ┌──────────┴──────────┐
        │   SQLite Cache      │
        │  (local/offline)    │
        └──────────┬──────────┘
                   │
        ┌──────────┴──────────┐
        │   Data Transform    │
        │  • Normalize units   │
        │  • Calculate indices │
        │  • Build history     │
        └──────────┬──────────┘
                   │
        ┌──────────┴──────────┐
        │  UE5 Data Tables     │
        │  (Content/DataTables)│
        └──────────┬──────────┘
                   │
        ┌──────────┴──────────┐
        │   In-Game Systems    │
        │  • Market            │
        │  • Weather           │
        │  • Navigation        │
        └─────────────────────┘
```

---

## 8. Implementation Strategy

### 8.1 Priorities

| Priority | Data Source | Phase | Reason |
|----------|-------------|-------|--------|
| **P0** | World Port Index | Phase 0 | Core geography |
| **P0** | Open-Meteo | Phase 1 | Free, no key, weather core mechanic |
| **P0** | World Bank Commodities | Phase 1 | Free, base economy |
| **P1** | Trading Economics | Phase 2 | Real-time prices |
| **P1** | Copernicus Marine | Phase 2 | Ocean currents |
| **P2** | Baltic Exchange | Phase 3 | Freight rates (if budget allows) |
| **P2** | MarineTraffic | Phase 3 | Real-time port data |
| **P2** | CLIWOC | Phase 4 | Historical weather |
| **P3** | NSIDC | Phase 4 | Ice routing |
| **P3** | ECMWF | Phase 5 | Premium weather |

### 8.2 Rate Limiting & Caching

```python
# Cache strategy
CACHE_TTL = {
    "commodity_prices": 3600,    # 1 hour
    "weather_forecast": 1800,     # 30 minutes
    "port_data": 86400,           # 24 hours (slow-changing)
    "ship_data": 604800,          # 7 days (very slow)
    "historical": -1,             # Never expires
}

# Rate limiter
RATE_LIMITS = {
    "trading_economics": 100,     # per day (free tier)
    "open_meteo": 10000,         # per day
    "world_bank": 100,           # per minute
}
```

### 8.3 Fallback Strategy

1. Try primary source
2. If fail: try secondary source
3. If fail: use cached data
4. If no cache: use static snapshot (shipped with game)
5. Notify player: "Using cached data — last updated: YYYY-MM-DD"

---

## 9. Data License Compliance

| Source | License | Commercial Use | Attribution Required |
|--------|---------|---------------|---------------------|
| Open-Meteo | CC BY 4.0 | ✅ Yes | ✅ Yes |
| World Bank | CC BY 4.0 | ✅ Yes | ✅ Yes |
| NOAA | Public Domain | ✅ Yes | ❌ No |
| Natural Earth | Public Domain | ✅ Yes | ❌ No |
| GEBCO | Open Data | ✅ Yes | ✅ Yes |
| OSM | ODbL | ✅ Yes | ✅ Share-Alike |
| Trading Economics | Commercial | ✅ Yes (paid) | ✅ Yes |
| Baltic Exchange | Commercial | ✅ Yes (subscription) | ✅ Yes |
| CLIWOC | Open Data | ✅ Yes | ✅ Yes |
| Copernicus | Free/Commercial | ✅ Yes | ✅ Yes |
| ECMWF | Academic/Commercial | ⚠️ Restricted | ✅ Yes |
| NSIDC | NASA Open | ✅ Yes | ✅ Yes |

**Action items:**
- [ ] Create ATTRIBUTION.md with all data sources
- [ ] Include attributions in-game (settings → credits → data sources)
- [ ] Review licenses before commercial release
- [ ] Set up automated license compliance checks

---

## 10. API Keys Management

### 10.1 Environment Variables

```bash
# .env.example (never commit real keys!)
TRADING_ECONOMICS_API_KEY=your_key_here
MARINETRAFFIC_API_KEY=your_key_here
BALTIC_EXCHANGE_API_KEY=your_key_here
ECMWF_API_KEY=your_key_here
COPERNICUS_API_KEY=your_key_here
```

### 10.2 Game Build

- Free APIs: embedded in build (no keys needed)
- Paid APIs: keys loaded from config file (not committed)
- CI/CD: keys injected from GitHub Secrets

---

## 11. Offline Play

### 11.1 Static Data Snapshot

Ship with game:
- Full port database (World Port Index)
- Historical commodity prices (5 years)
- Historical weather patterns (seasonal averages)
- Ship specifications database

### 11.2 Cache Behavior

```
Online:   Fetch real-time data → cache → display
Offline:  Use cache → if stale, use snapshot → display warning
```

### 11.3 Cache Size Limits

| Data Type | Max Cache Size | Retention |
|-----------|---------------|-----------|
| Commodity prices | 50 MB | 30 days |
| Weather forecasts | 100 MB | 7 days |
| Port data | 20 MB | 90 days |
| Ship data | 10 MB | 365 days |
| Historical | 200 MB | Forever |

---

*Document owner: Munin 🐦‍⬛*  
*Updated: 2026-05-14*
