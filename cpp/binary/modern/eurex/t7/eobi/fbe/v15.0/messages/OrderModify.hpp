#pragma once

#include "../types/RequestTime.hpp"
#include "../types/TrdRegTsPrevTimePriority.hpp"
#include "../types/PrevPrice.hpp"
#include "../types/PrevDisplayQty.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetailsComp.hpp"
#include "../types/PrevPriceHhiIndicator.hpp"
#include "../types/Pad7.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

#pragma pack(push, 1)

// 
struct OrderModify {

    RequestTime request_time;
    TrdRegTsPrevTimePriority trd_reg_ts_prev_time_priority;
    PrevPrice prev_price;
    PrevDisplayQty prev_display_qty;
    SecurityId security_id;
    OrderDetailsComp order_details_comp;
    PrevPriceHhiIndicator prev_price_hhi_indicator;
    Pad7 pad7;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13101;

    // parse method
    static OrderModify* parse(std::byte* buffer) {
        return reinterpret_cast<OrderModify*>(buffer);
    }

    // parse method const
    static const OrderModify* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderModify*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderModify* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const OrderModify*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
