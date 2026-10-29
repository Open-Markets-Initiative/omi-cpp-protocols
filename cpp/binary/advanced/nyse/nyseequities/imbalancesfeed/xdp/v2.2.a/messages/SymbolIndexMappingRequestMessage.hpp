#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SourceId.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"
#include "../types/RetransmitMethod.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

namespace xdp_imbalancesfeed = ::nyse::nyseequities::imbalancesfeed::xdp::v2_2_a;

#pragma pack(push, 1)

// Symbol Index Mapping Request Message
struct symbol_index_mapping_request_message {

    struct fields_type {
        xdp_imbalancesfeed::symbol_index symbol_index;
        xdp_imbalancesfeed::source_id source_id;
        xdp_imbalancesfeed::product_id product_id;
        xdp_imbalancesfeed::channel_id channel_id;
        xdp_imbalancesfeed::retransmit_method retransmit_method;
    };

    xdp_imbalancesfeed::message_header header = {std::uint16_t(sizeof(xdp_imbalancesfeed::message_header) + sizeof(fields_type)), message_type::enum_type::symbol_index_mapping_request_message};

    fields_type fields;

    // parse method
    static symbol_index_mapping_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_index_mapping_request_message*>(buffer);
    }

    // parse method const
    static const symbol_index_mapping_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_index_mapping_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_index_mapping_request_message::fields_type, symbol_index) == 0, "unexpected offset of symbol_index_mapping_request_message::fields_type::symbol_index");
static_assert(offsetof(symbol_index_mapping_request_message::fields_type, source_id) == 4, "unexpected offset of symbol_index_mapping_request_message::fields_type::source_id");
static_assert(offsetof(symbol_index_mapping_request_message::fields_type, product_id) == 14, "unexpected offset of symbol_index_mapping_request_message::fields_type::product_id");
static_assert(offsetof(symbol_index_mapping_request_message::fields_type, channel_id) == 15, "unexpected offset of symbol_index_mapping_request_message::fields_type::channel_id");
static_assert(offsetof(symbol_index_mapping_request_message::fields_type, retransmit_method) == 16, "unexpected offset of symbol_index_mapping_request_message::fields_type::retransmit_method");
static_assert(sizeof(symbol_index_mapping_request_message::fields_type) == 17, "unexpected sizeof symbol_index_mapping_request_message::fields_type");
static_assert(sizeof(symbol_index_mapping_request_message) == sizeof(xdp_imbalancesfeed::message_header) + 17, "unexpected sizeof symbol_index_mapping_request_message");

#pragma pack(pop)
}
