#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/EquilibriumPrice.hpp"
#include "../types/MatchedQuantity.hpp"
#include "../types/BidQuantity.hpp"
#include "../types/AskQuantity.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Equilibrium Price Message
struct equilibrium_price_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::equilibrium_price equilibrium_price;
        itch_ntp::matched_quantity matched_quantity;
        itch_ntp::bid_quantity bid_quantity;
        itch_ntp::ask_quantity ask_quantity;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::equilibrium_price_message};

    fields_type fields;

    // parse method
    static equilibrium_price_message* parse(std::byte* buffer) {
        return reinterpret_cast<equilibrium_price_message*>(buffer);
    }

    // parse method const
    static const equilibrium_price_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const equilibrium_price_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(equilibrium_price_message::fields_type, nanoseconds) == 0, "unexpected offset of equilibrium_price_message::fields_type::nanoseconds");
static_assert(offsetof(equilibrium_price_message::fields_type, trade_date) == 4, "unexpected offset of equilibrium_price_message::fields_type::trade_date");
static_assert(offsetof(equilibrium_price_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of equilibrium_price_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(equilibrium_price_message::fields_type, equilibrium_price) == 10, "unexpected offset of equilibrium_price_message::fields_type::equilibrium_price");
static_assert(offsetof(equilibrium_price_message::fields_type, matched_quantity) == 18, "unexpected offset of equilibrium_price_message::fields_type::matched_quantity");
static_assert(offsetof(equilibrium_price_message::fields_type, bid_quantity) == 26, "unexpected offset of equilibrium_price_message::fields_type::bid_quantity");
static_assert(offsetof(equilibrium_price_message::fields_type, ask_quantity) == 34, "unexpected offset of equilibrium_price_message::fields_type::ask_quantity");
static_assert(sizeof(equilibrium_price_message::fields_type) == 42, "unexpected sizeof equilibrium_price_message::fields_type");
static_assert(sizeof(equilibrium_price_message) == sizeof(itch_ntp::message_header) + 42, "unexpected sizeof equilibrium_price_message");

#pragma pack(pop)
}
