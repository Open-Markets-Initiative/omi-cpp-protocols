#pragma once

#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/TrdRegTsPrevTimePriority.hpp"
#include "../types/PrevPrice.hpp"
#include "../types/PrevDisplayQty.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetails.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published if an existing order in the book is modified, whereby the new parameters might cause a change in time priority.
struct OrderModifyMessage {

    TrdRegTsTimeIn trd_reg_ts_time_in;
    TrdRegTsPrevTimePriority trd_reg_ts_prev_time_priority;
    PrevPrice prev_price;
    PrevDisplayQty prev_display_qty;
    SecurityId security_id;
    OrderDetails order_details;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13101;

    // parse method
    static OrderModifyMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderModifyMessage*>(buffer);
    }

    // parse method const
    static const OrderModifyMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderModifyMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderModifyMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderModifyMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
