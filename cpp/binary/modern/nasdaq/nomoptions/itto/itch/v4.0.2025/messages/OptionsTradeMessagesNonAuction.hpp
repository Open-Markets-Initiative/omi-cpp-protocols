#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/OptionId.hpp"
#include "../types/CrossNumber.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// This Options Trade Message is designed to provide execution details for normal match events involving non-displayable order types. (Note: There is a separate message for NASDAQ Option auction events.)
struct OptionsTradeMessagesNonAuction {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    BuySellIndicator buy_sell_indicator;
    OptionId option_id;
    CrossNumber cross_number;
    MatchNumber match_number;
    PriceLong price_long;
    VolumeLong volume_long;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'P';

    // parse method
    static OptionsTradeMessagesNonAuction* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsTradeMessagesNonAuction*>(buffer);
    }

    // parse method const
    static const OptionsTradeMessagesNonAuction* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsTradeMessagesNonAuction*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsTradeMessagesNonAuction* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsTradeMessagesNonAuction*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
