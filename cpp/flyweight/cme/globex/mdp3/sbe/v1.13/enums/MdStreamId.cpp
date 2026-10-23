#include "MdStreamId.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(MdStreamId value) {
    switch (value) {
        case MdStreamId::MarketPlaceAssistant: return "Market Place Assistant";
        case MdStreamId::Globex: return "Globex";
        case MdStreamId::Refinitiv: return "Refinitiv";
        case MdStreamId::Icap: return "Icap";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdStreamId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_13
