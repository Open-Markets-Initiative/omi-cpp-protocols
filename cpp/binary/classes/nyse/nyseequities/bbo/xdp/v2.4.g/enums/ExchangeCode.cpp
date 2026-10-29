#include "ExchangeCode.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

std::string_view to_string(ExchangeCode value) {
    switch (value) {
        case ExchangeCode::NyseAmerican: return "Nyse American";
        case ExchangeCode::NyseNational: return "Nyse National";
        case ExchangeCode::Nyse: return "Nyse";
        case ExchangeCode::NyseArca: return "Nyse Arca";
        case ExchangeCode::Nasdaq: return "Nasdaq";
        case ExchangeCode::Iex: return "Iex";
        case ExchangeCode::Bats: return "Bats";
        case ExchangeCode::GlobalOtc: return "Global Otc";
        case ExchangeCode::Otcbb: return "Otcbb";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExchangeCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
