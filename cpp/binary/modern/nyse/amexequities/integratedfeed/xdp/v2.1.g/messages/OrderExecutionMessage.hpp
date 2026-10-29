#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PrintableFlag.hpp"
#include "../types/NumParitySplits.hpp"
#include "../types/DbExecId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

#pragma pack(push, 1)

// An Order Execution message is sent when an order is partially or fully executed.
struct OrderExecutionMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    OrderId order_id;
    TradeId trade_id;
    Price price;
    Volume volume;
    PrintableFlag printable_flag;
    NumParitySplits num_parity_splits;
    DbExecId db_exec_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 103;

    // parse method
    static OrderExecutionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutionMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderExecutionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
