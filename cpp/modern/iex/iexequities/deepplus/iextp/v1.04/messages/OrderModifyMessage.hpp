#pragma once

#include "../bitfields/ModifyFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OrderIdReference.hpp"
#include "../types/Size.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

#pragma pack(push, 1)

// A displayed order that had its Price, Size, or Priority component changed as a result of user or system action
struct OrderModifyMessage {

    ModifyFlags modify_flags;
    Timestamp timestamp;
    Symbol symbol;
    OrderIdReference order_id_reference;
    Size size;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'M';

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
