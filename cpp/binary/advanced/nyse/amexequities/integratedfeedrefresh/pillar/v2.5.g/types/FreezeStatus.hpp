#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

// freeze_status
struct freeze_status {

    enum class enum_type : std::uint8_t {
        imbalance_freeze_not_in_effect = 0,
        imbalance_freeze_is_in_effect = 1
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Imbalance Freeze Is In Effect", enum_type::imbalance_freeze_is_in_effect},
        {"Imbalance Freeze Not In Effect", enum_type::imbalance_freeze_not_in_effect}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::imbalance_freeze_not_in_effect: return "Imbalance Freeze Not In Effect";
            case enum_type::imbalance_freeze_is_in_effect: return "Imbalance Freeze Is In Effect";
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

    static constexpr const char* name = "freeze_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<freeze_status::enum_type>;
    using storage_type = result_type;

    constexpr freeze_status()
     : value{ enum_type{} } {}

    constexpr freeze_status(enum_type v)
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
            set(enum_type::imbalance_freeze_is_in_effect);
    }

  protected:
    enum_type value;
};
}
