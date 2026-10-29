#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// mass_action_scope
struct mass_action_scope {

    enum class enum_type : std::uint8_t {
        all_orders_for_a_trading_session = 6,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"All Orders For A Trading Session", enum_type::all_orders_for_a_trading_session},
        {"No Value", enum_type::no_value}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::all_orders_for_a_trading_session: return "All Orders For A Trading Session";
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

    static constexpr const char* name = "mass_action_scope";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<mass_action_scope::enum_type>;
    using storage_type = result_type;

    constexpr mass_action_scope()
     : value{ enum_type{} } {}

    constexpr mass_action_scope(enum_type v)
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
