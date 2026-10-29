#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/FirstLevelPrice.hpp"
#include "../types/SecondLevelPrice.hpp"
#include "../types/ThirdLevelPrice.hpp"
#include "../types/FirstVolume.hpp"
#include "../types/SecondVolume.hpp"
#include "../types/ThirdVolume.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Reserved1.hpp"
#include "../types/FirstLevelCustomerVolume.hpp"
#include "../types/SecondLevelCustomerVolume.hpp"
#include "../types/ThirdLevelCustomerVolume.hpp"
#include "../types/Reserved2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// The Refresh Market Depth Sell message is sent in the event no Sell Market Depth messages are published for the symbol for 2 consecutive minutes.
struct RefreshOutrightMarketDepthSellMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SymbolSeqNum symbol_seq_num;
    FirstLevelPrice first_level_price;
    SecondLevelPrice second_level_price;
    ThirdLevelPrice third_level_price;
    FirstVolume first_volume;
    SecondVolume second_volume;
    ThirdVolume third_volume;
    QuoteCondition quote_condition;
    Reserved1 reserved_1;
    FirstLevelCustomerVolume first_level_customer_volume;
    SecondLevelCustomerVolume second_level_customer_volume;
    ThirdLevelCustomerVolume third_level_customer_volume;
    Reserved2 reserved_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 505;

    // parse method
    static RefreshOutrightMarketDepthSellMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RefreshOutrightMarketDepthSellMessage*>(buffer);
    }

    // parse method const
    static const RefreshOutrightMarketDepthSellMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RefreshOutrightMarketDepthSellMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RefreshOutrightMarketDepthSellMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RefreshOutrightMarketDepthSellMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
