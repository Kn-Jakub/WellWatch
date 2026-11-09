# 0002 — Point-to-point LoRa on 868 MHz between site and home

**Status:** Accepted · **Date:** 2026-10-30

## Context
The well (and later the reservoir) is up to 1 km from the house, out of WiFi range. Both sites have electricity, a battery version may come later. Data rate is tiny: one reading every few minutes.

## Options
1. **WiFi** with a repeater — needs line of sight and powered repeaters, fragile over 1 km.
2. **LoRaWAN** (The Things Network or own gateway) — a standard, but needs a LoRaWAN gateway, network server and device registration. Overkill for 1–2 nodes.
3. **GSM/LTE modem** — monthly cost, SIM management.
4. **Point-to-point LoRa** — two ESP32 boards with LoRa modules, own simple protocol.

## Decision
Point-to-point LoRa, **868 MHz** EU band. Node at the site sends, an ESP32 gateway at home receives and forwards to MQTT ([0003-mqtt-as-integration-bus](0003-mqtt-as-integration-bus.md)).

## Consequences
- Cheap (~2 modules + antennas), long range, low power → battery version stays possible.
- Own binary packet format (version, node id, sequence number, payload, CRC) — to be designed in its own ADR together with the firmware.
- EU duty cycle limit 1 % — fine for a reading every few minutes; must be respected if the interval is shortened.
- No delivery guarantee: lost packets are detected by gaps in the sequence number, not retransmitted.
- **Risk:** terrain can block 1 km → early range test with two boards (RSSI/SNR) before the hardware design is fixed.
