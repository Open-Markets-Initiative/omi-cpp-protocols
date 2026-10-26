#pragma once

#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

// 
struct OrderMassDelete {

    SecurityId security_id;
    TransactTime transact_time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13103;

    // parse method
    static OrderMassDelete* parse(std::byte* buffer) {
        return reinterpret_cast<OrderMassDelete*>(buffer);
    }

    // parse method const
    static const OrderMassDelete* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderMassDelete*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderMassDelete* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const OrderMassDelete*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
