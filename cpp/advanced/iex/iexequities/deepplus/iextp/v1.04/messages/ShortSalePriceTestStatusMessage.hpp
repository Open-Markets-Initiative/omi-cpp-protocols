#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ShortSalePriceTestStatus.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/Detail.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

namespace iextp_deepplus = ::iex::iexequities::deepplus::iextp::v1_04;

#pragma pack(push, 1)

// Short Sale Price Test Status Message
struct short_sale_price_test_status_message {

    struct fields_type {
        iextp_deepplus::short_sale_price_test_status short_sale_price_test_status;
        iextp_deepplus::timestamp timestamp;
        iextp_deepplus::symbol symbol;
        iextp_deepplus::detail detail;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::short_sale_price_test_status_message};

    fields_type fields;

    // parse method
    static short_sale_price_test_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<short_sale_price_test_status_message*>(buffer);
    }

    // parse method const
    static const short_sale_price_test_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const short_sale_price_test_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(short_sale_price_test_status_message::fields_type, short_sale_price_test_status) == 0, "unexpected offset of short_sale_price_test_status_message::fields_type::short_sale_price_test_status");
static_assert(offsetof(short_sale_price_test_status_message::fields_type, timestamp) == 1, "unexpected offset of short_sale_price_test_status_message::fields_type::timestamp");
static_assert(offsetof(short_sale_price_test_status_message::fields_type, symbol) == 9, "unexpected offset of short_sale_price_test_status_message::fields_type::symbol");
static_assert(offsetof(short_sale_price_test_status_message::fields_type, detail) == 17, "unexpected offset of short_sale_price_test_status_message::fields_type::detail");
static_assert(sizeof(short_sale_price_test_status_message::fields_type) == 18, "unexpected sizeof short_sale_price_test_status_message::fields_type");
static_assert(sizeof(short_sale_price_test_status_message) == sizeof(message_header) + 18, "unexpected sizeof short_sale_price_test_status_message");

#pragma pack(pop)
}
