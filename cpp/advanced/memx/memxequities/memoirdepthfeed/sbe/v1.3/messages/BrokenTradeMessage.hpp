#pragma once

#include <cstddef>
#include "../structs/SbeHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TradeId.hpp"
#include "../types/OriginalQuantity.hpp"
#include "../types/OriginalPrice.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

// Broken Trade Message
struct broken_trade_message {

    struct fields_type {
        sbe_memoirdepthfeed::timestamp timestamp;
        sbe_memoirdepthfeed::security_id security_id;
        sbe_memoirdepthfeed::trade_id trade_id;
        sbe_memoirdepthfeed::original_quantity original_quantity;
        sbe_memoirdepthfeed::original_price original_price;
    };

    sbe_memoirdepthfeed::sbe_header header = {{}, template_id::enum_type::broken_trade_message, schema_id(2), version(259)};

    fields_type fields;

    // parse method
    static broken_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<broken_trade_message*>(buffer);
    }

    // parse method const
    static const broken_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const broken_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(broken_trade_message::fields_type, timestamp) == 0, "unexpected offset of broken_trade_message::fields_type::timestamp");
static_assert(offsetof(broken_trade_message::fields_type, security_id) == 8, "unexpected offset of broken_trade_message::fields_type::security_id");
static_assert(offsetof(broken_trade_message::fields_type, trade_id) == 10, "unexpected offset of broken_trade_message::fields_type::trade_id");
static_assert(offsetof(broken_trade_message::fields_type, original_quantity) == 18, "unexpected offset of broken_trade_message::fields_type::original_quantity");
static_assert(offsetof(broken_trade_message::fields_type, original_price) == 22, "unexpected offset of broken_trade_message::fields_type::original_price");
static_assert(sizeof(broken_trade_message::fields_type) == 30, "unexpected sizeof broken_trade_message::fields_type");
static_assert(sizeof(broken_trade_message) == sizeof(sbe_memoirdepthfeed::sbe_header) + 30, "unexpected sizeof broken_trade_message");

#pragma pack(pop)
}
