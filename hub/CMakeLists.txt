# The hub: a modular monolith (docs/adr/0005).
#   core/  plain C++ processing logic, no MQTT / gRPC / SQLite / Qt includes
#   app/   the wellwatch-hub executable that wires the modules together
# Adapters (ingest/, storage/, api/) are added in later steps.

add_subdirectory(core)
add_subdirectory(app)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
