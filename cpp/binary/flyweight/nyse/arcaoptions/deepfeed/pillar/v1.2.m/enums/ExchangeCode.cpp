#include "ExchangeCode.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(ExchangeCode value) {
    switch (value) {
        case ExchangeCode::NyseAmerican: return "Nyse American";
        case ExchangeCode::Txse: return "Txse";
        case ExchangeCode::Ltse: return "Ltse";
        case ExchangeCode::NyseTexas: return "Nyse Texas";
        case ExchangeCode::Nyse: return "Nyse";
        case ExchangeCode::NyseArca: return "Nyse Arca";
        case ExchangeCode::Nasdaq: return "Nasdaq";
        case ExchangeCode::Iex: return "Iex";
        case ExchangeCode::Cboe: return "Cboe";
        case ExchangeCode::OtcOrIndexBasedProductSpaceOr0X20: return "Otc Or Index Based Product Space Or 0 X 20";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExchangeCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
