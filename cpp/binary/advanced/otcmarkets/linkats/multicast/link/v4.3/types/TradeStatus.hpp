// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/TradeStatus.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// trade_status
struct trade_status {

    using type = uint8_t;

    static constexpr type irregular = type{1} << 0;

    static constexpr const char* name = "trade_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr trade_status()
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

    [[nodiscard]] constexpr bool has_irregular() const { return has(irregular); }

    constexpr void set_irregular(bool v) { set(irregular, v); }

  protected:
    type value;
};
}
