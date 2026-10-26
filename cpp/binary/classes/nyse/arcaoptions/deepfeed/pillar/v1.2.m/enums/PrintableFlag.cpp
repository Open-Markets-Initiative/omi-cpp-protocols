#include "PrintableFlag.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(PrintableFlag value) {
    switch (value) {
        case PrintableFlag::TradeNotIncludedInTotalVolume: return "Trade Not Included In Total Volume";
        case PrintableFlag::TradeIncludedInTotalVolume: return "Trade Included In Total Volume";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PrintableFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
