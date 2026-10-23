#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// trade_flags
struct trade_flags {

    using type = uint8_t;

    static constexpr type sip_reporting = type{1} << 0;
    static constexpr type retail_trade_indicator = type{1} << 1;

    static constexpr const char* name = "trade_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr trade_flags()
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

    [[nodiscard]] constexpr bool has_sip_reporting() const { return has(sip_reporting); }
    [[nodiscard]] constexpr bool has_retail_trade_indicator() const { return has(retail_trade_indicator); }

    constexpr void set_sip_reporting(bool v) { set(sip_reporting, v); }
    constexpr void set_retail_trade_indicator(bool v) { set(retail_trade_indicator, v); }

  protected:
    type value;
};
}
