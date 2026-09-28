#include "TrdSubType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

std::string_view to_string(TrdSubType value) {
    switch (value) {
        case TrdSubType::MultiAssetTrade: return "Multi Asset Trade";
        case TrdSubType::LegTrade: return "Leg Trade";
        case TrdSubType::MidpointTrade: return "Midpoint Trade";
        case TrdSubType::BlockBookTrade: return "Block Book Trade";
        case TrdSubType::RfTrade: return "Rf Trade";
        case TrdSubType::RlpTrade: return "Rlp Trade";
        case TrdSubType::TacTrade: return "Tac Trade";
        case TrdSubType::TaaTrade: return "Taa Trade";
        case TrdSubType::SweepTrade: return "Sweep Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TrdSubType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
