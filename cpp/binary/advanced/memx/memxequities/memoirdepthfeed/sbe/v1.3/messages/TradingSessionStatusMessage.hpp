#pragma once

#include <cstddef>
#include "../structs/SbeHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TradingSession.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

// Trading Session Status Message
struct trading_session_status_message {

    struct fields_type {
        sbe_memoirdepthfeed::timestamp timestamp;
        sbe_memoirdepthfeed::trading_session trading_session;
    };

    sbe_memoirdepthfeed::sbe_header header = {{}, template_id::enum_type::trading_session_status_message, schema_id(2), version(259)};

    fields_type fields;

    // parse method
    static trading_session_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<trading_session_status_message*>(buffer);
    }

    // parse method const
    static const trading_session_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_session_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_session_status_message::fields_type, timestamp) == 0, "unexpected offset of trading_session_status_message::fields_type::timestamp");
static_assert(offsetof(trading_session_status_message::fields_type, trading_session) == 8, "unexpected offset of trading_session_status_message::fields_type::trading_session");
static_assert(sizeof(trading_session_status_message::fields_type) == 9, "unexpected sizeof trading_session_status_message::fields_type");
static_assert(sizeof(trading_session_status_message) == sizeof(sbe_memoirdepthfeed::sbe_header) + 9, "unexpected sizeof trading_session_status_message");

#pragma pack(pop)
}
