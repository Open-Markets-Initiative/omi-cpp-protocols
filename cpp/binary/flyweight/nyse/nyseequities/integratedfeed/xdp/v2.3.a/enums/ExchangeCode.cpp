#include "ExchangeCode.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

std::string_view to_string(ExchangeCode value) {
    switch (value) {
        case ExchangeCode::NyseAmerican: return "Nyse American";
        case ExchangeCode::Ltse: return "Ltse";
        case ExchangeCode::Nyse: return "Nyse";
        case ExchangeCode::NyseArca: return "Nyse Arca";
        case ExchangeCode::Nasdaq: return "Nasdaq";
        case ExchangeCode::Iex: return "Iex";
        case ExchangeCode::Cboe: return "Cboe";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExchangeCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
