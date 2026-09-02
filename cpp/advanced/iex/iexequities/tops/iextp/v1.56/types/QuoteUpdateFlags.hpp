#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

// quote_update_flags
struct quote_update_flags {

    using type = uint8_t;

    static constexpr type market_session = type{1} << 6;
    static constexpr type symbol_availability = type{1} << 7;

    static constexpr const char* name = "quote_update_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr quote_update_flags()
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

    [[nodiscard]] constexpr bool has_market_session() const { return has(market_session); }
    [[nodiscard]] constexpr bool has_symbol_availability() const { return has(symbol_availability); }

    constexpr void set_market_session(bool v) { set(market_session, v); }
    constexpr void set_symbol_availability(bool v) { set(symbol_availability, v); }

  protected:
    type value;
};
}
