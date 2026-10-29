#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/MdControlType.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

// Market Data Control Message
struct market_data_control_message {

    struct fields_type {
        csm_marketdatafeed::md_control_type md_control_type;
    };

    csm_marketdatafeed::message_header header = {{}, template_id::enum_type::market_data_control_message, {}, {}};

    fields_type fields;

    // parse method
    static market_data_control_message* parse(std::byte* buffer) {
        return reinterpret_cast<market_data_control_message*>(buffer);
    }

    // parse method const
    static const market_data_control_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const market_data_control_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(market_data_control_message::fields_type, md_control_type) == 0, "unexpected offset of market_data_control_message::fields_type::md_control_type");
static_assert(sizeof(market_data_control_message::fields_type) == 1, "unexpected sizeof market_data_control_message::fields_type");
static_assert(sizeof(market_data_control_message) == sizeof(csm_marketdatafeed::message_header) + 1, "unexpected sizeof market_data_control_message");

#pragma pack(pop)
}
