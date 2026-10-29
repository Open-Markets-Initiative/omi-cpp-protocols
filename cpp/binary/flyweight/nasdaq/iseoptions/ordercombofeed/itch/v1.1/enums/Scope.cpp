#include "Scope.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(Scope value) {
    switch (value) {
        case Scope::Local: return "Local";
        case Scope::National: return "National";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Scope value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
