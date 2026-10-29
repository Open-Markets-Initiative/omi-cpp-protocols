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
#include "../types/NumParitySplits.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

#pragma pack(push, 1)

// The Add Order Refresh message can be sent in either of two contexts: 1) If a client sends a Refresh Request to the Request Controller, an Add Order Refresh message is sent over the Refresh channels as part of the refresh response for every order currently sitting on the book. 2) If NYSE Operations refreshes a symbol, a Symbol Clear message is published, followed by a full refresh. The refresh includes an Add Order Refresh message for every order currently sitting on the book of the symbol.
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
    NumParitySplits num_parity_splits;

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
