#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SourceId.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"

namespace nyse::nyseequities::bbo::pillar::v2_5_b {

namespace pillar_bbo = ::nyse::nyseequities::bbo::pillar::v2_5_b;

#pragma pack(push, 1)

// Refresh Request Message
struct refresh_request_message {

    struct fields_type {
        pillar_bbo::symbol_index symbol_index;
        pillar_bbo::source_id source_id;
        pillar_bbo::product_id product_id;
        pillar_bbo::channel_id channel_id;
    };

    pillar_bbo::message_header header = {std::uint16_t(sizeof(pillar_bbo::message_header) + sizeof(fields_type)), message_type::enum_type::refresh_request_message};

    fields_type fields;

    // parse method
    static refresh_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<refresh_request_message*>(buffer);
    }

    // parse method const
    static const refresh_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const refresh_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(refresh_request_message::fields_type, symbol_index) == 0, "unexpected offset of refresh_request_message::fields_type::symbol_index");
static_assert(offsetof(refresh_request_message::fields_type, source_id) == 4, "unexpected offset of refresh_request_message::fields_type::source_id");
static_assert(offsetof(refresh_request_message::fields_type, product_id) == 14, "unexpected offset of refresh_request_message::fields_type::product_id");
static_assert(offsetof(refresh_request_message::fields_type, channel_id) == 15, "unexpected offset of refresh_request_message::fields_type::channel_id");
static_assert(sizeof(refresh_request_message::fields_type) == 16, "unexpected sizeof refresh_request_message::fields_type");
static_assert(sizeof(refresh_request_message) == sizeof(pillar_bbo::message_header) + 16, "unexpected sizeof refresh_request_message");

#pragma pack(pop)
}
