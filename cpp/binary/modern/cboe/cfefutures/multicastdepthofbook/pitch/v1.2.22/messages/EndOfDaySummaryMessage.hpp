#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/TradeDate.hpp"
#include "../types/OpenInterest.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/OpenPrice.hpp"
#include "../types/ClosePrice.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/BlockVolume.hpp"
#include "../types/EcrpVolume.hpp"
#include "../bitfields/SummaryFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// The End of Day Summary message is sent immediately after trading ends for a symbol. No more Market Update messages will follow an End of Day Summary message for a particular symbol.
struct EndOfDaySummaryMessage {

    TimeOffset time_offset;
    Symbol symbol;
    TradeDate trade_date;
    OpenInterest open_interest;
    HighPrice high_price;
    LowPrice low_price;
    OpenPrice open_price;
    ClosePrice close_price;
    TotalVolume total_volume;
    BlockVolume block_volume;
    EcrpVolume ecrp_volume;
    SummaryFlags summary_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xBA;

    // parse method
    static EndOfDaySummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfDaySummaryMessage*>(buffer);
    }

    // parse method const
    static const EndOfDaySummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfDaySummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EndOfDaySummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const EndOfDaySummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
