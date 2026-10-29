#include "CrossType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::AllOrNoneCross: return "All Or None Cross";
        case CrossType::CrossExecutedAgainstBookFromClient: return "Cross Executed Against Book From Client";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
