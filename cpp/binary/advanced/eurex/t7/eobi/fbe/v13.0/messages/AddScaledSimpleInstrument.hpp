#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityDesc.hpp"
#include "../types/SecurityType.hpp"
#include "../types/Pad1.hpp"
#include "../types/QuantityScalingFactor.hpp"
#include "../types/Pad4.hpp"
#include "../structs/RelatedInstrumentGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v13_0;

#pragma pack(push, 1)

// Add Scaled Simple Instrument
struct add_scaled_simple_instrument {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_desc security_desc;
        fbe_eobi::security_type security_type;
        fbe_eobi::pad1 pad1;
        fbe_eobi::quantity_scaling_factor quantity_scaling_factor;
        fbe_eobi::pad4 pad4;
        fbe_eobi::related_instrument_grp_comp related_instrument_grp_comp;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::add_scaled_simple_instrument, {}};

    fields_type fields;

    // parse method
    static add_scaled_simple_instrument* parse(std::byte* buffer) {
        return reinterpret_cast<add_scaled_simple_instrument*>(buffer);
    }

    // parse method const
    static const add_scaled_simple_instrument* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_scaled_simple_instrument*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_scaled_simple_instrument::fields_type, security_id) == 0, "unexpected offset of add_scaled_simple_instrument::fields_type::security_id");
static_assert(offsetof(add_scaled_simple_instrument::fields_type, transact_time) == 8, "unexpected offset of add_scaled_simple_instrument::fields_type::transact_time");
static_assert(offsetof(add_scaled_simple_instrument::fields_type, security_desc) == 16, "unexpected offset of add_scaled_simple_instrument::fields_type::security_desc");
static_assert(offsetof(add_scaled_simple_instrument::fields_type, security_type) == 56, "unexpected offset of add_scaled_simple_instrument::fields_type::security_type");
static_assert(offsetof(add_scaled_simple_instrument::fields_type, pad1) == 57, "unexpected offset of add_scaled_simple_instrument::fields_type::pad1");
static_assert(offsetof(add_scaled_simple_instrument::fields_type, quantity_scaling_factor) == 58, "unexpected offset of add_scaled_simple_instrument::fields_type::quantity_scaling_factor");
static_assert(offsetof(add_scaled_simple_instrument::fields_type, pad4) == 60, "unexpected offset of add_scaled_simple_instrument::fields_type::pad4");
static_assert(offsetof(add_scaled_simple_instrument::fields_type, related_instrument_grp_comp) == 64, "unexpected offset of add_scaled_simple_instrument::fields_type::related_instrument_grp_comp");
static_assert(sizeof(add_scaled_simple_instrument::fields_type) == 72, "unexpected sizeof add_scaled_simple_instrument::fields_type");
static_assert(sizeof(add_scaled_simple_instrument) == sizeof(fbe_eobi::message_header_comp) + 72, "unexpected sizeof add_scaled_simple_instrument");

#pragma pack(pop)
}
