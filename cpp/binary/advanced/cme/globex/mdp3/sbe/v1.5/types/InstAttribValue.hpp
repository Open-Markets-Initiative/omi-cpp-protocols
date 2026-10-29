#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cme::mdp3::v5 {

// inst_attrib_value
struct inst_attrib_value {

    using type = uint32_t;

    static constexpr type electronic_match_eligible = type{1} << 0;
    static constexpr type order_cross_eligible = type{1} << 1;
    static constexpr type block_trade_eligible = type{1} << 2;
    static constexpr type efp_eligible = type{1} << 3;
    static constexpr type ebf_eligible = type{1} << 4;
    static constexpr type efs_eligible = type{1} << 5;
    static constexpr type efr_eligible = type{1} << 6;
    static constexpr type otc_eligible = type{1} << 7;
    static constexpr type ilink_indicative_mass_quoting_eligible = type{1} << 8;
    static constexpr type negative_strike_eligible = type{1} << 9;
    static constexpr type negative_price_outright_eligible = type{1} << 10;
    static constexpr type is_fractional = type{1} << 11;
    static constexpr type volatility_quoted_option = type{1} << 12;
    static constexpr type rfq_cross_eligible = type{1} << 13;
    static constexpr type zero_price_outright_eligible = type{1} << 14;
    static constexpr type decaying_product_eligibility = type{1} << 15;
    static constexpr type variable_product_eligibility = type{1} << 16;
    static constexpr type daily_product_eligibility = type{1} << 17;
    static constexpr type gt_orders_eligibility = type{1} << 18;
    static constexpr type implied_matching_eligibility = type{1} << 19;

    static constexpr const char* name = "inst_attrib_value";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<uint32_t>;
    using storage_type = result_type;

    constexpr inst_attrib_value()
     : value{ 0 } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(uint32_t v) {
        value = v;
    }

    constexpr void set(result_type v) {
        if (v.has_value())
            set(v.value());
        else
            set(type{0});
    }

    [[nodiscard]] constexpr bool has(type bit) const { return (value & bit) != 0; }
    constexpr void set(type bit, bool enabled) { if (enabled) value |= bit; else value &= static_cast<type>(~bit); }

    [[nodiscard]] constexpr bool has_electronic_match_eligible() const { return has(electronic_match_eligible); }
    [[nodiscard]] constexpr bool has_order_cross_eligible() const { return has(order_cross_eligible); }
    [[nodiscard]] constexpr bool has_block_trade_eligible() const { return has(block_trade_eligible); }
    [[nodiscard]] constexpr bool has_efp_eligible() const { return has(efp_eligible); }
    [[nodiscard]] constexpr bool has_ebf_eligible() const { return has(ebf_eligible); }
    [[nodiscard]] constexpr bool has_efs_eligible() const { return has(efs_eligible); }
    [[nodiscard]] constexpr bool has_efr_eligible() const { return has(efr_eligible); }
    [[nodiscard]] constexpr bool has_otc_eligible() const { return has(otc_eligible); }
    [[nodiscard]] constexpr bool has_ilink_indicative_mass_quoting_eligible() const { return has(ilink_indicative_mass_quoting_eligible); }
    [[nodiscard]] constexpr bool has_negative_strike_eligible() const { return has(negative_strike_eligible); }
    [[nodiscard]] constexpr bool has_negative_price_outright_eligible() const { return has(negative_price_outright_eligible); }
    [[nodiscard]] constexpr bool has_is_fractional() const { return has(is_fractional); }
    [[nodiscard]] constexpr bool has_volatility_quoted_option() const { return has(volatility_quoted_option); }
    [[nodiscard]] constexpr bool has_rfq_cross_eligible() const { return has(rfq_cross_eligible); }
    [[nodiscard]] constexpr bool has_zero_price_outright_eligible() const { return has(zero_price_outright_eligible); }
    [[nodiscard]] constexpr bool has_decaying_product_eligibility() const { return has(decaying_product_eligibility); }
    [[nodiscard]] constexpr bool has_variable_product_eligibility() const { return has(variable_product_eligibility); }
    [[nodiscard]] constexpr bool has_daily_product_eligibility() const { return has(daily_product_eligibility); }
    [[nodiscard]] constexpr bool has_gt_orders_eligibility() const { return has(gt_orders_eligibility); }
    [[nodiscard]] constexpr bool has_implied_matching_eligibility() const { return has(implied_matching_eligibility); }

    constexpr void set_electronic_match_eligible(bool v) { set(electronic_match_eligible, v); }
    constexpr void set_order_cross_eligible(bool v) { set(order_cross_eligible, v); }
    constexpr void set_block_trade_eligible(bool v) { set(block_trade_eligible, v); }
    constexpr void set_efp_eligible(bool v) { set(efp_eligible, v); }
    constexpr void set_ebf_eligible(bool v) { set(ebf_eligible, v); }
    constexpr void set_efs_eligible(bool v) { set(efs_eligible, v); }
    constexpr void set_efr_eligible(bool v) { set(efr_eligible, v); }
    constexpr void set_otc_eligible(bool v) { set(otc_eligible, v); }
    constexpr void set_ilink_indicative_mass_quoting_eligible(bool v) { set(ilink_indicative_mass_quoting_eligible, v); }
    constexpr void set_negative_strike_eligible(bool v) { set(negative_strike_eligible, v); }
    constexpr void set_negative_price_outright_eligible(bool v) { set(negative_price_outright_eligible, v); }
    constexpr void set_is_fractional(bool v) { set(is_fractional, v); }
    constexpr void set_volatility_quoted_option(bool v) { set(volatility_quoted_option, v); }
    constexpr void set_rfq_cross_eligible(bool v) { set(rfq_cross_eligible, v); }
    constexpr void set_zero_price_outright_eligible(bool v) { set(zero_price_outright_eligible, v); }
    constexpr void set_decaying_product_eligibility(bool v) { set(decaying_product_eligibility, v); }
    constexpr void set_variable_product_eligibility(bool v) { set(variable_product_eligibility, v); }
    constexpr void set_daily_product_eligibility(bool v) { set(daily_product_eligibility, v); }
    constexpr void set_gt_orders_eligibility(bool v) { set(gt_orders_eligibility, v); }
    constexpr void set_implied_matching_eligibility(bool v) { set(implied_matching_eligibility, v); }

  protected:
    type value;
};
}
