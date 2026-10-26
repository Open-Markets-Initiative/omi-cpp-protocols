#include "Authenticity.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

std::string_view to_string(Authenticity value) {
    switch (value) {
        case Authenticity::LiveProduction: return "Live Production";
        case Authenticity::Test: return "Test";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Authenticity value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
