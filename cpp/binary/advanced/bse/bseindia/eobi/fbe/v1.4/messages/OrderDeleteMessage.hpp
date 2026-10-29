#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetails.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Order Delete Message
struct order_delete_message {

    struct fields_type {
        fbe_eobi::trd_reg_ts_time_in trd_reg_ts_time_in;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_id security_id;
        fbe_eobi::order_details order_details;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::order_delete_message, {}};

    fields_type fields;

    // parse method
    static order_delete_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_delete_message*>(buffer);
    }

    // parse method const
    static const order_delete_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_delete_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_delete_message::fields_type, trd_reg_ts_time_in) == 0, "unexpected offset of order_delete_message::fields_type::trd_reg_ts_time_in");
static_assert(offsetof(order_delete_message::fields_type, transact_time) == 8, "unexpected offset of order_delete_message::fields_type::transact_time");
static_assert(offsetof(order_delete_message::fields_type, security_id) == 16, "unexpected offset of order_delete_message::fields_type::security_id");
static_assert(offsetof(order_delete_message::fields_type, order_details) == 24, "unexpected offset of order_delete_message::fields_type::order_details");
static_assert(sizeof(order_delete_message::fields_type) == 56, "unexpected sizeof order_delete_message::fields_type");
static_assert(sizeof(order_delete_message) == sizeof(fbe_eobi::message_header) + 56, "unexpected sizeof order_delete_message");

#pragma pack(pop)
}
