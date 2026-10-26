#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityDesc.hpp"
#include "../types/SecurityType.hpp"
#include "../types/PutOrCall.hpp"
#include "../types/ExerciseStyle.hpp"
#include "../types/SettlMethod.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/OptAttribute.hpp"
#include "../types/ContractDate.hpp"
#include "../types/SecurityReferenceDataSupplement.hpp"
#include "../types/Pad4.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

// Add Flexible Instrument
struct add_flexible_instrument {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_desc security_desc;
        fbe_eobi::security_type security_type;
        fbe_eobi::put_or_call put_or_call;
        fbe_eobi::exercise_style exercise_style;
        fbe_eobi::settl_method settl_method;
        fbe_eobi::maturity_date maturity_date;
        fbe_eobi::strike_price strike_price;
        fbe_eobi::opt_attribute opt_attribute;
        fbe_eobi::contract_date contract_date;
        fbe_eobi::security_reference_data_supplement security_reference_data_supplement;
        fbe_eobi::pad4 pad4;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::add_flexible_instrument, {}};

    fields_type fields;

    // parse method
    static add_flexible_instrument* parse(std::byte* buffer) {
        return reinterpret_cast<add_flexible_instrument*>(buffer);
    }

    // parse method const
    static const add_flexible_instrument* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_flexible_instrument*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_flexible_instrument::fields_type, security_id) == 0, "unexpected offset of add_flexible_instrument::fields_type::security_id");
static_assert(offsetof(add_flexible_instrument::fields_type, transact_time) == 8, "unexpected offset of add_flexible_instrument::fields_type::transact_time");
static_assert(offsetof(add_flexible_instrument::fields_type, security_desc) == 16, "unexpected offset of add_flexible_instrument::fields_type::security_desc");
static_assert(offsetof(add_flexible_instrument::fields_type, security_type) == 56, "unexpected offset of add_flexible_instrument::fields_type::security_type");
static_assert(offsetof(add_flexible_instrument::fields_type, put_or_call) == 57, "unexpected offset of add_flexible_instrument::fields_type::put_or_call");
static_assert(offsetof(add_flexible_instrument::fields_type, exercise_style) == 58, "unexpected offset of add_flexible_instrument::fields_type::exercise_style");
static_assert(offsetof(add_flexible_instrument::fields_type, settl_method) == 59, "unexpected offset of add_flexible_instrument::fields_type::settl_method");
static_assert(offsetof(add_flexible_instrument::fields_type, maturity_date) == 60, "unexpected offset of add_flexible_instrument::fields_type::maturity_date");
static_assert(offsetof(add_flexible_instrument::fields_type, strike_price) == 64, "unexpected offset of add_flexible_instrument::fields_type::strike_price");
static_assert(offsetof(add_flexible_instrument::fields_type, opt_attribute) == 72, "unexpected offset of add_flexible_instrument::fields_type::opt_attribute");
static_assert(offsetof(add_flexible_instrument::fields_type, contract_date) == 76, "unexpected offset of add_flexible_instrument::fields_type::contract_date");
static_assert(offsetof(add_flexible_instrument::fields_type, security_reference_data_supplement) == 80, "unexpected offset of add_flexible_instrument::fields_type::security_reference_data_supplement");
static_assert(offsetof(add_flexible_instrument::fields_type, pad4) == 84, "unexpected offset of add_flexible_instrument::fields_type::pad4");
static_assert(sizeof(add_flexible_instrument::fields_type) == 88, "unexpected sizeof add_flexible_instrument::fields_type");
static_assert(sizeof(add_flexible_instrument) == sizeof(fbe_eobi::message_header_comp) + 88, "unexpected sizeof add_flexible_instrument");

#pragma pack(pop)
}
