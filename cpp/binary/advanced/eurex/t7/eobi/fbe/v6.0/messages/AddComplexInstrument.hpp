#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecuritySubType.hpp"
#include "../types/ProductComplex.hpp"
#include "../types/ImpliedMarketIndicator.hpp"
#include "../types/NoLegs.hpp"
#include "../types/Pad1.hpp"
#include "../structs/InstrmtLegGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v6_0;

#pragma pack(push, 1)

// Add Complex Instrument
struct add_complex_instrument {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_sub_type security_sub_type;
        fbe_eobi::product_complex product_complex;
        fbe_eobi::implied_market_indicator implied_market_indicator;
        fbe_eobi::no_legs no_legs;
        fbe_eobi::pad1 pad1;
        fbe_eobi::instrmt_leg_grp_comp instrmt_leg_grp_comp;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::add_complex_instrument, {}};

    fields_type fields;

    // parse method
    static add_complex_instrument* parse(std::byte* buffer) {
        return reinterpret_cast<add_complex_instrument*>(buffer);
    }

    // parse method const
    static const add_complex_instrument* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_complex_instrument*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_complex_instrument::fields_type, security_id) == 0, "unexpected offset of add_complex_instrument::fields_type::security_id");
static_assert(offsetof(add_complex_instrument::fields_type, transact_time) == 8, "unexpected offset of add_complex_instrument::fields_type::transact_time");
static_assert(offsetof(add_complex_instrument::fields_type, security_sub_type) == 16, "unexpected offset of add_complex_instrument::fields_type::security_sub_type");
static_assert(offsetof(add_complex_instrument::fields_type, product_complex) == 20, "unexpected offset of add_complex_instrument::fields_type::product_complex");
static_assert(offsetof(add_complex_instrument::fields_type, implied_market_indicator) == 21, "unexpected offset of add_complex_instrument::fields_type::implied_market_indicator");
static_assert(offsetof(add_complex_instrument::fields_type, no_legs) == 22, "unexpected offset of add_complex_instrument::fields_type::no_legs");
static_assert(offsetof(add_complex_instrument::fields_type, pad1) == 23, "unexpected offset of add_complex_instrument::fields_type::pad1");
static_assert(offsetof(add_complex_instrument::fields_type, instrmt_leg_grp_comp) == 24, "unexpected offset of add_complex_instrument::fields_type::instrmt_leg_grp_comp");
static_assert(sizeof(add_complex_instrument::fields_type) == 48, "unexpected sizeof add_complex_instrument::fields_type");
static_assert(sizeof(add_complex_instrument) == sizeof(fbe_eobi::message_header_comp) + 48, "unexpected sizeof add_complex_instrument");

#pragma pack(pop)
}
