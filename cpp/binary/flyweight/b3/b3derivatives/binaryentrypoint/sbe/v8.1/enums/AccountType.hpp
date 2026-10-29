#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// accountType
enum class AccountType : std::uint8_t {
    RemoveAccountInformation = 38, // Remove Account Information
    RegularAccount = 39,           // Regular Account
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AccountType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AccountType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
