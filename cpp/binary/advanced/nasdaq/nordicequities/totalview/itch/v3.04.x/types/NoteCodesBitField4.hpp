#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// note_codes_bit_field_4
struct note_codes_bit_field_4 {

    using type = uint8_t;

    static constexpr type bb_buy_back = type{1} << 0;
    static constexpr type ce_capped_by_esma = type{1} << 3;
    static constexpr type pd_price_discrepancy_historical_average_share_classes = type{1} << 5;
    static constexpr type sm_stressed_market = type{1} << 6;
    static constexpr type ew_marketwide_exceptional_circumstance = type{1} << 7;

    static constexpr const char* name = "note_codes_bit_field_4";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr note_codes_bit_field_4()
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

    [[nodiscard]] constexpr bool has_bb_buy_back() const { return has(bb_buy_back); }
    [[nodiscard]] constexpr bool has_ce_capped_by_esma() const { return has(ce_capped_by_esma); }
    [[nodiscard]] constexpr bool has_pd_price_discrepancy_historical_average_share_classes() const { return has(pd_price_discrepancy_historical_average_share_classes); }
    [[nodiscard]] constexpr bool has_sm_stressed_market() const { return has(sm_stressed_market); }
    [[nodiscard]] constexpr bool has_ew_marketwide_exceptional_circumstance() const { return has(ew_marketwide_exceptional_circumstance); }

    constexpr void set_bb_buy_back(bool v) { set(bb_buy_back, v); }
    constexpr void set_ce_capped_by_esma(bool v) { set(ce_capped_by_esma, v); }
    constexpr void set_pd_price_discrepancy_historical_average_share_classes(bool v) { set(pd_price_discrepancy_historical_average_share_classes, v); }
    constexpr void set_sm_stressed_market(bool v) { set(sm_stressed_market, v); }
    constexpr void set_ew_marketwide_exceptional_circumstance(bool v) { set(ew_marketwide_exceptional_circumstance, v); }

  protected:
    type value;
};
}
