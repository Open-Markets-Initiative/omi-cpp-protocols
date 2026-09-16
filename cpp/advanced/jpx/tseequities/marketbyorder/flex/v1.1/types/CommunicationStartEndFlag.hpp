#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// communication_start_end_flag
struct communication_start_end_flag {

    enum class enum_type : std::uint8_t {
        health_check_control = 0,
        communication_start = 1,
        communication_end = 2
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Communication End", enum_type::communication_end},
        {"Communication Start", enum_type::communication_start},
        {"Health Check Control", enum_type::health_check_control}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::health_check_control: return "Health Check Control";
            case enum_type::communication_start: return "Communication Start";
            case enum_type::communication_end: return "Communication End";
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

    static constexpr const char* name = "communication_start_end_flag";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<communication_start_end_flag::enum_type>;
    using storage_type = result_type;

    constexpr communication_start_end_flag()
     : value{ enum_type::health_check_control } {}

    constexpr communication_start_end_flag(enum_type v)
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
            set(enum_type::communication_end);
    }

  protected:
    enum_type value;
};
}
