#include "Type.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(Type value) {
    switch (value) {
        case Type::PriceImprovement: return "Price Improvement";
        case Type::Facilitation: return "Facilitation";
        case Type::Solicitation: return "Solicitation";
        case Type::Bold: return "Bold";
        case Type::Coa: return "Coa";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Type value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
