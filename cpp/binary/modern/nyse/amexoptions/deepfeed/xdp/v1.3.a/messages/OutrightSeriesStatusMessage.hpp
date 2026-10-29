#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/HaltCondition.hpp"
#include "../types/Reserved2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// The Series Status message is used to inform the subscribers of changes in symbol status of an outright symbol.
struct OutrightSeriesStatusMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SymbolSeqNum symbol_seq_num;
    SecurityStatus security_status;
    HaltCondition halt_condition;
    Reserved2 reserved_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 421;

    // parse method
    static OutrightSeriesStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OutrightSeriesStatusMessage*>(buffer);
    }

    // parse method const
    static const OutrightSeriesStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OutrightSeriesStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OutrightSeriesStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OutrightSeriesStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
