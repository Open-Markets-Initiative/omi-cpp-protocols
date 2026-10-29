#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Symbol trading state
enum class State : char {
    Halted = 'H',  // Halted
    Trading = 'T', // Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(State value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, State value);

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
