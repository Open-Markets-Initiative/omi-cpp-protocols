#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// multi_leg_reporting_type
struct multi_leg_reporting_type {

    enum class enum_type : std::uint8_t {
        single_security = 1,
        individual_leg_of_a_multi_leg_security = 2,
        multi_leg_security = 3,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Individual Leg Of A Multi Leg Security", enum_type::individual_leg_of_a_multi_leg_security},
        {"Multi Leg Security", enum_type::multi_leg_security},
        {"No Value", enum_type::no_value},
        {"Single Security", enum_type::single_security}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::single_security: return "Single Security";
            case enum_type::individual_leg_of_a_multi_leg_security: return "Individual Leg Of A Multi Leg Security";
            case enum_type::multi_leg_security: return "Multi Leg Security";
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

    static constexpr const char* name = "multi_leg_reporting_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<multi_leg_reporting_type::enum_type>;
    using storage_type = result_type;

    constexpr multi_leg_reporting_type()
     : value{ enum_type{} } {}

    constexpr multi_leg_reporting_type(enum_type v)
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
