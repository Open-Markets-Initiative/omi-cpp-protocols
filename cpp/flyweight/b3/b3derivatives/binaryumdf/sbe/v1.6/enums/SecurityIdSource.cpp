#include "SecurityIdSource.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

std::string_view to_string(SecurityIdSource value) {
    switch (value) {
        case SecurityIdSource::Isin: return "Isin";
        case SecurityIdSource::ExchangeSymbol: return "Exchange Symbol";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityIdSource value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
