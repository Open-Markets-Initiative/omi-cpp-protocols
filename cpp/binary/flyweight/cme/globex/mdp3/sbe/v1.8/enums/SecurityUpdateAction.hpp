#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_8 {

// Last Security update action on Incremental feed, 'D' or 'M' is used when a mid-week deletion
// or modification (i.e. extension) occurs
enum class SecurityUpdateAction : char {
    Add = 'A',    // Add
    Delete = 'D', // Delete
    Modify = 'M', // Modify
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityUpdateAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityUpdateAction value);

} // namespace cme::globex::mdp3::sbe::v1_8
