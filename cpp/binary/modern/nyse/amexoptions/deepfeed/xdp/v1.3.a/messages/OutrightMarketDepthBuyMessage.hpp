#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/FirstLevelPrice.hpp"
#include "../types/SecondLevelPrice.hpp"
#include "../types/ThirdLevelPrice.hpp"
#include "../types/FirstLevelVolume.hpp"
#include "../types/SecondLevelVolume.hpp"
#include "../types/ThirdLevelVolume.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Reserved1.hpp"
#include "../types/FirstLevelCustomerVolume.hpp"
#include "../types/SecondLevelCustomerVolume.hpp"
#include "../types/ThirdLevelCustomerVolume.hpp"
#include "../types/Reserved2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// The Buy Market Depth message provides prices and aggregated volumes for each of the best three Buy levels.
struct OutrightMarketDepthBuyMessage {

    SourceTime source_time;
    SourceNs source_ns;
    SeriesIndex series_index;
    SymbolSeqNum symbol_seq_num;
    FirstLevelPrice first_level_price;
    SecondLevelPrice second_level_price;
    ThirdLevelPrice third_level_price;
    FirstLevelVolume first_level_volume;
    SecondLevelVolume second_level_volume;
    ThirdLevelVolume third_level_volume;
    QuoteCondition quote_condition;
    Reserved1 reserved_1;
    FirstLevelCustomerVolume first_level_customer_volume;
    SecondLevelCustomerVolume second_level_customer_volume;
    ThirdLevelCustomerVolume third_level_customer_volume;
    Reserved2 reserved_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 403;

    // parse method
    static OutrightMarketDepthBuyMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OutrightMarketDepthBuyMessage*>(buffer);
    }

    // parse method const
    static const OutrightMarketDepthBuyMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OutrightMarketDepthBuyMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OutrightMarketDepthBuyMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OutrightMarketDepthBuyMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
