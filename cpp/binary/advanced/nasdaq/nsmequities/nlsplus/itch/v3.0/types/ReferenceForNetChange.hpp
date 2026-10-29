#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// reference_for_net_change
struct reference_for_net_change {

    enum class enum_type : char {
        first_trade_price = 'F',
        underwriter_price = 'W'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"First Trade Price", enum_type::first_trade_price},
        {"Underwriter Price", enum_type::underwriter_price}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::first_trade_price: return "First Trade Price";
            case enum_type::underwriter_price: return "Underwriter Price";
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

    static constexpr const char* name = "reference_for_net_change";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<reference_for_net_change::enum_type>;
    using storage_type = result_type;

    constexpr reference_for_net_change()
     : value{ enum_type{} } {}

    constexpr reference_for_net_change(enum_type v)
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
            set(enum_type::underwriter_price);
    }

  protected:
    enum_type value;
};
}
