#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

// trade_condition
struct trade_condition {

    enum class enum_type : std::uint8_t {
        implied_trade = 1,
        systematic_internalizer = 153,
        midpoint_price = 155,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Implied Trade", enum_type::implied_trade},
        {"Midpoint Price", enum_type::midpoint_price},
        {"No Value", enum_type::no_value},
        {"Systematic Internalizer", enum_type::systematic_internalizer}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::implied_trade: return "Implied Trade";
            case enum_type::systematic_internalizer: return "Systematic Internalizer";
            case enum_type::midpoint_price: return "Midpoint Price";
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

    static constexpr const char* name = "trade_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_condition::enum_type>;
    using storage_type = result_type;

    constexpr trade_condition()
     : value{ enum_type{} } {}

    constexpr trade_condition(enum_type v)
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
            set(static_cast<enum_type>(0xFF));
    }

  protected:
    enum_type value;
};
}
