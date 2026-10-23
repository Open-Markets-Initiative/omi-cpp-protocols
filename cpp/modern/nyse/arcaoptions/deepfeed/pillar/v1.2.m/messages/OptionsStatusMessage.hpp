#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/SeriesStatus.hpp"
#include "../types/MarketState.hpp"
#include "../types/OptionsStatusHaltCondition.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Informs clients of changes in the status of a specific option outright series and complex series, such as Trading Halts.
struct OptionsStatusMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    SeriesStatus series_status;
    MarketState market_state;
    OptionsStatusHaltCondition options_status_halt_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 51;

    // parse method
    static OptionsStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsStatusMessage*>(buffer);
    }

    // parse method const
    static const OptionsStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
