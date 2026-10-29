#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// note_codes_bit_field_5
struct note_codes_bit_field_5 {

    using type = uint8_t;

    static constexpr type em_exceptional_circumstances_related_to_market_maker = type{1} << 0;
    static constexpr type un_underlying_not_quoted = type{1} << 1;
    static constexpr type da_digital_asset = type{1} << 2;
    static constexpr type kn_knock_out_buy_back_into_next_trading_day = type{1} << 3;

    static constexpr const char* name = "note_codes_bit_field_5";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr note_codes_bit_field_5()
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

    [[nodiscard]] constexpr bool has_em_exceptional_circumstances_related_to_market_maker() const { return has(em_exceptional_circumstances_related_to_market_maker); }
    [[nodiscard]] constexpr bool has_un_underlying_not_quoted() const { return has(un_underlying_not_quoted); }
    [[nodiscard]] constexpr bool has_da_digital_asset() const { return has(da_digital_asset); }
    [[nodiscard]] constexpr bool has_kn_knock_out_buy_back_into_next_trading_day() const { return has(kn_knock_out_buy_back_into_next_trading_day); }

    constexpr void set_em_exceptional_circumstances_related_to_market_maker(bool v) { set(em_exceptional_circumstances_related_to_market_maker, v); }
    constexpr void set_un_underlying_not_quoted(bool v) { set(un_underlying_not_quoted, v); }
    constexpr void set_da_digital_asset(bool v) { set(da_digital_asset, v); }
    constexpr void set_kn_knock_out_buy_back_into_next_trading_day(bool v) { set(kn_knock_out_buy_back_into_next_trading_day, v); }

  protected:
    type value;
};
}
