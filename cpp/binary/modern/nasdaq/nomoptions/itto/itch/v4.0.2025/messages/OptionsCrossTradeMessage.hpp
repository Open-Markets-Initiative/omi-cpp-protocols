#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OptionId.hpp"
#include "../types/CrossNumber.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/CrossType.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// This message will also be used to report all executions within a price improvement (PRISM) auction.
struct OptionsCrossTradeMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    OptionId option_id;
    CrossNumber cross_number;
    MatchNumber match_number;
    CrossType cross_type;
    PriceLong price_long;
    VolumeLong volume_long;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Q';

    // parse method
    static OptionsCrossTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsCrossTradeMessage*>(buffer);
    }

    // parse method const
    static const OptionsCrossTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsCrossTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsCrossTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsCrossTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
