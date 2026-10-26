#pragma once

#include <cstddef>
#include "../structs/SbeHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/SecurityTradingStatusReason.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

// Security Trading Status Message
struct security_trading_status_message {

    struct fields_type {
        sbe_memoirdepthfeed::timestamp timestamp;
        sbe_memoirdepthfeed::security_id security_id;
        sbe_memoirdepthfeed::security_trading_status security_trading_status;
        sbe_memoirdepthfeed::security_trading_status_reason security_trading_status_reason;
    };

    sbe_memoirdepthfeed::sbe_header header = {{}, template_id::enum_type::security_trading_status_message, schema_id(2), version(259)};

    fields_type fields;

    // parse method
    static security_trading_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_trading_status_message*>(buffer);
    }

    // parse method const
    static const security_trading_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_trading_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_trading_status_message::fields_type, timestamp) == 0, "unexpected offset of security_trading_status_message::fields_type::timestamp");
static_assert(offsetof(security_trading_status_message::fields_type, security_id) == 8, "unexpected offset of security_trading_status_message::fields_type::security_id");
static_assert(offsetof(security_trading_status_message::fields_type, security_trading_status) == 10, "unexpected offset of security_trading_status_message::fields_type::security_trading_status");
static_assert(offsetof(security_trading_status_message::fields_type, security_trading_status_reason) == 11, "unexpected offset of security_trading_status_message::fields_type::security_trading_status_reason");
static_assert(sizeof(security_trading_status_message::fields_type) == 12, "unexpected sizeof security_trading_status_message::fields_type");
static_assert(sizeof(security_trading_status_message) == sizeof(sbe_memoirdepthfeed::sbe_header) + 12, "unexpected sizeof security_trading_status_message");

#pragma pack(pop)
}
