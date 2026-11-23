// Lseg.Millennium.Level2.Mitch.v11.9: types/StatisticsReserved.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// statistics_reserved
struct statistics_reserved {

    using type = uint8_t;

    static constexpr type unused_8 = type{0xFF} << 0;

    static constexpr const char* name = "statistics_reserved";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr statistics_reserved()
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

    [[nodiscard]] constexpr type get_unused_8() const { return static_cast<type>((value & unused_8) >> 0); }

    constexpr void set_unused_8(type v) { const type held = static_cast<type>((value & static_cast<type>(~unused_8)) | ((v << 0) & unused_8)); value = held; }

  protected:
    type value;
};
}
