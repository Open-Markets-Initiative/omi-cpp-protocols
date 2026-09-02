#pragma once

#include "../types/OperationalHaltStatus.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

#pragma pack(push, 1)

// The Exchange may suspend trading of one or more securities on IEX for operational reasons and indicates such operational halt using the Operational Halt Status Message.
struct OperationalHaltStatusMessage {

    OperationalHaltStatus operational_halt_status;
    Timestamp timestamp;
    Symbol symbol;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'O';

    // parse method
    static OperationalHaltStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OperationalHaltStatusMessage*>(buffer);
    }

    // parse method const
    static const OperationalHaltStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OperationalHaltStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OperationalHaltStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OperationalHaltStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
