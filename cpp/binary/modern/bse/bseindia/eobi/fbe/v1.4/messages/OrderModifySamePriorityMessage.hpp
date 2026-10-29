#pragma once

#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/TransactTime.hpp"
#include "../types/PrevDisplayQty.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetails.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published if the time priority of an existing order is not changed.
struct OrderModifySamePriorityMessage {

    TrdRegTsTimeIn trd_reg_ts_time_in;
    TransactTime transact_time;
    PrevDisplayQty prev_display_qty;
    SecurityId security_id;
    OrderDetails order_details;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13106;

    // parse method
    static OrderModifySamePriorityMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderModifySamePriorityMessage*>(buffer);
    }

    // parse method const
    static const OrderModifySamePriorityMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderModifySamePriorityMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderModifySamePriorityMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderModifySamePriorityMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
