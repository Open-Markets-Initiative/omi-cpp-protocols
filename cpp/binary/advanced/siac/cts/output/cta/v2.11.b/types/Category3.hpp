#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// category_3
struct category_3 {

    enum class enum_type : char {
        not_extended_hours_or_sold_out_of_sequence = ' ',
        sold_last_late_reporting = 'L',
        market_center_opening_trade = 'O',
        extended_hours_trade = 'T',
        extended_hours_sold_out_of_sequence = 'U',
        sold_out_of_sequence = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Extended Hours Sold Out Of Sequence", enum_type::extended_hours_sold_out_of_sequence},
        {"Extended Hours Trade", enum_type::extended_hours_trade},
        {"Market Center Opening Trade", enum_type::market_center_opening_trade},
        {"Not Extended Hours Or Sold Out Of Sequence", enum_type::not_extended_hours_or_sold_out_of_sequence},
        {"Sold Last Late Reporting", enum_type::sold_last_late_reporting},
        {"Sold Out Of Sequence", enum_type::sold_out_of_sequence}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_extended_hours_or_sold_out_of_sequence: return "Not Extended Hours Or Sold Out Of Sequence";
            case enum_type::sold_last_late_reporting: return "Sold Last Late Reporting";
            case enum_type::market_center_opening_trade: return "Market Center Opening Trade";
            case enum_type::extended_hours_trade: return "Extended Hours Trade";
            case enum_type::extended_hours_sold_out_of_sequence: return "Extended Hours Sold Out Of Sequence";
            case enum_type::sold_out_of_sequence: return "Sold Out Of Sequence";
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

    static constexpr const char* name = "category_3";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<category_3::enum_type>;
    using storage_type = result_type;

    constexpr category_3()
     : value{ enum_type{} } {}

    constexpr category_3(enum_type v)
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
            set(enum_type::sold_out_of_sequence);
    }

  protected:
    enum_type value;
};
}
