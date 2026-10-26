#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../bitfields/ModifyOrderFlags.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// This message format is used to publish price/size changes for an existing displayed order on MIAX Pearl Equities book.
struct ModifyOrderMessage {

    Nanoseconds nanoseconds;
    SymbolId symbol_id;
    OrderId order_id;
    Price price;
    Size size;
    ModifyOrderFlags modify_order_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 21;

    // parse method
    static ModifyOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ModifyOrderMessage*>(buffer);
    }

    // parse method const
    static const ModifyOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ModifyOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ModifyOrderMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const ModifyOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
