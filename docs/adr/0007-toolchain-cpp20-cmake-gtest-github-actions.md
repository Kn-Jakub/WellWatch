# 0007 — Toolchain: C++20, CMake presets, GoogleTest, GitHub Actions

**Status:** Accepted · **Date:** 2026-10-30

## Context
The hub must build on a desktop (development) and for the RPi 5 (ARM64). The repo is also meant to show modern engineering practice.

## Decision
- **C++20** (concepts, `std::jthread`, `std::span`, ranges). `std::format` only if the RPi's GCC is 13 or newer — otherwise the `{fmt}` library. *Check the GCC version on the RPi at step 1.*
- **CMake** with presets: `debug`, `release`, `asan`, `tsan`; dependencies through `FetchContent` or the distro packages.
- **GoogleTest + GoogleMock**.
- **clang-format** and **clang-tidy**, warnings `-Wall -Wextra -Wpedantic -Werror` in CI.
- **GitHub Actions:** build + tests on every push, sanitizer builds, later the ARM64 build and Docker image.

## Consequences
- CI is green from the first commit — the habit starts with an empty project.
- Sanitizer builds catch memory errors and data races early (the processing core is multithreaded).
- C++20 on GCC 12+ is fine for the RPi OS; C++23 features are avoided until the toolchain is confirmed.
