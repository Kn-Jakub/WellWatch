#pragma once

#include <string_view>

namespace wellwatch::core {

/// Version of the hub, taken from the CMake project version.
[[nodiscard]] std::string_view version() noexcept;

} // namespace wellwatch::core
