#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// order_category
struct order_category {

    enum class enum_type : char {
        result_of_options_exercise = 'B',
        result_of_assignment_from_an_options_exercise = 'C',
        result_of_automatic_options_exercise = 'D',
        result_of_midpoint_order = 'E',
        result_of_block_book_trade = 'F',
        result_of_trade_at_close = 'G',
        result_of_trade_at_average = 'H',
        implied_order = '7',
        no_value = '\0'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Implied Order", enum_type::implied_order},
        {"No Value", enum_type::no_value},
        {"Result Of Assignment From An Options Exercise", enum_type::result_of_assignment_from_an_options_exercise},
        {"Result Of Automatic Options Exercise", enum_type::result_of_automatic_options_exercise},
        {"Result Of Block Book Trade", enum_type::result_of_block_book_trade},
        {"Result Of Midpoint Order", enum_type::result_of_midpoint_order},
        {"Result Of Options Exercise", enum_type::result_of_options_exercise},
        {"Result Of Trade At Average", enum_type::result_of_trade_at_average},
        {"Result Of Trade At Close", enum_type::result_of_trade_at_close}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::result_of_options_exercise: return "Result Of Options Exercise";
            case enum_type::result_of_assignment_from_an_options_exercise: return "Result Of Assignment From An Options Exercise";
            case enum_type::result_of_automatic_options_exercise: return "Result Of Automatic Options Exercise";
            case enum_type::result_of_midpoint_order: return "Result Of Midpoint Order";
            case enum_type::result_of_block_book_trade: return "Result Of Block Book Trade";
            case enum_type::result_of_trade_at_close: return "Result Of Trade At Close";
            case enum_type::result_of_trade_at_average: return "Result Of Trade At Average";
            case enum_type::implied_order: return "Implied Order";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "order_category";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<order_category::enum_type>;
    using storage_type = result_type;

    constexpr order_category()
     : value{ enum_type{} } {}

    constexpr order_category(enum_type v)
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
            set(static_cast<enum_type>(0));
    }

  protected:
    enum_type value;
};
}
