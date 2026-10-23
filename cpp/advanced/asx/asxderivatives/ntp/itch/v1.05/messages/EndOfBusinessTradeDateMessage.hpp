#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/EventCode.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// End Of Business Trade Date Message
struct end_of_business_trade_date_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::event_code event_code;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::end_of_business_trade_date_message};

    fields_type fields;

    // parse method
    static end_of_business_trade_date_message* parse(std::byte* buffer) {
        return reinterpret_cast<end_of_business_trade_date_message*>(buffer);
    }

    // parse method const
    static const end_of_business_trade_date_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const end_of_business_trade_date_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(end_of_business_trade_date_message::fields_type, nanoseconds) == 0, "unexpected offset of end_of_business_trade_date_message::fields_type::nanoseconds");
static_assert(offsetof(end_of_business_trade_date_message::fields_type, trade_date) == 4, "unexpected offset of end_of_business_trade_date_message::fields_type::trade_date");
static_assert(offsetof(end_of_business_trade_date_message::fields_type, event_code) == 6, "unexpected offset of end_of_business_trade_date_message::fields_type::event_code");
static_assert(sizeof(end_of_business_trade_date_message::fields_type) == 7, "unexpected sizeof end_of_business_trade_date_message::fields_type");
static_assert(sizeof(end_of_business_trade_date_message) == sizeof(itch_ntp::message_header) + 7, "unexpected sizeof end_of_business_trade_date_message");

#pragma pack(pop)
}
