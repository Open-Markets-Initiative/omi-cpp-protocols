#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// closing_only_indicator
struct closing_only_indicator {

    enum class enum_type : char {
        standard_series = '0',
        closing_only_series = '1'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Closing Only Series", enum_type::closing_only_series},
        {"Standard Series", enum_type::standard_series}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::standard_series: return "Standard Series";
            case enum_type::closing_only_series: return "Closing Only Series";
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

    static constexpr const char* name = "closing_only_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<closing_only_indicator::enum_type>;
    using storage_type = result_type;

    constexpr closing_only_indicator()
     : value{ enum_type{} } {}

    constexpr closing_only_indicator(enum_type v)
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
            set(enum_type::closing_only_series);
    }

  protected:
    enum_type value;
};
}
