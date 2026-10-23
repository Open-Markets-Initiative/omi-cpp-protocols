#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// note_codes_bit_field_2
struct note_codes_bit_field_2 {

    using type = uint8_t;

    static constexpr type br_company_bankruptcy = type{1} << 0;
    static constexpr type su_suspension = type{1} << 1;
    static constexpr type rl_removal_from_listing_in_process = type{1} << 2;
    static constexpr type sl_other_surveillance_list_reason = type{1} << 3;
    static constexpr type to_a_significant_reverse_takeover_pending = type{1} << 4;
    static constexpr type cs_cent_shares = type{1} << 5;
    static constexpr type rs_reversed_split = type{1} << 6;
    static constexpr type bs_excluding_comb_bonus_split = type{1} << 7;

    static constexpr const char* name = "note_codes_bit_field_2";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr note_codes_bit_field_2()
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

    [[nodiscard]] constexpr bool has_br_company_bankruptcy() const { return has(br_company_bankruptcy); }
    [[nodiscard]] constexpr bool has_su_suspension() const { return has(su_suspension); }
    [[nodiscard]] constexpr bool has_rl_removal_from_listing_in_process() const { return has(rl_removal_from_listing_in_process); }
    [[nodiscard]] constexpr bool has_sl_other_surveillance_list_reason() const { return has(sl_other_surveillance_list_reason); }
    [[nodiscard]] constexpr bool has_to_a_significant_reverse_takeover_pending() const { return has(to_a_significant_reverse_takeover_pending); }
    [[nodiscard]] constexpr bool has_cs_cent_shares() const { return has(cs_cent_shares); }
    [[nodiscard]] constexpr bool has_rs_reversed_split() const { return has(rs_reversed_split); }
    [[nodiscard]] constexpr bool has_bs_excluding_comb_bonus_split() const { return has(bs_excluding_comb_bonus_split); }

    constexpr void set_br_company_bankruptcy(bool v) { set(br_company_bankruptcy, v); }
    constexpr void set_su_suspension(bool v) { set(su_suspension, v); }
    constexpr void set_rl_removal_from_listing_in_process(bool v) { set(rl_removal_from_listing_in_process, v); }
    constexpr void set_sl_other_surveillance_list_reason(bool v) { set(sl_other_surveillance_list_reason, v); }
    constexpr void set_to_a_significant_reverse_takeover_pending(bool v) { set(to_a_significant_reverse_takeover_pending, v); }
    constexpr void set_cs_cent_shares(bool v) { set(cs_cent_shares, v); }
    constexpr void set_rs_reversed_split(bool v) { set(rs_reversed_split, v); }
    constexpr void set_bs_excluding_comb_bonus_split(bool v) { set(bs_excluding_comb_bonus_split, v); }

  protected:
    type value;
};
}
