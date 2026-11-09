# 0005 — Hub as a modular monolith with a framework-free core

**Status:** Accepted · **Date:** 2026-10-30

## Context
The hub combines MQTT, processing, storage and an API. Libraries may change (Paho → another client, SQLite → something else), and the processing logic is the part that needs the most tests.

## Decision
- **One process**, split into modules with hard boundaries — no microservices.
- **Ports and adapters:** `core/` (filtering, compensation, level/volume, trends, alerts) is plain C++ with **no** MQTT, gRPC, SQLite or Qt includes. It talks to the outside through small interfaces (e.g. `MeasurementSource`, `HistoryStore`, `AlertSink`).
- `ingest/`, `storage/`, `api/` are adapters implementing those interfaces.

## Consequences
- The core is unit-tested with GoogleTest/GMock and fake adapters — no broker or database in unit tests.
- Replacing a library touches one adapter, not the logic.
- A bit more code up front (interfaces) — worth it, and it is a good thing to show and explain in interviews.
