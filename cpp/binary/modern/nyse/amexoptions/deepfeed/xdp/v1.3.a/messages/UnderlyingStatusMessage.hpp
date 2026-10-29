#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/UnderlyingIndex.hpp"
#include "../types/UnderlyingSeqNum.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/HaltCondition.hpp"
#include "../types/Reserved2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// The Underlying Status message is used to inform the subscribers of changes in the status of an Underlying symbol.
struct UnderlyingStatusMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    UnderlyingIndex underlying_index;
    UnderlyingSeqNum underlying_seq_num;
    SecurityStatus security_status;
    HaltCondition halt_condition;
    Reserved2 reserved_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 419;

    // parse method
    static UnderlyingStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingStatusMessage*>(buffer);
    }

    // parse method const
    static const UnderlyingStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const UnderlyingStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const UnderlyingStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
