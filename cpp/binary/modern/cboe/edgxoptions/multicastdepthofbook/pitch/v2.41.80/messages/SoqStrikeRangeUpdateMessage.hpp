#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/SoqIdentifier.hpp"
#include "../types/LowerStrikePrice.hpp"
#include "../types/UpperStrikePrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// C1 Only. The SOQ Strike Range Update message is only available on the C1 Exchange. This message disseminates the minimum and maximum strike prices of the strike price range used to calculate the Special Opening Quote (SOQ) on a Volatility Settlement date. In the event that multiple distinct SOQ calculations occur on the same day, the applicable SOQ is differentiated by the SOQ Identifier field, which is set to the CSMi symbol on which the final settlement SOQ value is disseminated.
struct SoqStrikeRangeUpdateMessage {

    TimeOffset time_offset;
    SoqIdentifier soq_identifier;
    LowerStrikePrice lower_strike_price;
    UpperStrikePrice upper_strike_price;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x9D;

    // parse method
    static SoqStrikeRangeUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SoqStrikeRangeUpdateMessage*>(buffer);
    }

    // parse method const
    static const SoqStrikeRangeUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SoqStrikeRangeUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SoqStrikeRangeUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SoqStrikeRangeUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
