#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// event_code
struct event_code {

    enum class enum_type : char {
        end_of_day = 'C',
        start_of_day = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"End Of Day", enum_type::end_of_day},
        {"Start Of Day", enum_type::start_of_day}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::end_of_day: return "End Of Day";
            case enum_type::start_of_day: return "Start Of Day";
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

    static constexpr const char* name = "event_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<event_code::enum_type>;
    using storage_type = result_type;

    constexpr event_code()
     : value{ enum_type{} } {}

    constexpr event_code(enum_type v)
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
            set(enum_type::start_of_day);
    }

  protected:
    enum_type value;
};
}
