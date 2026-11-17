// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/PacketFlag.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// packet_flag
struct packet_flag {

    using type = uint8_t;

    static constexpr type heartbeat = type{1} << 0;
    static constexpr type seq_num_reset = type{1} << 1;
    static constexpr type replay = type{1} << 6;
    static constexpr type test = type{1} << 7;

    static constexpr const char* name = "packet_flag";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr packet_flag()
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

    [[nodiscard]] constexpr bool has_heartbeat() const { return has(heartbeat); }
    [[nodiscard]] constexpr bool has_seq_num_reset() const { return has(seq_num_reset); }
    [[nodiscard]] constexpr bool has_replay() const { return has(replay); }
    [[nodiscard]] constexpr bool has_test() const { return has(test); }

    constexpr void set_heartbeat(bool v) { set(heartbeat, v); }
    constexpr void set_seq_num_reset(bool v) { set(seq_num_reset, v); }
    constexpr void set_replay(bool v) { set(replay, v); }
    constexpr void set_test(bool v) { set(test, v); }

  protected:
    type value;
};
}
