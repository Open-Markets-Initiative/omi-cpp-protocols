#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Money or Par indicates if the GC is filled by par amount or by money amount
enum class MoneyOrPar : std::uint8_t {
    Money = 1, // Money
    Par = 2,   // Par
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MoneyOrPar value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MoneyOrPar value);

} // namespace cme::globex::mdp3::sbe::v1_13
