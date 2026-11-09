#include "wellwatch/core/version.hpp"

namespace wellwatch::core {

std::string_view version() noexcept {
    return WELLWATCH_VERSION;
}

} // namespace wellwatch::core
