#pragma once

#include "../types/Timestamp.hpp"
#include "../types/Instrument.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/StatisticType.hpp"
#include "../types/StatisticPrice.hpp"
#include "../types/StatisticSize.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ImbalanceQuantity.hpp"
#include "../types/AuctionInfo.hpp"
#include "../types/OpeningClosingPriceIndicator.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

#pragma pack(push, 1)

// Contains a set of statistics that are not updated frequently.
struct StatisticsUpdateMessage {

    Timestamp timestamp;
    Instrument instrument;
    SourceVenue source_venue;
    StatisticType statistic_type;
    StatisticPrice statistic_price;
    StatisticSize statistic_size;
    AuctionType auction_type;
    ImbalanceQuantity imbalance_quantity;
    AuctionInfo auction_info;
    OpeningClosingPriceIndicator opening_closing_price_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x6A;

    // parse method
    static StatisticsUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StatisticsUpdateMessage*>(buffer);
    }

    // parse method const
    static const StatisticsUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StatisticsUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StatisticsUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StatisticsUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
