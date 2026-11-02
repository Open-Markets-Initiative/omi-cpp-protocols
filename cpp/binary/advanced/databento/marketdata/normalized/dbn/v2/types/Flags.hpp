#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// flags
struct flags {

    using type = uint8_t;

    static constexpr type publisher_specific = type{1} << 1;
    static constexpr type maybe_bad_book = type{1} << 2;
    static constexpr type bad_ts_recv = type{1} << 3;
    static constexpr type mbp = type{1} << 4;
    static constexpr type snapshot = type{1} << 5;
    static constexpr type tob = type{1} << 6;
    static constexpr type last = type{1} << 7;

    static constexpr const char* name = "flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr flags()
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

    [[nodiscard]] constexpr bool has_publisher_specific() const { return has(publisher_specific); }
    [[nodiscard]] constexpr bool has_maybe_bad_book() const { return has(maybe_bad_book); }
    [[nodiscard]] constexpr bool has_bad_ts_recv() const { return has(bad_ts_recv); }
    [[nodiscard]] constexpr bool has_mbp() const { return has(mbp); }
    [[nodiscard]] constexpr bool has_snapshot() const { return has(snapshot); }
    [[nodiscard]] constexpr bool has_tob() const { return has(tob); }
    [[nodiscard]] constexpr bool has_last() const { return has(last); }

    constexpr void set_publisher_specific(bool v) { set(publisher_specific, v); }
    constexpr void set_maybe_bad_book(bool v) { set(maybe_bad_book, v); }
    constexpr void set_bad_ts_recv(bool v) { set(bad_ts_recv, v); }
    constexpr void set_mbp(bool v) { set(mbp, v); }
    constexpr void set_snapshot(bool v) { set(snapshot, v); }
    constexpr void set_tob(bool v) { set(tob, v); }
    constexpr void set_last(bool v) { set(last, v); }

  protected:
    type value;
};
}
