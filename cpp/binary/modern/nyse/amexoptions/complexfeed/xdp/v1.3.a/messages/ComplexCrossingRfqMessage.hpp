#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceNs.hpp"
#include "../types/ComplexIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/Side.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Volume2.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// The Complex Crossing RFQ (Request for Quote) message is sent out in the event of a COA auction on a complex order.
struct ComplexCrossingRfqMessage {

    SourceTime source_time;
    SourceNs source_ns;
    ComplexIndex complex_index;
    SymbolSeqNum symbol_seq_num;
    Side side;
    Reserved1 reserved_1;
    Volume2 volume_2;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 429;

    // parse method
    static ComplexCrossingRfqMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexCrossingRfqMessage*>(buffer);
    }

    // parse method const
    static const ComplexCrossingRfqMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexCrossingRfqMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexCrossingRfqMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ComplexCrossingRfqMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
