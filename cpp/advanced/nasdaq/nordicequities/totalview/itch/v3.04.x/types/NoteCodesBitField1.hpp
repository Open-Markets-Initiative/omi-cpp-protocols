#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// note_codes_bit_field_1
struct note_codes_bit_field_1 {

    using type = uint8_t;

    static constexpr type nm_new_market_company = type{1} << 0;
    static constexpr type xr_excluding_participating_in_rights = type{1} << 1;
    static constexpr type sp_excluding_participating_in_split = type{1} << 2;
    static constexpr type po_company_subject_to_public_offer = type{1} << 3;
    static constexpr type ud_under_drawing = type{1} << 4;
    static constexpr type sr_excluding_comb_split_and_issue_rights = type{1} << 5;
    static constexpr type ul_un_listed = type{1} << 6;
    static constexpr type wi_when_issued = type{1} << 7;

    static constexpr const char* name = "note_codes_bit_field_1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr note_codes_bit_field_1()
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

    [[nodiscard]] constexpr bool has_nm_new_market_company() const { return has(nm_new_market_company); }
    [[nodiscard]] constexpr bool has_xr_excluding_participating_in_rights() const { return has(xr_excluding_participating_in_rights); }
    [[nodiscard]] constexpr bool has_sp_excluding_participating_in_split() const { return has(sp_excluding_participating_in_split); }
    [[nodiscard]] constexpr bool has_po_company_subject_to_public_offer() const { return has(po_company_subject_to_public_offer); }
    [[nodiscard]] constexpr bool has_ud_under_drawing() const { return has(ud_under_drawing); }
    [[nodiscard]] constexpr bool has_sr_excluding_comb_split_and_issue_rights() const { return has(sr_excluding_comb_split_and_issue_rights); }
    [[nodiscard]] constexpr bool has_ul_un_listed() const { return has(ul_un_listed); }
    [[nodiscard]] constexpr bool has_wi_when_issued() const { return has(wi_when_issued); }

    constexpr void set_nm_new_market_company(bool v) { set(nm_new_market_company, v); }
    constexpr void set_xr_excluding_participating_in_rights(bool v) { set(xr_excluding_participating_in_rights, v); }
    constexpr void set_sp_excluding_participating_in_split(bool v) { set(sp_excluding_participating_in_split, v); }
    constexpr void set_po_company_subject_to_public_offer(bool v) { set(po_company_subject_to_public_offer, v); }
    constexpr void set_ud_under_drawing(bool v) { set(ud_under_drawing, v); }
    constexpr void set_sr_excluding_comb_split_and_issue_rights(bool v) { set(sr_excluding_comb_split_and_issue_rights, v); }
    constexpr void set_ul_un_listed(bool v) { set(ul_un_listed, v); }
    constexpr void set_wi_when_issued(bool v) { set(wi_when_issued, v); }

  protected:
    type value;
};
}
