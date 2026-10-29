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

// 
struct ComplexCubeRfqMessage {

    SourceTime source_time;
    SourceNs source_ns;
    ComplexIndex complex_index;
    SymbolSeqNum symbol_seq_num;
    Side side;
    Reserved1 reserved_1;
    Volume2 volume_2;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 472;

    // parse method
    static ComplexCubeRfqMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexCubeRfqMessage*>(buffer);
    }

    // parse method const
    static const ComplexCubeRfqMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexCubeRfqMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexCubeRfqMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ComplexCubeRfqMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
