#pragma once

#include "../types/SeriesIndex.hpp"
#include "../types/SeriesType.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/OptionSymbolRoot.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/UnderlyingIndex.hpp"
#include "../types/PriceScaleCode.hpp"
#include "../types/ContractMultiplier.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/PutOrCall.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/ClosingOnlyIndicator.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

#pragma pack(push, 1)

// This message is published over the real-time data channels at system startup or in the context of a refresh sequence after a Matching Engine or PILLAR Publisher failover.
struct OutrightSeriesIndexMappingMessage {

    SeriesIndex series_index;
    SeriesType series_type;
    MarketId market_id;
    SystemId system_id;
    OptionSymbolRoot option_symbol_root;
    UnderlyingSymbol underlying_symbol;
    UnderlyingIndex underlying_index;
    PriceScaleCode price_scale_code;
    ContractMultiplier contract_multiplier;
    MaturityDate maturity_date;
    PutOrCall put_or_call;
    StrikePrice strike_price;
    ClosingOnlyIndicator closing_only_indicator;
    Reserved1 reserved_1;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 50;

    // parse method
    static OutrightSeriesIndexMappingMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OutrightSeriesIndexMappingMessage*>(buffer);
    }

    // parse method const
    static const OutrightSeriesIndexMappingMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OutrightSeriesIndexMappingMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OutrightSeriesIndexMappingMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OutrightSeriesIndexMappingMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
