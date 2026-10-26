#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Indicates production or test
enum class TestModeFlag : std::uint8_t {
    Production = 1, // Production
    Test = 2,       // Test
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TestModeFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TestModeFlag value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
