// Databento.MarketData.Normalized.Dbn.v1: messages/SystemMsg.hpp
#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/Msg.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v1;

#pragma pack(push, 1)

// System Msg
struct system_msg {

    struct fields_type {
        dbn_normalized::msg msg;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::system, {}, {}, {}};

    fields_type fields;

    // parse method
    static system_msg* parse(std::byte* buffer) {
        return reinterpret_cast<system_msg*>(buffer);
    }

    // parse method const
    static const system_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const system_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(system_msg::fields_type, msg) == 0, "unexpected offset of system_msg::fields_type::msg");
static_assert(sizeof(system_msg::fields_type) == 64, "unexpected sizeof system_msg::fields_type");
static_assert(sizeof(system_msg) == sizeof(dbn_normalized::record_header) + 64, "unexpected sizeof system_msg");

#pragma pack(pop)
}
