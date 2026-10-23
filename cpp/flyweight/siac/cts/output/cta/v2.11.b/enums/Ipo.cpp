#include "Ipo.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(Ipo value) {
    switch (value) {
        case Ipo::NotAnIpoSymbol: return "Not An Ipo Symbol";
        case Ipo::IpoSymbol: return "Ipo Symbol";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Ipo value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
