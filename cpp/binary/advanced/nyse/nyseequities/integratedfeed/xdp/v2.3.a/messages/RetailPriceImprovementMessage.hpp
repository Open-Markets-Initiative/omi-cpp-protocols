#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/RpiIndicator.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

namespace xdp_integratedfeed = ::nyse::nyseequities::integratedfeed::xdp::v2_3_a;

#pragma pack(push, 1)

// Retail Price Improvement Message
struct retail_price_improvement_message {

    struct fields_type {
        xdp_integratedfeed::source_time_ns source_time_ns;
        xdp_integratedfeed::symbol_index symbol_index;
        xdp_integratedfeed::symbol_seq_num symbol_seq_num;
        xdp_integratedfeed::rpi_indicator rpi_indicator;
    };

    xdp_integratedfeed::message_header header = {std::uint16_t(sizeof(xdp_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::retail_price_improvement_message};

    fields_type fields;

    // parse method
    static retail_price_improvement_message* parse(std::byte* buffer) {
        return reinterpret_cast<retail_price_improvement_message*>(buffer);
    }

    // parse method const
    static const retail_price_improvement_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const retail_price_improvement_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(retail_price_improvement_message::fields_type, source_time_ns) == 0, "unexpected offset of retail_price_improvement_message::fields_type::source_time_ns");
static_assert(offsetof(retail_price_improvement_message::fields_type, symbol_index) == 4, "unexpected offset of retail_price_improvement_message::fields_type::symbol_index");
static_assert(offsetof(retail_price_improvement_message::fields_type, symbol_seq_num) == 8, "unexpected offset of retail_price_improvement_message::fields_type::symbol_seq_num");
static_assert(offsetof(retail_price_improvement_message::fields_type, rpi_indicator) == 12, "unexpected offset of retail_price_improvement_message::fields_type::rpi_indicator");
static_assert(sizeof(retail_price_improvement_message::fields_type) == 13, "unexpected sizeof retail_price_improvement_message::fields_type");
static_assert(sizeof(retail_price_improvement_message) == sizeof(xdp_integratedfeed::message_header) + 13, "unexpected sizeof retail_price_improvement_message");

#pragma pack(pop)
}
