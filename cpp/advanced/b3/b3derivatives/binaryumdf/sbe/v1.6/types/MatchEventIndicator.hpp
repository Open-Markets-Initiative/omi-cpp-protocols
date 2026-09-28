#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// match_event_indicator
struct match_event_indicator {

    using type = uint8_t;

    static constexpr type last_trade_msg = type{1} << 0;
    static constexpr type last_volume_msg = type{1} << 1;
    static constexpr type last_quote_msg = type{1} << 2;
    static constexpr type last_stats_msg = type{1} << 3;
    static constexpr type last_implied_msg = type{1} << 4;
    static constexpr type recovery_msg = type{1} << 5;
    static constexpr type end_of_event = type{1} << 7;

    static constexpr const char* name = "match_event_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr match_event_indicator()
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

    [[nodiscard]] constexpr bool has_last_trade_msg() const { return has(last_trade_msg); }
    [[nodiscard]] constexpr bool has_last_volume_msg() const { return has(last_volume_msg); }
    [[nodiscard]] constexpr bool has_last_quote_msg() const { return has(last_quote_msg); }
    [[nodiscard]] constexpr bool has_last_stats_msg() const { return has(last_stats_msg); }
    [[nodiscard]] constexpr bool has_last_implied_msg() const { return has(last_implied_msg); }
    [[nodiscard]] constexpr bool has_recovery_msg() const { return has(recovery_msg); }
    [[nodiscard]] constexpr bool has_end_of_event() const { return has(end_of_event); }

    constexpr void set_last_trade_msg(bool v) { set(last_trade_msg, v); }
    constexpr void set_last_volume_msg(bool v) { set(last_volume_msg, v); }
    constexpr void set_last_quote_msg(bool v) { set(last_quote_msg, v); }
    constexpr void set_last_stats_msg(bool v) { set(last_stats_msg, v); }
    constexpr void set_last_implied_msg(bool v) { set(last_implied_msg, v); }
    constexpr void set_recovery_msg(bool v) { set(recovery_msg, v); }
    constexpr void set_end_of_event(bool v) { set(end_of_event, v); }

  protected:
    type value;
};
}
