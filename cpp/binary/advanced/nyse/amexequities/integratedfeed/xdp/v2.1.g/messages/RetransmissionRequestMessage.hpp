#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/BeginSeqNum.hpp"
#include "../types/EndSeqNum.hpp"
#include "../types/SourceId.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

namespace xdp_integratedfeed = ::nyse::amexequities::integratedfeed::xdp::v2_1_g;

#pragma pack(push, 1)

// Retransmission Request Message
struct retransmission_request_message {

    struct fields_type {
        xdp_integratedfeed::begin_seq_num begin_seq_num;
        xdp_integratedfeed::end_seq_num end_seq_num;
        xdp_integratedfeed::source_id source_id;
        xdp_integratedfeed::product_id product_id;
        xdp_integratedfeed::channel_id channel_id;
    };

    xdp_integratedfeed::message_header header = {std::uint16_t(sizeof(xdp_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::retransmission_request_message};

    fields_type fields;

    // parse method
    static retransmission_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<retransmission_request_message*>(buffer);
    }

    // parse method const
    static const retransmission_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const retransmission_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(retransmission_request_message::fields_type, begin_seq_num) == 0, "unexpected offset of retransmission_request_message::fields_type::begin_seq_num");
static_assert(offsetof(retransmission_request_message::fields_type, end_seq_num) == 4, "unexpected offset of retransmission_request_message::fields_type::end_seq_num");
static_assert(offsetof(retransmission_request_message::fields_type, source_id) == 8, "unexpected offset of retransmission_request_message::fields_type::source_id");
static_assert(offsetof(retransmission_request_message::fields_type, product_id) == 18, "unexpected offset of retransmission_request_message::fields_type::product_id");
static_assert(offsetof(retransmission_request_message::fields_type, channel_id) == 19, "unexpected offset of retransmission_request_message::fields_type::channel_id");
static_assert(sizeof(retransmission_request_message::fields_type) == 20, "unexpected sizeof retransmission_request_message::fields_type");
static_assert(sizeof(retransmission_request_message) == sizeof(xdp_integratedfeed::message_header) + 20, "unexpected sizeof retransmission_request_message");

#pragma pack(pop)
}
