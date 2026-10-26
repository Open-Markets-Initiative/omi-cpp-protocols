#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// width_type
struct width_type {

    enum class enum_type : char {
        regular = 'R',
        volatility = 'V',
        max_quote_width = 'Q'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Max Quote Width", enum_type::max_quote_width},
        {"Regular", enum_type::regular},
        {"Volatility", enum_type::volatility}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular: return "Regular";
            case enum_type::volatility: return "Volatility";
            case enum_type::max_quote_width: return "Max Quote Width";
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

    static constexpr const char* name = "width_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<width_type::enum_type>;
    using storage_type = result_type;

    constexpr width_type()
     : value{ enum_type{} } {}

    constexpr width_type(enum_type v)
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
            set(enum_type::max_quote_width);
    }

  protected:
    enum_type value;
};
}
