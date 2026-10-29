#include "RetransmitMethod.hpp"

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

std::string_view to_string(RetransmitMethod value) {
    switch (value) {
        case RetransmitMethod::Udp: return "Udp";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RetransmitMethod value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::arcaequities::bbo::xdp::v2_4_c
