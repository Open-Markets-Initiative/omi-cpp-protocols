#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies whether the security symbol is a test symbol
enum class Test : char {
    NotATestSymbol = '0', // Not A Test Symbol
    TestSymbol = '1',     // Test Symbol
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Test value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Test value);

} // namespace siac::cts::output::cta::v2_11_b
