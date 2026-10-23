#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// note_codes_bit_field_3
struct note_codes_bit_field_3 {

    using type = uint8_t;

    static constexpr type ss_excluding_comb_split_redemption_share = type{1} << 0;
    static constexpr type fn_first_north_company = type{1} << 1;
    static constexpr type ob_observation_status = type{1} << 2;
    static constexpr type xd_excluding_dividend = type{1} << 3;
    static constexpr type fe_foreign_non_eueea_entity = type{1} << 4;
    static constexpr type so_sold_out_buy_back = type{1} << 5;
    static constexpr type sk_soft_knock = type{1} << 6;
    static constexpr type kb_knock_out_buy_back = type{1} << 7;

    static constexpr const char* name = "note_codes_bit_field_3";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr note_codes_bit_field_3()
     : value{ 0 } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(uint8_t v) {
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

    [[nodiscard]] constexpr bool has_ss_excluding_comb_split_redemption_share() const { return has(ss_excluding_comb_split_redemption_share); }
    [[nodiscard]] constexpr bool has_fn_first_north_company() const { return has(fn_first_north_company); }
    [[nodiscard]] constexpr bool has_ob_observation_status() const { return has(ob_observation_status); }
    [[nodiscard]] constexpr bool has_xd_excluding_dividend() const { return has(xd_excluding_dividend); }
    [[nodiscard]] constexpr bool has_fe_foreign_non_eueea_entity() const { return has(fe_foreign_non_eueea_entity); }
    [[nodiscard]] constexpr bool has_so_sold_out_buy_back() const { return has(so_sold_out_buy_back); }
    [[nodiscard]] constexpr bool has_sk_soft_knock() const { return has(sk_soft_knock); }
    [[nodiscard]] constexpr bool has_kb_knock_out_buy_back() const { return has(kb_knock_out_buy_back); }

    constexpr void set_ss_excluding_comb_split_redemption_share(bool v) { set(ss_excluding_comb_split_redemption_share, v); }
    constexpr void set_fn_first_north_company(bool v) { set(fn_first_north_company, v); }
    constexpr void set_ob_observation_status(bool v) { set(ob_observation_status, v); }
    constexpr void set_xd_excluding_dividend(bool v) { set(xd_excluding_dividend, v); }
    constexpr void set_fe_foreign_non_eueea_entity(bool v) { set(fe_foreign_non_eueea_entity, v); }
    constexpr void set_so_sold_out_buy_back(bool v) { set(so_sold_out_buy_back, v); }
    constexpr void set_sk_soft_knock(bool v) { set(sk_soft_knock, v); }
    constexpr void set_kb_knock_out_buy_back(bool v) { set(kb_knock_out_buy_back, v); }

  protected:
    type value;
};
}
