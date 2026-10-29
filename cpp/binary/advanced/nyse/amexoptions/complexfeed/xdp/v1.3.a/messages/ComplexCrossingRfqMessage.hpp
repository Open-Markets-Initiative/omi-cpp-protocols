#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceNs.hpp"
#include "../types/ComplexIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/Side.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Volume2.hpp"
#include "../types/Price.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

namespace xdp_complexfeed = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Complex Crossing Rfq Message
struct complex_crossing_rfq_message {

    struct fields_type {
        xdp_complexfeed::source_time source_time;
        xdp_complexfeed::source_ns source_ns;
        xdp_complexfeed::complex_index complex_index;
        xdp_complexfeed::symbol_seq_num symbol_seq_num;
        xdp_complexfeed::side side;
        xdp_complexfeed::reserved_1 reserved_1;
        xdp_complexfeed::volume_2 volume_2;
        xdp_complexfeed::price price;
    };

    xdp_complexfeed::message_header header = {std::uint16_t(sizeof(xdp_complexfeed::message_header) + sizeof(fields_type)), message_type::enum_type::complex_crossing_rfq_message};

    fields_type fields;

    // parse method
    static complex_crossing_rfq_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_crossing_rfq_message*>(buffer);
    }

    // parse method const
    static const complex_crossing_rfq_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_crossing_rfq_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_crossing_rfq_message::fields_type, source_time) == 0, "unexpected offset of complex_crossing_rfq_message::fields_type::source_time");
static_assert(offsetof(complex_crossing_rfq_message::fields_type, source_ns) == 4, "unexpected offset of complex_crossing_rfq_message::fields_type::source_ns");
static_assert(offsetof(complex_crossing_rfq_message::fields_type, complex_index) == 8, "unexpected offset of complex_crossing_rfq_message::fields_type::complex_index");
static_assert(offsetof(complex_crossing_rfq_message::fields_type, symbol_seq_num) == 12, "unexpected offset of complex_crossing_rfq_message::fields_type::symbol_seq_num");
static_assert(offsetof(complex_crossing_rfq_message::fields_type, side) == 16, "unexpected offset of complex_crossing_rfq_message::fields_type::side");
static_assert(offsetof(complex_crossing_rfq_message::fields_type, reserved_1) == 17, "unexpected offset of complex_crossing_rfq_message::fields_type::reserved_1");
static_assert(offsetof(complex_crossing_rfq_message::fields_type, volume_2) == 18, "unexpected offset of complex_crossing_rfq_message::fields_type::volume_2");
static_assert(offsetof(complex_crossing_rfq_message::fields_type, price) == 20, "unexpected offset of complex_crossing_rfq_message::fields_type::price");
static_assert(sizeof(complex_crossing_rfq_message::fields_type) == 24, "unexpected sizeof complex_crossing_rfq_message::fields_type");
static_assert(sizeof(complex_crossing_rfq_message) == sizeof(xdp_complexfeed::message_header) + 24, "unexpected sizeof complex_crossing_rfq_message");

#pragma pack(pop)
}
