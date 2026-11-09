# 0004 — One repository for all parts

**Status:** Accepted · **Date:** 2026-10-30

## Context
The project has a C++ hub, a Qt dashboard, protobuf definitions, a simulator and later ESP32 firmware. They share message formats.

## Decision
One GitHub repository:
```
hub/  dashboard/  proto/  simulator/  firmware/  docs/adr/  .github/workflows/
```
Each part builds on its own (own CMake target / PlatformIO project), one CI workflow per part.

## Consequences
- A change to a message format and all its users is one commit, one review.
- One place to link from the CV.
- CI must build only the changed parts (path filters) so it stays fast.
