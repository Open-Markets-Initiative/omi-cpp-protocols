#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// posMaintAction
enum class PosMaintAction : char {
    New = '1',    // New
    Cancel = '3', // Cancel
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PosMaintAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PosMaintAction value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
