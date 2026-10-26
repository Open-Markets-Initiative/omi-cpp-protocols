#include "PriceType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(PriceType value) {
    switch (value) {
        case PriceType::StrikePriceIsAmount: return "Strike Price Is Amount";
        case PriceType::StrikePriceIsAmount2: return "Strike Price Is Amount";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
