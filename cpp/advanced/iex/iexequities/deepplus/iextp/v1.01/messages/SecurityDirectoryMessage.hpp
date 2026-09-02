#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SecurityDirectoryFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/AdjustedPocPrice.hpp"
#include "../types/LuldTier.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

namespace iextp_deepplus = ::iex::iexequities::deepplus::iextp::v1_01;

#pragma pack(push, 1)

// Security Directory Message
struct security_directory_message {

    struct fields_type {
        iextp_deepplus::security_directory_flags security_directory_flags;
        iextp_deepplus::timestamp timestamp;
        iextp_deepplus::symbol symbol;
        iextp_deepplus::round_lot_size round_lot_size;
        iextp_deepplus::adjusted_poc_price adjusted_poc_price;
        iextp_deepplus::luld_tier luld_tier;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::security_directory_message};

    fields_type fields;

    // parse method
    static security_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_directory_message*>(buffer);
    }

    // parse method const
    static const security_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_directory_message::fields_type, security_directory_flags) == 0, "unexpected offset of security_directory_message::fields_type::security_directory_flags");
static_assert(offsetof(security_directory_message::fields_type, timestamp) == 1, "unexpected offset of security_directory_message::fields_type::timestamp");
static_assert(offsetof(security_directory_message::fields_type, symbol) == 9, "unexpected offset of security_directory_message::fields_type::symbol");
static_assert(offsetof(security_directory_message::fields_type, round_lot_size) == 17, "unexpected offset of security_directory_message::fields_type::round_lot_size");
static_assert(offsetof(security_directory_message::fields_type, adjusted_poc_price) == 21, "unexpected offset of security_directory_message::fields_type::adjusted_poc_price");
static_assert(offsetof(security_directory_message::fields_type, luld_tier) == 29, "unexpected offset of security_directory_message::fields_type::luld_tier");
static_assert(sizeof(security_directory_message::fields_type) == 30, "unexpected sizeof security_directory_message::fields_type");
static_assert(sizeof(security_directory_message) == sizeof(message_header) + 30, "unexpected sizeof security_directory_message");

#pragma pack(pop)
}
