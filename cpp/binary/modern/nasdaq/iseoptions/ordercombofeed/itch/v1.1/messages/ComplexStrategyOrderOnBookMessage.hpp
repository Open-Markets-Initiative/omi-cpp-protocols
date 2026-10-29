#pragma once

#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/OrderType.hpp"
#include "../types/Side.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/ExecFlag.hpp"
#include "../types/OrderCapacity.hpp"
#include "../types/Scope.hpp"
#include "../types/OwnerId.hpp"
#include "../types/Giveup.hpp"
#include "../types/Cmta.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

#pragma pack(push, 1)

// An Order on Book message is generated for all the following situations whenever an order free from any display restrictions is reported by the matching engine. In all such cases the order size to be displayed is as reported by the matching engine
struct ComplexStrategyOrderOnBookMessage {

    Timestamp timestamp;
    StrategyId strategy_id;
    OrderType order_type;
    Side side;
    Price price;
    Size size;
    ExecFlag exec_flag;
    OrderCapacity order_capacity;
    Scope scope;
    OwnerId owner_id;
    Giveup giveup;
    Cmta cmta;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'L';

    // parse method
    static ComplexStrategyOrderOnBookMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexStrategyOrderOnBookMessage*>(buffer);
    }

    // parse method const
    static const ComplexStrategyOrderOnBookMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexStrategyOrderOnBookMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexStrategyOrderOnBookMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ComplexStrategyOrderOnBookMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
