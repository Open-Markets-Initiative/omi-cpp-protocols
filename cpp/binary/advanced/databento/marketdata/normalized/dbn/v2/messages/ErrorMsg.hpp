// Databento.MarketData.Normalized.Dbn.v2: messages/ErrorMsg.hpp
#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/Err.hpp"
#include "../types/ErrorCode.hpp"
#include "../types/IsLast.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v2;

#pragma pack(push, 1)

// Error Msg
struct error_msg {

    struct fields_type {
        dbn_normalized::err err;
        dbn_normalized::error_code error_code;
        dbn_normalized::is_last is_last;
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
static_assert(offsetof(error_msg::fields_type, error_code) == 302, "unexpected offset of error_msg::fields_type::error_code");
static_assert(offsetof(error_msg::fields_type, is_last) == 303, "unexpected offset of error_msg::fields_type::is_last");
static_assert(sizeof(error_msg::fields_type) == 304, "unexpected sizeof error_msg::fields_type");
static_assert(sizeof(error_msg) == sizeof(dbn_normalized::record_header) + 304, "unexpected sizeof error_msg");

#pragma pack(pop)
}
