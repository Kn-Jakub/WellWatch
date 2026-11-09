# WellWatch

Water level monitoring for our well, and later for the public reservoir. An ESP32 + LoRa sensor node measures the distance to the water, a gateway forwards it over MQTT, and a C++20 hub on a Raspberry Pi 5 turns the raw readings into level, volume, consumption and refill rate, "hours until empty" and alerts.

> **Status:** step 1 of 7, the project skeleton (CMake presets, GoogleTest, CI). See [Roadmap](#roadmap).

## Why

This year we had problems with water distribution. The goal is to know the level of the well at any time, how fast it is consumed and how fast it refills, and to get an alert before it runs empty.

## Architecture

```
 SITE (well / reservoir)            HOME                          RPi 5
┌──────────────────────┐   LoRa   ┌──────────────┐  MQTT   ┌──────────────────────────────────┐
│ ESP32 + LoRa node    │ ───────► │ ESP32 LoRa   │ ──────► │ Mosquitto broker (Docker)        │
│ level + temp sensor  │ 868 MHz  │ gateway      │  WiFi   │        │                         │
│ mains powered (v1)   │  ≤ 1 km  │ (LoRa→MQTT)  │         │ C++ hub service                  │
└──────────────────────┘          └──────────────┘         │  ingest → filter → level/volume  │
                                                           │  → trends, alerts → SQLite       │
                                                           │  gRPC API ──► Qt/QML dashboard   │
                                                           │  MQTT discovery ──► Home Assistant│
                                                           └──────────────────────────────────┘
```

The hub is a modular monolith: the processing core is plain C++ with no MQTT, database or UI dependencies, and talks to the outside through small interfaces. The reasons for this and the other choices are in the [architecture decision records](docs/adr/).

## Build and test

Requirements: a C++20 compiler (GCC 13+ or Clang 17+), CMake 3.25+, Ninja. GoogleTest is downloaded by CMake.

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

| Preset | Purpose |
|---|---|
| `debug` | Development build |
| `release` | Optimised build |
| `asan` | AddressSanitizer + UndefinedBehaviorSanitizer |
| `tsan` | ThreadSanitizer |
| `tidy` | Debug build with clang-tidy (build only) |

CI (GitHub Actions) builds and tests every preset with warnings as errors, runs clang-tidy and checks the formatting with clang-format.

## Repository layout

```
hub/          C++ service: core/ (processing), app/ (executable), tests/
docs/adr/     architecture decision records
.github/      CI workflows
```

Planned: `dashboard/` (Qt/QML), `proto/` (protobuf), `simulator/` (fake node publishing to MQTT), `firmware/` (ESP32 node and gateway).

## Roadmap

1. **Skeleton:** CMake presets, GoogleTest, GitHub Actions ← *current*
2. Simulator + MQTT ingest (Mosquitto in Docker)
3. Processing core: filtering, temperature compensation, level/volume, trends, alerts
4. SQLite history + gRPC API
5. Qt/QML dashboard
6. Docker image + ARM64 build for the Raspberry Pi 5
7. Real hardware and ESP32 firmware, then v2 for the reservoir

Rule: simulator first, hardware last. The hub must work on simulated data before anything is soldered.
