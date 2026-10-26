#pragma once

#include "../types/Timestamp.hpp"
#include "../types/Instrument.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/Volume.hpp"
#include "../types/VolumeOnbookOnly.hpp"
#include "../types/Vwap.hpp"
#include "../types/VwapOnbookOnly.hpp"
#include "../types/NumberOfTrades.hpp"
#include "../types/NumberOfTradesOnbookOnly.hpp"
#include "../types/Turnover.hpp"
#include "../types/TurnoverOnbookOnly.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

#pragma pack(push, 1)

// Contains a set of statistics that are updated frequently, usually as a result of executions.
struct StatisticsMessage {

    Timestamp timestamp;
    Instrument instrument;
    SourceVenue source_venue;
    Volume volume;
    VolumeOnbookOnly volume_onbook_only;
    Vwap vwap;
    VwapOnbookOnly vwap_onbook_only;
    NumberOfTrades number_of_trades;
    NumberOfTradesOnbookOnly number_of_trades_onbook_only;
    Turnover turnover;
    TurnoverOnbookOnly turnover_onbook_only;

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
