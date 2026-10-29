#pragma once

#include "../types/Stock.hpp"
#include "../types/MarketCode.hpp"
#include "../types/OperationalHaltAction.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Indicates the current operational status of a security to the trading community. An operational halt is specific to the market centre for which it is declared and does not interrupt trading of the instrument on any other market place.
struct OperationalHaltMessage {

    Stock stock;
    MarketCode market_code;
    OperationalHaltAction operational_halt_action;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'h';

    // parse method
    static OperationalHaltMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OperationalHaltMessage*>(buffer);
    }

    // parse method const
    static const OperationalHaltMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OperationalHaltMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OperationalHaltMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OperationalHaltMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
