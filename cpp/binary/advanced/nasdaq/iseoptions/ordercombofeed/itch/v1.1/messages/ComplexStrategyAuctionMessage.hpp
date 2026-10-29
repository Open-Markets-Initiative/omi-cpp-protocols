#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/AuctionId.hpp"
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
#include "../types/AuctionEvent.hpp"
#include "../types/AuctionType.hpp"
#include "../types/NumberOfResponses.hpp"
#include "../types/ResponsePrice.hpp"
#include "../types/ResponseSize.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

namespace itch_ordercombofeed = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

#pragma pack(push, 1)
struct complex_strategy_auction_message_auction_response_entry {
    itch_ordercombofeed::response_price response_price;
    itch_ordercombofeed::response_size response_size;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Complex Strategy Auction Message
struct complex_strategy_auction_message {

    struct fields_type {
        itch_ordercombofeed::timestamp timestamp;
        itch_ordercombofeed::strategy_id strategy_id;
        itch_ordercombofeed::auction_id auction_id;
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
        itch_ordercombofeed::auction_event auction_event;
        itch_ordercombofeed::auction_type auction_type;
        itch_ordercombofeed::number_of_responses number_of_responses;
    };

    itch_ordercombofeed::message_header header = {std::uint16_t(sizeof(itch_ordercombofeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::complex_strategy_auction_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(itch_ordercombofeed::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return (sz + 2) == sizeof(itch_ordercombofeed::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + ((sz + 2) - sizeof(itch_ordercombofeed::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    external_count_iterator<complex_strategy_auction_message_auction_response_entry> auction_response() const {
        return { tail_begin(), fields.number_of_responses.get().value(), tail_end() };
    }


    // parse method
    static complex_strategy_auction_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_strategy_auction_message*>(buffer);
    }

    // parse method const
    static const complex_strategy_auction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_strategy_auction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_strategy_auction_message::fields_type, timestamp) == 0, "unexpected offset of complex_strategy_auction_message::fields_type::timestamp");
static_assert(offsetof(complex_strategy_auction_message::fields_type, strategy_id) == 6, "unexpected offset of complex_strategy_auction_message::fields_type::strategy_id");
static_assert(offsetof(complex_strategy_auction_message::fields_type, auction_id) == 10, "unexpected offset of complex_strategy_auction_message::fields_type::auction_id");
static_assert(offsetof(complex_strategy_auction_message::fields_type, order_type) == 14, "unexpected offset of complex_strategy_auction_message::fields_type::order_type");
static_assert(offsetof(complex_strategy_auction_message::fields_type, side) == 15, "unexpected offset of complex_strategy_auction_message::fields_type::side");
static_assert(offsetof(complex_strategy_auction_message::fields_type, price) == 16, "unexpected offset of complex_strategy_auction_message::fields_type::price");
static_assert(offsetof(complex_strategy_auction_message::fields_type, size) == 20, "unexpected offset of complex_strategy_auction_message::fields_type::size");
static_assert(offsetof(complex_strategy_auction_message::fields_type, exec_flag) == 24, "unexpected offset of complex_strategy_auction_message::fields_type::exec_flag");
static_assert(offsetof(complex_strategy_auction_message::fields_type, order_capacity) == 25, "unexpected offset of complex_strategy_auction_message::fields_type::order_capacity");
static_assert(offsetof(complex_strategy_auction_message::fields_type, scope) == 26, "unexpected offset of complex_strategy_auction_message::fields_type::scope");
static_assert(offsetof(complex_strategy_auction_message::fields_type, owner_id) == 27, "unexpected offset of complex_strategy_auction_message::fields_type::owner_id");
static_assert(offsetof(complex_strategy_auction_message::fields_type, giveup) == 33, "unexpected offset of complex_strategy_auction_message::fields_type::giveup");
static_assert(offsetof(complex_strategy_auction_message::fields_type, cmta) == 39, "unexpected offset of complex_strategy_auction_message::fields_type::cmta");
static_assert(offsetof(complex_strategy_auction_message::fields_type, auction_event) == 45, "unexpected offset of complex_strategy_auction_message::fields_type::auction_event");
static_assert(offsetof(complex_strategy_auction_message::fields_type, auction_type) == 46, "unexpected offset of complex_strategy_auction_message::fields_type::auction_type");
static_assert(offsetof(complex_strategy_auction_message::fields_type, number_of_responses) == 47, "unexpected offset of complex_strategy_auction_message::fields_type::number_of_responses");
static_assert(sizeof(complex_strategy_auction_message::fields_type) == 48, "unexpected sizeof complex_strategy_auction_message::fields_type");

#pragma pack(pop)
}

#include "details/ComplexStrategyAuctionMessageWriter.hpp"
#include "details/ComplexStrategyAuctionMessageReader.hpp"
