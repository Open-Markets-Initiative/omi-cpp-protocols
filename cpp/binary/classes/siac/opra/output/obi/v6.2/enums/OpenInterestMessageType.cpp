#include "OpenInterestMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(OpenInterestMessageType value) {
    switch (value) {
        case OpenInterestMessageType::OpenInterest: return "Open Interest";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpenInterestMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
