// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: types/MatchAlgorithm.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// match_algorithm
struct match_algorithm {

    enum class enum_type : char {
        price_then_time = 'P'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 1> from_string_map = {{
        {"Price Then Time", enum_type::price_then_time}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::price_then_time: return "Price Then Time";
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

    static constexpr const char* name = "match_algorithm";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<match_algorithm::enum_type>;
    using storage_type = result_type;

    constexpr match_algorithm()
     : value{ enum_type{} } {}

    constexpr match_algorithm(enum_type v)
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
            set(enum_type::price_then_time);
    }

  protected:
    enum_type value;
};
}
