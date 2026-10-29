#pragma once

#include "../types/Side.hpp"
#include "../types/Pad7.hpp"
#include "../types/Price.hpp"
#include "../types/TrdRegTsTimePriority.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/Pad4.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published whenever a visible order is fully executed at its displayed price.
struct FullOrderExecutionMessage {

    Side side;
    Pad7 pad_7;
    Price price;
    TrdRegTsTimePriority trd_reg_ts_time_priority;
    SecurityId security_id;
    TrdMatchId trd_match_id;
    Pad4 pad_4;
    LastQty last_qty;
    LastPx last_px;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13104;

    // parse method
    static FullOrderExecutionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<FullOrderExecutionMessage*>(buffer);
    }

    // parse method const
    static const FullOrderExecutionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const FullOrderExecutionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const FullOrderExecutionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const FullOrderExecutionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
