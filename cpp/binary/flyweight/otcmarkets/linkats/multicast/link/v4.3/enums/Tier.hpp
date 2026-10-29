#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// The market tier assigned by OTC Markets Group.
enum class Tier : std::uint8_t {
    NoTier = 0,                    // No Tier
    OtcqxusPremier = 1,            // Otcqxus Premier
    Otcqxus = 2,                   // Otcqxus
    OtcqxInternationalPremier = 5, // Otcqx International Premier
    OtcqxInternational = 6,        // Otcqx International
    Otcqb = 10,                    // Otcqb
    OtcbbOnly = 11,                // Otcbb Only
    PinkCurrent = 20,              // Pink Current
    PinkLimited = 21,              // Pink Limited
    PinkNoInformation = 22,        // Pink No Information
    GreyMarket = 30,               // Grey Market
    ExpertMarket = 40,             // Expert Market
    OtcBonds = 50,                 // Otc Bonds
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Tier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Tier value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
