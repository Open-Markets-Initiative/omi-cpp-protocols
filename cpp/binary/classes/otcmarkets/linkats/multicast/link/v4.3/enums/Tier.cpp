#include "Tier.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(Tier value) {
    switch (value) {
        case Tier::NoTier: return "No Tier";
        case Tier::OtcqxusPremier: return "Otcqxus Premier";
        case Tier::Otcqxus: return "Otcqxus";
        case Tier::OtcqxInternationalPremier: return "Otcqx International Premier";
        case Tier::OtcqxInternational: return "Otcqx International";
        case Tier::Otcqb: return "Otcqb";
        case Tier::OtcbbOnly: return "Otcbb Only";
        case Tier::PinkCurrent: return "Pink Current";
        case Tier::PinkLimited: return "Pink Limited";
        case Tier::PinkNoInformation: return "Pink No Information";
        case Tier::GreyMarket: return "Grey Market";
        case Tier::ExpertMarket: return "Expert Market";
        case Tier::OtcBonds: return "Otc Bonds";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Tier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
