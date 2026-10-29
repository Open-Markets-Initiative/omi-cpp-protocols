#pragma once

#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetailsComp.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

#pragma pack(push, 1)

// 
struct OrderDelete {

    TrdRegTsTimeIn trd_reg_ts_time_in;
    TransactTime transact_time;
    SecurityId security_id;
    OrderDetailsComp order_details_comp;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13102;

    // parse method
    static OrderDelete* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDelete*>(buffer);
    }

    // parse method const
    static const OrderDelete* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDelete*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderDelete* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const OrderDelete*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
