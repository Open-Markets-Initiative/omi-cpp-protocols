#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// strategy_type
struct strategy_type {

    enum class enum_type : char {
        vertical_spread = 'V',
        time_spread = 'T',
        diagonal_spread = 'D',
        straddle = 'S',
        strangle = 'G',
        combo = 'C',
        risk_reversal = 'R',
        ratio_spread = 'A',
        custom = 'U'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Combo", enum_type::combo},
        {"Custom", enum_type::custom},
        {"Diagonal Spread", enum_type::diagonal_spread},
        {"Ratio Spread", enum_type::ratio_spread},
        {"Risk Reversal", enum_type::risk_reversal},
        {"Straddle", enum_type::straddle},
        {"Strangle", enum_type::strangle},
        {"Time Spread", enum_type::time_spread},
        {"Vertical Spread", enum_type::vertical_spread}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::vertical_spread: return "Vertical Spread";
            case enum_type::time_spread: return "Time Spread";
            case enum_type::diagonal_spread: return "Diagonal Spread";
            case enum_type::straddle: return "Straddle";
            case enum_type::strangle: return "Strangle";
            case enum_type::combo: return "Combo";
            case enum_type::risk_reversal: return "Risk Reversal";
            case enum_type::ratio_spread: return "Ratio Spread";
            case enum_type::custom: return "Custom";
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

    static constexpr const char* name = "strategy_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<strategy_type::enum_type>;
    using storage_type = result_type;

    constexpr strategy_type()
     : value{ enum_type{} } {}

    constexpr strategy_type(enum_type v)
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
            set(enum_type::custom);
    }

  protected:
    enum_type value;
};
}
