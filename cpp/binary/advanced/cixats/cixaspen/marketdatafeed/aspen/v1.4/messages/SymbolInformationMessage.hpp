#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SymbolId.hpp"
#include "../types/Symbol.hpp"
#include "../types/ListingMarket.hpp"
#include "../types/BoardLotSize.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

namespace aspen_marketdatafeed = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

#pragma pack(push, 1)

// Symbol Information Message
struct symbol_information_message {

    struct fields_type {
        aspen_marketdatafeed::timestamp timestamp;
        aspen_marketdatafeed::symbol_id symbol_id;
        aspen_marketdatafeed::symbol symbol;
        aspen_marketdatafeed::listing_market listing_market;
        aspen_marketdatafeed::board_lot_size board_lot_size;
    };

    aspen_marketdatafeed::message_header header = {std::uint16_t(sizeof(aspen_marketdatafeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::symbol_information_message};

    fields_type fields;

    // parse method
    static symbol_information_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_information_message*>(buffer);
    }

    // parse method const
    static const symbol_information_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_information_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_information_message::fields_type, timestamp) == 0, "unexpected offset of symbol_information_message::fields_type::timestamp");
static_assert(offsetof(symbol_information_message::fields_type, symbol_id) == 8, "unexpected offset of symbol_information_message::fields_type::symbol_id");
static_assert(offsetof(symbol_information_message::fields_type, symbol) == 10, "unexpected offset of symbol_information_message::fields_type::symbol");
static_assert(offsetof(symbol_information_message::fields_type, listing_market) == 21, "unexpected offset of symbol_information_message::fields_type::listing_market");
static_assert(offsetof(symbol_information_message::fields_type, board_lot_size) == 22, "unexpected offset of symbol_information_message::fields_type::board_lot_size");
static_assert(sizeof(symbol_information_message::fields_type) == 26, "unexpected sizeof symbol_information_message::fields_type");
static_assert(sizeof(symbol_information_message) == sizeof(aspen_marketdatafeed::message_header) + 26, "unexpected sizeof symbol_information_message");

#pragma pack(pop)
}
