#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/StatisticType.hpp"
#include "../types/Price.hpp"
#include "../types/OpenClosePriceIndicator.hpp"
#include "../bitfields/StatisticsReserved.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Used to disseminate official Opening and Closing prices
struct StatisticsMessage {

    Nanosecond nanosecond;
    InstrumentId instrument_id;
    ReservedA reserved_a;
    ReservedB reserved_b;
    StatisticType statistic_type;
    Price price;
    OpenClosePriceIndicator open_close_price_indicator;
    StatisticsReserved statistics_reserved;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x77;

    // parse method
    static StatisticsMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StatisticsMessage*>(buffer);
    }

    // parse method const
    static const StatisticsMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StatisticsMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StatisticsMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StatisticsMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
