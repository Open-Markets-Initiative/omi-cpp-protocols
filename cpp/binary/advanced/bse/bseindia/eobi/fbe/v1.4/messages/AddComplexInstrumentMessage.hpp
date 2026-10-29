#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecuritySubType.hpp"
#include "../types/ProductComplex.hpp"
#include "../types/ImpliedMarketIndicator.hpp"
#include "../types/NoLegs.hpp"
#include "../types/Pad1.hpp"
#include "../structs/InstrmtLegGrp.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Add Complex Instrument Message
struct add_complex_instrument_message {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_sub_type security_sub_type;
        fbe_eobi::product_complex product_complex;
        fbe_eobi::implied_market_indicator implied_market_indicator;
        fbe_eobi::no_legs no_legs;
        fbe_eobi::pad_1 pad_1;
        fbe_eobi::instrmt_leg_grp instrmt_leg_grp;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::add_complex_instrument_message, {}};

    fields_type fields;

    // parse method
    static add_complex_instrument_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_complex_instrument_message*>(buffer);
    }

    // parse method const
    static const add_complex_instrument_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_complex_instrument_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_complex_instrument_message::fields_type, security_id) == 0, "unexpected offset of add_complex_instrument_message::fields_type::security_id");
static_assert(offsetof(add_complex_instrument_message::fields_type, transact_time) == 8, "unexpected offset of add_complex_instrument_message::fields_type::transact_time");
static_assert(offsetof(add_complex_instrument_message::fields_type, security_sub_type) == 16, "unexpected offset of add_complex_instrument_message::fields_type::security_sub_type");
static_assert(offsetof(add_complex_instrument_message::fields_type, product_complex) == 20, "unexpected offset of add_complex_instrument_message::fields_type::product_complex");
static_assert(offsetof(add_complex_instrument_message::fields_type, implied_market_indicator) == 21, "unexpected offset of add_complex_instrument_message::fields_type::implied_market_indicator");
static_assert(offsetof(add_complex_instrument_message::fields_type, no_legs) == 22, "unexpected offset of add_complex_instrument_message::fields_type::no_legs");
static_assert(offsetof(add_complex_instrument_message::fields_type, pad_1) == 23, "unexpected offset of add_complex_instrument_message::fields_type::pad_1");
static_assert(offsetof(add_complex_instrument_message::fields_type, instrmt_leg_grp) == 24, "unexpected offset of add_complex_instrument_message::fields_type::instrmt_leg_grp");
static_assert(sizeof(add_complex_instrument_message::fields_type) == 40, "unexpected sizeof add_complex_instrument_message::fields_type");
static_assert(sizeof(add_complex_instrument_message) == sizeof(fbe_eobi::message_header) + 40, "unexpected sizeof add_complex_instrument_message");

#pragma pack(pop)
}
