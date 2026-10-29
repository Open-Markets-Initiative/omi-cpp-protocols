#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/ComplexIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/HaltCondition.hpp"
#include "../types/Reserved2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// The Complex Status message is used to inform the subscribers of changes in symbol status of a complex symbol.
struct ComplexStatusMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    ComplexIndex complex_index;
    SymbolSeqNum symbol_seq_num;
    SecurityStatus security_status;
    HaltCondition halt_condition;
    Reserved2 reserved_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 433;

    // parse method
    static ComplexStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexStatusMessage*>(buffer);
    }

    // parse method const
    static const ComplexStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ComplexStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
