#pragma once

#include "../types/OptionId.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/LegId.hpp"
#include "../types/ExpirationYear.hpp"
#include "../types/ExpirationMonth.hpp"
#include "../types/ExpirationDay.hpp"
#include "../types/ExplicitStrikePrice.hpp"
#include "../types/OptionType.hpp"
#include "../types/Side.hpp"
#include "../types/LegRatio.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

#pragma pack(push, 1)

struct LegInformation {

    OptionId option_id;
    SecuritySymbol security_symbol;
    LegId leg_id;
    ExpirationYear expiration_year;
    ExpirationMonth expiration_month;
    ExpirationDay expiration_day;
    ExplicitStrikePrice explicit_strike_price;
    OptionType option_type;
    Side side;
    LegRatio leg_ratio;

    // parse method
    static LegInformation* parse(std::byte* buffer) {
        return reinterpret_cast<LegInformation*>(buffer);
    }

    // parse method const
    static const LegInformation* parse(const std::byte* buffer) {
        return reinterpret_cast<const LegInformation*>(buffer);
    }
};

#pragma pack(pop)
}
