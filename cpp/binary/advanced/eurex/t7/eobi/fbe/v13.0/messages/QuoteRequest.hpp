#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastQty.hpp"
#include "../types/Side.hpp"
#include "../types/Pad7.hpp"
#include "../types/TransactTime.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v13_0;

#pragma pack(push, 1)

// Quote Request
struct quote_request {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::side side;
        fbe_eobi::pad7 pad7;
        fbe_eobi::transact_time transact_time;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::quote_request, {}};

    fields_type fields;

    // parse method
    static quote_request* parse(std::byte* buffer) {
        return reinterpret_cast<quote_request*>(buffer);
    }

    // parse method const
    static const quote_request* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_request*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_request::fields_type, security_id) == 0, "unexpected offset of quote_request::fields_type::security_id");
static_assert(offsetof(quote_request::fields_type, last_qty) == 8, "unexpected offset of quote_request::fields_type::last_qty");
static_assert(offsetof(quote_request::fields_type, side) == 16, "unexpected offset of quote_request::fields_type::side");
static_assert(offsetof(quote_request::fields_type, pad7) == 17, "unexpected offset of quote_request::fields_type::pad7");
static_assert(offsetof(quote_request::fields_type, transact_time) == 24, "unexpected offset of quote_request::fields_type::transact_time");
static_assert(sizeof(quote_request::fields_type) == 32, "unexpected sizeof quote_request::fields_type");
static_assert(sizeof(quote_request) == sizeof(fbe_eobi::message_header_comp) + 32, "unexpected sizeof quote_request");

#pragma pack(pop)
}
