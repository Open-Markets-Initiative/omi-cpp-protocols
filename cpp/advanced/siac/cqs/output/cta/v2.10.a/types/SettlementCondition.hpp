#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// settlement_condition
struct settlement_condition {

    enum class enum_type : char {
        regular_way_settlement = ' ',
        cash_settlement = 'A',
        next_day_settlement = 'B'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Cash Settlement", enum_type::cash_settlement},
        {"Next Day Settlement", enum_type::next_day_settlement},
        {"Regular Way Settlement", enum_type::regular_way_settlement}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular_way_settlement: return "Regular Way Settlement";
            case enum_type::cash_settlement: return "Cash Settlement";
            case enum_type::next_day_settlement: return "Next Day Settlement";
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

    static constexpr const char* name = "settlement_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<settlement_condition::enum_type>;
    using storage_type = result_type;

    constexpr settlement_condition()
     : value{ enum_type{} } {}

    constexpr settlement_condition(enum_type v)
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
            set(enum_type::next_day_settlement);
    }

  protected:
    enum_type value;
};
}
