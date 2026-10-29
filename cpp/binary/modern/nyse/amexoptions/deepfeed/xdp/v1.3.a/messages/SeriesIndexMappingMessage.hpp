#pragma once

#include "../types/SeriesIndex.hpp"
#include "../types/ChannelId.hpp"
#include "../types/ReservedA1.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/ReservedB1.hpp"
#include "../types/StreamId.hpp"
#include "../types/UnderlyingIndex.hpp"
#include "../types/ContractMultiplier.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/PutOrCall.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/PriceScaleCode.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/OptionSymbolRoot.hpp"
#include "../types/GroupId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// On system startup, each multicast channel sends all the symbols on its channel. Underlying Index Mapping messages are published first, followed by all Series Index Mapping messages, and for the Complex feed, Complex Symbol Definitions last of all.
struct SeriesIndexMappingMessage {

    SeriesIndex series_index;
    ChannelId channel_id;
    ReservedA1 reserved_a_1;
    MarketId market_id;
    SystemId system_id;
    ReservedB1 reserved_b_1;
    StreamId stream_id;
    UnderlyingIndex underlying_index;
    ContractMultiplier contract_multiplier;
    MaturityDate maturity_date;
    PutOrCall put_or_call;
    StrikePrice strike_price;
    PriceScaleCode price_scale_code;
    UnderlyingSymbol underlying_symbol;
    OptionSymbolRoot option_symbol_root;
    GroupId group_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 437;

    // parse method
    static SeriesIndexMappingMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SeriesIndexMappingMessage*>(buffer);
    }

    // parse method const
    static const SeriesIndexMappingMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SeriesIndexMappingMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SeriesIndexMappingMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SeriesIndexMappingMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
