#pragma once

#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published when the order book is expected to be emptied.
struct OrderMassDeleteMessage {

    SecurityId security_id;
    TransactTime transact_time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13103;

    // parse method
    static OrderMassDeleteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderMassDeleteMessage*>(buffer);
    }

    // parse method const
    static const OrderMassDeleteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderMassDeleteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderMassDeleteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderMassDeleteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
