# 0006 — Nodes send raw measurements, all processing happens in the hub

**Status:** Accepted · **Date:** 2026-10-30

## Context
Filtering, temperature compensation and converting distance to level/volume could run on the ESP32 or in the hub.

## Decision
The node sends **raw values only** (distance, temperature, supply voltage). Everything else happens in the hub.

## Consequences
- Firmware stays small and rarely changes — updating a device in a well is harder than updating the RPi.
- Algorithms are written and tested in C++ on Linux, with the full toolchain (sanitizers, debugger, benchmarks).
- Raw history is stored, so improved filters can be re-run on old data.
- A few more bytes over LoRa — negligible.
- A node that is offline has no local logic (e.g. no local alarm). Acceptable: alerts come from the hub, and "node offline" is itself an alert.
