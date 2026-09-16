#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// reset_start_end_flag
struct reset_start_end_flag {

    enum class enum_type : std::uint8_t {
        start_of_reset_dissemination = 1,
        end_of_reset_dissemination = 2
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"End Of Reset Dissemination", enum_type::end_of_reset_dissemination},
        {"Start Of Reset Dissemination", enum_type::start_of_reset_dissemination}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::start_of_reset_dissemination: return "Start Of Reset Dissemination";
            case enum_type::end_of_reset_dissemination: return "End Of Reset Dissemination";
            default: return "unknown";
        }
    }

    static constexpr std::optional<enum_type> from_string(std::string_view str) {
        auto it = std::lower_bound(
            from_string_map.begin(),
            from_string_map.end(),
            str,
            [](const auto& pair, std::string_view s) { return pair.first < s; }
        );
        if (it != from_string_map.end() && it->first == str) {
            return it->second;
        }
        return std::nullopt;
    }

    static constexpr const char* name = "reset_start_end_flag";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<reset_start_end_flag::enum_type>;
    using storage_type = result_type;

    constexpr reset_start_end_flag()
     : value{ enum_type::start_of_reset_dissemination } {}

    constexpr reset_start_end_flag(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(enum_type::end_of_reset_dissemination);
    }

  protected:
    enum_type value;
};
}
