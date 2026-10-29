#pragma once

#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetails.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published for each new order that was entered in the order book.
struct OrderAddMessage {

    TrdRegTsTimeIn trd_reg_ts_time_in;
    SecurityId security_id;
    OrderDetails order_details;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13100;

    // parse method
    static OrderAddMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderAddMessage*>(buffer);
    }

    // parse method const
    static const OrderAddMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderAddMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderAddMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderAddMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
