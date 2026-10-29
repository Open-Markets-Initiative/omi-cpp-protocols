#pragma once

#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetails.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published whenever an existing order is deleted from the order book.
struct OrderDeleteMessage {

    TrdRegTsTimeIn trd_reg_ts_time_in;
    TransactTime transact_time;
    SecurityId security_id;
    OrderDetails order_details;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13102;

    // parse method
    static OrderDeleteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDeleteMessage*>(buffer);
    }

    // parse method const
    static const OrderDeleteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDeleteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderDeleteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderDeleteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
