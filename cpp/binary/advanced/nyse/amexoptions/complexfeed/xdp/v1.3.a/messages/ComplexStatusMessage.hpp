#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/ComplexIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/HaltCondition.hpp"
#include "../types/Reserved2.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

namespace xdp_complexfeed = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Complex Status Message
struct complex_status_message {

    struct fields_type {
        xdp_complexfeed::source_time source_time;
        xdp_complexfeed::source_time_ns source_time_ns;
        xdp_complexfeed::complex_index complex_index;
        xdp_complexfeed::symbol_seq_num symbol_seq_num;
        xdp_complexfeed::security_status security_status;
        xdp_complexfeed::halt_condition halt_condition;
        xdp_complexfeed::reserved_2 reserved_2;
    };

    xdp_complexfeed::message_header header = {std::uint16_t(sizeof(xdp_complexfeed::message_header) + sizeof(fields_type)), message_type::enum_type::complex_status_message};

    fields_type fields;

    // parse method
    static complex_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_status_message*>(buffer);
    }

    // parse method const
    static const complex_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_status_message::fields_type, source_time) == 0, "unexpected offset of complex_status_message::fields_type::source_time");
static_assert(offsetof(complex_status_message::fields_type, source_time_ns) == 4, "unexpected offset of complex_status_message::fields_type::source_time_ns");
static_assert(offsetof(complex_status_message::fields_type, complex_index) == 8, "unexpected offset of complex_status_message::fields_type::complex_index");
static_assert(offsetof(complex_status_message::fields_type, symbol_seq_num) == 12, "unexpected offset of complex_status_message::fields_type::symbol_seq_num");
static_assert(offsetof(complex_status_message::fields_type, security_status) == 16, "unexpected offset of complex_status_message::fields_type::security_status");
static_assert(offsetof(complex_status_message::fields_type, halt_condition) == 17, "unexpected offset of complex_status_message::fields_type::halt_condition");
static_assert(offsetof(complex_status_message::fields_type, reserved_2) == 18, "unexpected offset of complex_status_message::fields_type::reserved_2");
static_assert(sizeof(complex_status_message::fields_type) == 20, "unexpected sizeof complex_status_message::fields_type");
static_assert(sizeof(complex_status_message) == sizeof(xdp_complexfeed::message_header) + 20, "unexpected sizeof complex_status_message");

#pragma pack(pop)
}
