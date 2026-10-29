#pragma once

#include "../types/SecurityId.hpp"
#include "../types/UpperExecLimit.hpp"
#include "../types/LowerExecLimit.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published whenever there is a change in the limit price protection range of the instrument.
struct LppRangeMessage {

    SecurityId security_id;
    UpperExecLimit upper_exec_limit;
    LowerExecLimit lower_exec_limit;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13204;

    // parse method
    static LppRangeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LppRangeMessage*>(buffer);
    }

    // parse method const
    static const LppRangeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LppRangeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LppRangeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const LppRangeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
