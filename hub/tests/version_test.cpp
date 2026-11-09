#include <gtest/gtest.h>

#include "wellwatch/core/version.hpp"

namespace {

// Placeholder test so the pipeline runs from the first commit.
// The real core tests (filtering, compensation, level/volume) come in step 3.
TEST(Version, ReportsTheProjectVersion) {
    EXPECT_EQ(wellwatch::core::version(), WELLWATCH_EXPECTED_VERSION);
}

} // namespace
