#include "RetransmissionIndicator.hpp"

namespace siac::cts::output::cta::v2_10 {

std::string_view to_string(RetransmissionIndicator value) {
    switch (value) {
        case RetransmissionIndicator::Original: return "Original";
        case RetransmissionIndicator::Retransmitted: return "Retransmitted";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RetransmissionIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_10
