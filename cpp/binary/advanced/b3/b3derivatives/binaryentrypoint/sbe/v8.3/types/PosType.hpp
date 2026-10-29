#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// pos_type
struct pos_type {

    enum class enum_type : char {
        transaction_quantity = 'T',
        start_of_day_qty = 'S',
        option_exercise_qty = 'E',
        blocked_qty = 'B',
        uncovered_qty = 'U',
        covered_qty = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Blocked Qty", enum_type::blocked_qty},
        {"Covered Qty", enum_type::covered_qty},
        {"Option Exercise Qty", enum_type::option_exercise_qty},
        {"Start Of Day Qty", enum_type::start_of_day_qty},
        {"Transaction Quantity", enum_type::transaction_quantity},
        {"Uncovered Qty", enum_type::uncovered_qty}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::transaction_quantity: return "Transaction Quantity";
            case enum_type::start_of_day_qty: return "Start Of Day Qty";
            case enum_type::option_exercise_qty: return "Option Exercise Qty";
            case enum_type::blocked_qty: return "Blocked Qty";
            case enum_type::uncovered_qty: return "Uncovered Qty";
            case enum_type::covered_qty: return "Covered Qty";
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

    static constexpr const char* name = "pos_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<pos_type::enum_type>;
    using storage_type = result_type;

    constexpr pos_type()
     : value{ enum_type{} } {}

    constexpr pos_type(enum_type v)
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
            set(enum_type::covered_qty);
    }

  protected:
    enum_type value;
};
}
