# 0008 — Site geometry and thresholds are configuration, not code

**Status:** Accepted · **Date:** 2026-10-30

## Context
v1 is our well (1.5 m deep, 60 cm diameter, sensor ~1 m above the water). v2 is the public reservoir with a different shape and maybe a different sensor. Alert thresholds will be tuned over time.

## Decision
Each site is described in a **JSON** config file loaded at start: site id, node id(s), geometry (shape, dimensions, sensor height), sensor type and limits, alert thresholds. Library: **nlohmann/json** — the same library is needed for the MQTT payloads ([0003-mqtt-as-integration-bus](0003-mqtt-as-integration-bus.md)), so there is only one.

## Consequences
- v2 = a new config file, not new code.
- Config is validated at start; an invalid file stops the hub with a clear message.
- Geometry calculations are tested with several shapes (cylinder, rectangular tank).
