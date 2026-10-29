#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/OrderType.hpp"
#include "../types/Side.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/ExecFlag.hpp"
#include "../types/OrderCapacity.hpp"
#include "../types/Scope.hpp"
#include "../types/OwnerId.hpp"
#include "../types/Giveup.hpp"
#include "../types/Cmta.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

namespace itch_ordercombofeed = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

#pragma pack(push, 1)

// Complex Strategy Order On Book Message
struct complex_strategy_order_on_book_message {

    struct fields_type {
        itch_ordercombofeed::timestamp timestamp;
        itch_ordercombofeed::strategy_id strategy_id;
        itch_ordercombofeed::order_type order_type;
        itch_ordercombofeed::side side;
        itch_ordercombofeed::price price;
        itch_ordercombofeed::size_type size;
        itch_ordercombofeed::exec_flag exec_flag;
        itch_ordercombofeed::order_capacity order_capacity;
        itch_ordercombofeed::scope scope;
        itch_ordercombofeed::owner_id owner_id;
        itch_ordercombofeed::giveup giveup;
        itch_ordercombofeed::cmta cmta;
    };

    itch_ordercombofeed::message_header header = {std::uint16_t(sizeof(itch_ordercombofeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::complex_strategy_order_on_book_message};

    fields_type fields;

    // parse method
    static complex_strategy_order_on_book_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_strategy_order_on_book_message*>(buffer);
    }

    // parse method const
    static const complex_strategy_order_on_book_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_strategy_order_on_book_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, timestamp) == 0, "unexpected offset of complex_strategy_order_on_book_message::fields_type::timestamp");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, strategy_id) == 6, "unexpected offset of complex_strategy_order_on_book_message::fields_type::strategy_id");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, order_type) == 10, "unexpected offset of complex_strategy_order_on_book_message::fields_type::order_type");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, side) == 11, "unexpected offset of complex_strategy_order_on_book_message::fields_type::side");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, price) == 12, "unexpected offset of complex_strategy_order_on_book_message::fields_type::price");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, size) == 16, "unexpected offset of complex_strategy_order_on_book_message::fields_type::size");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, exec_flag) == 20, "unexpected offset of complex_strategy_order_on_book_message::fields_type::exec_flag");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, order_capacity) == 21, "unexpected offset of complex_strategy_order_on_book_message::fields_type::order_capacity");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, scope) == 22, "unexpected offset of complex_strategy_order_on_book_message::fields_type::scope");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, owner_id) == 23, "unexpected offset of complex_strategy_order_on_book_message::fields_type::owner_id");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, giveup) == 29, "unexpected offset of complex_strategy_order_on_book_message::fields_type::giveup");
static_assert(offsetof(complex_strategy_order_on_book_message::fields_type, cmta) == 35, "unexpected offset of complex_strategy_order_on_book_message::fields_type::cmta");
static_assert(sizeof(complex_strategy_order_on_book_message::fields_type) == 41, "unexpected sizeof complex_strategy_order_on_book_message::fields_type");
static_assert(sizeof(complex_strategy_order_on_book_message) == sizeof(itch_ordercombofeed::message_header) + 41, "unexpected sizeof complex_strategy_order_on_book_message");

#pragma pack(pop)
}
