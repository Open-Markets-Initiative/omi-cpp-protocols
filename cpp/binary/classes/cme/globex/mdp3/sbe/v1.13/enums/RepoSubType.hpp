#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Repo Sub Security Type
enum class RepoSubType : std::uint8_t {
    Special = 0,  // Special
    Gc = 1,       // Gc
    GcForDbv = 2, // Gc For Dbv
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RepoSubType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RepoSubType value);

} // namespace cme::globex::mdp3::sbe::v1_13
