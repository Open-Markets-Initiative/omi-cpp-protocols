#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastPx.hpp"
#include "../types/LastQty.hpp"
#include "../types/Side.hpp"
#include "../types/CrossRequestType.hpp"
#include "../types/InputSource.hpp"
#include "../types/Pad5.hpp"
#include "../types/TransactTime.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

// Cross Request
struct cross_request {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::last_px last_px;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::side side;
        fbe_eobi::cross_request_type cross_request_type;
        fbe_eobi::input_source input_source;
        fbe_eobi::pad5 pad5;
        fbe_eobi::transact_time transact_time;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::cross_request, {}};

    fields_type fields;

    // parse method
    static cross_request* parse(std::byte* buffer) {
        return reinterpret_cast<cross_request*>(buffer);
    }

    // parse method const
    static const cross_request* parse(const std::byte* buffer) {
        return reinterpret_cast<const cross_request*>(buffer);
    }

};

// layout verification
static_assert(offsetof(cross_request::fields_type, security_id) == 0, "unexpected offset of cross_request::fields_type::security_id");
static_assert(offsetof(cross_request::fields_type, last_px) == 8, "unexpected offset of cross_request::fields_type::last_px");
static_assert(offsetof(cross_request::fields_type, last_qty) == 16, "unexpected offset of cross_request::fields_type::last_qty");
static_assert(offsetof(cross_request::fields_type, side) == 24, "unexpected offset of cross_request::fields_type::side");
static_assert(offsetof(cross_request::fields_type, cross_request_type) == 25, "unexpected offset of cross_request::fields_type::cross_request_type");
static_assert(offsetof(cross_request::fields_type, input_source) == 26, "unexpected offset of cross_request::fields_type::input_source");
static_assert(offsetof(cross_request::fields_type, pad5) == 27, "unexpected offset of cross_request::fields_type::pad5");
static_assert(offsetof(cross_request::fields_type, transact_time) == 32, "unexpected offset of cross_request::fields_type::transact_time");
static_assert(sizeof(cross_request::fields_type) == 40, "unexpected sizeof cross_request::fields_type");
static_assert(sizeof(cross_request) == sizeof(fbe_eobi::message_header_comp) + 40, "unexpected sizeof cross_request");

#pragma pack(pop)
}
