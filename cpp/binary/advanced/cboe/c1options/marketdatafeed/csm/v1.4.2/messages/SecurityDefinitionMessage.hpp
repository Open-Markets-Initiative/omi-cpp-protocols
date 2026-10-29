#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/SecurityExchange.hpp"
#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/PriceType.hpp"
#include "../structs/StrikePrice.hpp"
#include "../types/PutOrCall.hpp"
#include "../structs/MinimumStrikePriceFraction.hpp"
#include "../structs/MaxStrikePrice.hpp"
#include "../structs/PremiumBreakPoint.hpp"
#include "../structs/MinimumAbovePremiumFraction.hpp"
#include "../structs/MinimumBelowPremiumFraction.hpp"
#include "../types/ExerciseStyle.hpp"
#include "../types/ContractSize.hpp"
#include "../types/NoLegs.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSecurityId.hpp"
#include "../types/LegSide.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)
struct security_definition_message_security_definition_leg_entry {
    csm_marketdatafeed::leg_ratio_qty leg_ratio_qty;
    csm_marketdatafeed::leg_security_id leg_security_id;
    csm_marketdatafeed::leg_side leg_side;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Security Definition Message
struct security_definition_message {

    struct fields_type {
        csm_marketdatafeed::security_exchange security_exchange;
        csm_marketdatafeed::class_key class_key;
        csm_marketdatafeed::security_id security_id;
        csm_marketdatafeed::maturity_date maturity_date;
        csm_marketdatafeed::price_type price_type;
        csm_marketdatafeed::strike_price strike_price;
        csm_marketdatafeed::put_or_call put_or_call;
        csm_marketdatafeed::minimum_strike_price_fraction minimum_strike_price_fraction;
        csm_marketdatafeed::max_strike_price max_strike_price;
        csm_marketdatafeed::premium_break_point premium_break_point;
        csm_marketdatafeed::minimum_above_premium_fraction minimum_above_premium_fraction;
        csm_marketdatafeed::minimum_below_premium_fraction minimum_below_premium_fraction;
        csm_marketdatafeed::exercise_style exercise_style;
        csm_marketdatafeed::contract_size contract_size;
        csm_marketdatafeed::no_legs no_legs;
    };

    csm_marketdatafeed::message_header header = {{}, template_id::enum_type::security_definition_message, {}, {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(csm_marketdatafeed::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const { return tail + tail_capacity; }

    // sequential access to variable-length regions
    sbe_var_data security_type() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data symbol(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data target_location_id(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data currency_code(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data underlying_symbol(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data underlying_type(const std::byte* position) const {
        return { position, tail_end() };
    }

    external_count_iterator<security_definition_message_security_definition_leg_entry> security_definition_leg(const std::byte* position) const {
        return { position, fields.no_legs.get().value(), tail_end() };
    }


    // parse method
    static security_definition_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_definition_message*>(buffer);
    }

    // parse method const
    static const security_definition_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_definition_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_definition_message::fields_type, security_exchange) == 0, "unexpected offset of security_definition_message::fields_type::security_exchange");
static_assert(offsetof(security_definition_message::fields_type, class_key) == 1, "unexpected offset of security_definition_message::fields_type::class_key");
static_assert(offsetof(security_definition_message::fields_type, security_id) == 5, "unexpected offset of security_definition_message::fields_type::security_id");
static_assert(offsetof(security_definition_message::fields_type, maturity_date) == 9, "unexpected offset of security_definition_message::fields_type::maturity_date");
static_assert(offsetof(security_definition_message::fields_type, price_type) == 17, "unexpected offset of security_definition_message::fields_type::price_type");
static_assert(offsetof(security_definition_message::fields_type, strike_price) == 18, "unexpected offset of security_definition_message::fields_type::strike_price");
static_assert(offsetof(security_definition_message::fields_type, put_or_call) == 23, "unexpected offset of security_definition_message::fields_type::put_or_call");
static_assert(offsetof(security_definition_message::fields_type, minimum_strike_price_fraction) == 24, "unexpected offset of security_definition_message::fields_type::minimum_strike_price_fraction");
static_assert(offsetof(security_definition_message::fields_type, max_strike_price) == 29, "unexpected offset of security_definition_message::fields_type::max_strike_price");
static_assert(offsetof(security_definition_message::fields_type, premium_break_point) == 34, "unexpected offset of security_definition_message::fields_type::premium_break_point");
static_assert(offsetof(security_definition_message::fields_type, minimum_above_premium_fraction) == 39, "unexpected offset of security_definition_message::fields_type::minimum_above_premium_fraction");
static_assert(offsetof(security_definition_message::fields_type, minimum_below_premium_fraction) == 44, "unexpected offset of security_definition_message::fields_type::minimum_below_premium_fraction");
static_assert(offsetof(security_definition_message::fields_type, exercise_style) == 49, "unexpected offset of security_definition_message::fields_type::exercise_style");
static_assert(offsetof(security_definition_message::fields_type, contract_size) == 50, "unexpected offset of security_definition_message::fields_type::contract_size");
static_assert(offsetof(security_definition_message::fields_type, no_legs) == 54, "unexpected offset of security_definition_message::fields_type::no_legs");
static_assert(sizeof(security_definition_message::fields_type) == 55, "unexpected sizeof security_definition_message::fields_type");

#pragma pack(pop)
}
