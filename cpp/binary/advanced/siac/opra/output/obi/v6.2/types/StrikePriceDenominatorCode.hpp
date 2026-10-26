#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// strike_price_denominator_code
struct strike_price_denominator_code {

    enum class enum_type : char {
        ten = 'A',
        hundred = 'B',
        thousand = 'C',
        ten_thousand = 'D',
        hundred_thousand = 'E',
        no_fraction = 'I'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Hundred", enum_type::hundred},
        {"Hundred Thousand", enum_type::hundred_thousand},
        {"No Fraction", enum_type::no_fraction},
        {"Ten", enum_type::ten},
        {"Ten Thousand", enum_type::ten_thousand},
        {"Thousand", enum_type::thousand}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::ten: return "Ten";
            case enum_type::hundred: return "Hundred";
            case enum_type::thousand: return "Thousand";
            case enum_type::ten_thousand: return "Ten Thousand";
            case enum_type::hundred_thousand: return "Hundred Thousand";
            case enum_type::no_fraction: return "No Fraction";
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

    static constexpr const char* name = "strike_price_denominator_code";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<strike_price_denominator_code::enum_type>;
    using storage_type = result_type;

    constexpr strike_price_denominator_code()
     : value{ enum_type{} } {}

    constexpr strike_price_denominator_code(enum_type v)
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
            set(enum_type::no_fraction);
    }

  protected:
    enum_type value;
};
}
