#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// leg_security_type
struct leg_security_type {

    enum class enum_type : std::uint8_t {
        leg_security_multi_leg = 1,
        leg_security_underlying_leg = 2,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Leg Security Multi Leg", enum_type::leg_security_multi_leg},
        {"Leg Security Underlying Leg", enum_type::leg_security_underlying_leg},
        {"No Value", enum_type::no_value}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::leg_security_multi_leg: return "Leg Security Multi Leg";
            case enum_type::leg_security_underlying_leg: return "Leg Security Underlying Leg";
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

    static constexpr const char* name = "leg_security_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<leg_security_type::enum_type>;
    using storage_type = result_type;

    constexpr leg_security_type()
     : value{ enum_type{} } {}

    constexpr leg_security_type(enum_type v)
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
