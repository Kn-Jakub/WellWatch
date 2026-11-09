# 0003 — MQTT as the integration bus, Mosquitto on the RPi 5

**Status:** Accepted · **Date:** 2026-10-30

## Context
Several parts need to exchange data: the LoRa gateway, the simulator, the C++ hub and Home Assistant. They should not know about each other directly.

## Decision
- **Mosquitto** broker in Docker on the **RPi 5**. Home Assistant connects to it through its MQTT integration (no broker inside HA).
- The gateway and the simulator publish **the same raw messages**, so the hub cannot tell them apart:
  - `wellwatch/node/<node_id>/raw` — JSON, integers only: `seq`, `distance_mm`, `temp_cdeg` (0.01 °C), `supply_mv`, `rssi`, `snr`, `rx_ts` (receive time added by the gateway — the node has no clock).
- The hub publishes processed values to `wellwatch/site/<site_id>/state` and Home Assistant discovery topics under `homeassistant/`.
- C++ client library: Eclipse Paho MQTT C++.

## Consequences
- The hub can be developed and tested end-to-end with the simulator before any hardware exists.
- HA integration is just discovery messages — no HA-specific code in the core.
- The broker is a single point of failure at home; acceptable for this use.
- The topic and payload layout is a contract — a change means a new ADR and a payload `version` field.
