#include "AccountType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(AccountType value) {
    switch (value) {
        case AccountType::RemoveAccountInformation: return "Remove Account Information";
        case AccountType::RegularAccount: return "Regular Account";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AccountType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
