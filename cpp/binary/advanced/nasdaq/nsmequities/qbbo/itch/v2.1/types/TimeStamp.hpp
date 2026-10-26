#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"
#include "../cache/Required.hpp"
#include "../common/Day.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// time_stamp
#pragma pack(push, 1)
struct time_stamp {

    static constexpr const char* name = "time_stamp";
    static constexpr std::size_t size = 6;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr time_stamp()
     : value{ 0 } {}

    time_stamp(std::uint64_t v)
     : value{ __builtin_bswap64(v << 16) } {}

    [[nodiscard]] result_type get() const {
        return result_type{__builtin_bswap64(static_cast<std::uint64_t>(value)) >> 16};
    }

    void set(std::uint64_t v) {
        value = __builtin_bswap64(v << 16);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

    // time_stamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds;
    // none where it has no value
    [[nodiscard]] std::optional<std::int64_t> utc(const calendar::Day& day) const {
        const auto held = get();
        if (!held.has_value()) {
            return std::nullopt;
        }
        return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(held.value()));
    }

  protected:
    std::uint64_t value:48;
};
#pragma pack(pop)
}
