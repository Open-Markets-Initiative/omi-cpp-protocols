#include "ExchangeCode.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

std::string_view to_string(ExchangeCode value) {
    switch (value) {
        case ExchangeCode::Nyse: return "Nyse";
        case ExchangeCode::NyseArca: return "Nyse Arca";
        case ExchangeCode::Nasdaq: return "Nasdaq";
        case ExchangeCode::NyseMkt: return "Nyse Mkt";
        case ExchangeCode::GlobalOtc: return "Global Otc";
        case ExchangeCode::ArcaLocalNonTapeBIndex: return "Arca Local Non Tape B Index";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExchangeCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
