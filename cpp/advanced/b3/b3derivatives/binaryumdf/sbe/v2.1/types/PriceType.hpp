#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// price_type
struct price_type {

    enum class enum_type : std::uint8_t {
        percentage = 1,
        pu = 2,
        fixed_amount = 3
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Fixed Amount", enum_type::fixed_amount},
        {"Percentage", enum_type::percentage},
        {"Pu", enum_type::pu}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::percentage: return "Percentage";
            case enum_type::pu: return "Pu";
            case enum_type::fixed_amount: return "Fixed Amount";
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

    static constexpr const char* name = "price_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<price_type::enum_type>;
    using storage_type = result_type;

    constexpr price_type()
     : value{ enum_type::percentage } {}

    constexpr price_type(enum_type v)
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
            set(enum_type::fixed_amount);
    }

  protected:
    enum_type value;
};
}
