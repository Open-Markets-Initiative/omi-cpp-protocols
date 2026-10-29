#include "AllocType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(AllocType value) {
    switch (value) {
        case AllocType::RequestToIntermediary: return "Request To Intermediary";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AllocType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
