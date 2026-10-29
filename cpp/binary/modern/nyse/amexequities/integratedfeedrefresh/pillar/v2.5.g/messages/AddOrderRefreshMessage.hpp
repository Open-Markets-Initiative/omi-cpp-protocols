#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/Side.hpp"
#include "../types/FirmId.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

#pragma pack(push, 1)

// The Add Order Refresh message can be sent in either of two contexts: refresh response or symbol refresh.
struct AddOrderRefreshMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    OrderId order_id;
    Price price;
    Volume volume;
    Side side;
    FirmId firm_id;
    Reserved1 reserved_1;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 106;

    // parse method
    static AddOrderRefreshMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderRefreshMessage*>(buffer);
    }

    // parse method const
    static const AddOrderRefreshMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderRefreshMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderRefreshMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderRefreshMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
