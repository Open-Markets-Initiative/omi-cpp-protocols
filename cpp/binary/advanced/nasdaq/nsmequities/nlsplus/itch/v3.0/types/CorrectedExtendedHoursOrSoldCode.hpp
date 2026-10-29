#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// corrected_extended_hours_or_sold_code
struct corrected_extended_hours_or_sold_code {

    enum class enum_type : char {
        extended_hours_trade = 'T',
        extended_hours_trade_reported_late = 'U',
        sold_last = 'L',
        sold_out_of_sequence = 'Z',
        not_applicable = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Extended Hours Trade", enum_type::extended_hours_trade},
        {"Extended Hours Trade Reported Late", enum_type::extended_hours_trade_reported_late},
        {"Not Applicable", enum_type::not_applicable},
        {"Sold Last", enum_type::sold_last},
        {"Sold Out Of Sequence", enum_type::sold_out_of_sequence}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::extended_hours_trade: return "Extended Hours Trade";
            case enum_type::extended_hours_trade_reported_late: return "Extended Hours Trade Reported Late";
            case enum_type::sold_last: return "Sold Last";
            case enum_type::sold_out_of_sequence: return "Sold Out Of Sequence";
            case enum_type::not_applicable: return "Not Applicable";
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

    static constexpr const char* name = "corrected_extended_hours_or_sold_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<corrected_extended_hours_or_sold_code::enum_type>;
    using storage_type = result_type;

    constexpr corrected_extended_hours_or_sold_code()
     : value{ enum_type{} } {}

    constexpr corrected_extended_hours_or_sold_code(enum_type v)
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
            set(enum_type::not_applicable);
    }

  protected:
    enum_type value;
};
}
