#pragma once

#include "../types/UnderlyingIndex.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/ChannelId.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/ExchangeCode.hpp"
#include "../types/PriceScaleCode.hpp"
#include "../types/SecurityType.hpp"
#include "../types/PriceResolution.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// On system startup, each multicast channel sends all the symbols on its channel. Underlying Index Mapping messages are published first, followed by all Series Index Mapping messages, and for the Complex feed, Complex Symbol Definitions last of all.
struct UnderlyingIndexMappingMessage {

    UnderlyingIndex underlying_index;
    UnderlyingSymbol underlying_symbol;
    ChannelId channel_id;
    MarketId market_id;
    SystemId system_id;
    ExchangeCode exchange_code;
    PriceScaleCode price_scale_code;
    SecurityType security_type;
    PriceResolution price_resolution;
    Reserved1 reserved_1;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 435;

    // parse method
    static UnderlyingIndexMappingMessage* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingIndexMappingMessage*>(buffer);
    }

    // parse method const
    static const UnderlyingIndexMappingMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingIndexMappingMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const UnderlyingIndexMappingMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const UnderlyingIndexMappingMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
