#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/CrossShares.hpp"
#include "../types/Stock.hpp"
#include "../types/CrossPrice.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/CrossType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Cross Trade Message
struct cross_trade_message {

    struct fields_type {
        itch_totalview::nanoseconds nanoseconds;
        itch_totalview::cross_shares cross_shares;
        itch_totalview::stock stock;
        itch_totalview::cross_price cross_price;
        itch_totalview::match_number match_number;
        itch_totalview::cross_type cross_type;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::cross_trade_message};

    fields_type fields;

    // parse method
    static cross_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<cross_trade_message*>(buffer);
    }

    // parse method const
    static const cross_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const cross_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(cross_trade_message::fields_type, nanoseconds) == 0, "unexpected offset of cross_trade_message::fields_type::nanoseconds");
static_assert(offsetof(cross_trade_message::fields_type, cross_shares) == 4, "unexpected offset of cross_trade_message::fields_type::cross_shares");
static_assert(offsetof(cross_trade_message::fields_type, stock) == 12, "unexpected offset of cross_trade_message::fields_type::stock");
static_assert(offsetof(cross_trade_message::fields_type, cross_price) == 18, "unexpected offset of cross_trade_message::fields_type::cross_price");
static_assert(offsetof(cross_trade_message::fields_type, match_number) == 22, "unexpected offset of cross_trade_message::fields_type::match_number");
static_assert(offsetof(cross_trade_message::fields_type, cross_type) == 30, "unexpected offset of cross_trade_message::fields_type::cross_type");
static_assert(sizeof(cross_trade_message::fields_type) == 31, "unexpected sizeof cross_trade_message::fields_type");
static_assert(sizeof(cross_trade_message) == sizeof(itch_totalview::message_header) + 31, "unexpected sizeof cross_trade_message");

#pragma pack(pop)
}
