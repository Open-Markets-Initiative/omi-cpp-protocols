// Databento.MarketData.Normalized.Dbn.v1: messages/ErrorMsg.hpp
#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/Err.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v1;

#pragma pack(push, 1)

// Error Msg
struct error_msg {

    struct fields_type {
        dbn_normalized::err err;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::error, {}, {}, {}};

    fields_type fields;

    // parse method
    static error_msg* parse(std::byte* buffer) {
        return reinterpret_cast<error_msg*>(buffer);
    }

    // parse method const
    static const error_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const error_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(error_msg::fields_type, err) == 0, "unexpected offset of error_msg::fields_type::err");
static_assert(sizeof(error_msg::fields_type) == 64, "unexpected sizeof error_msg::fields_type");
static_assert(sizeof(error_msg) == sizeof(dbn_normalized::record_header) + 64, "unexpected sizeof error_msg");

#pragma pack(pop)
}
