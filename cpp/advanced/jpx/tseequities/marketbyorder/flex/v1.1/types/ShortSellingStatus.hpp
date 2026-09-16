#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// short_selling_status
struct short_selling_status {

    enum class enum_type : std::uint8_t {
        short_selling_regulation_is_not_applied = 0,
        short_selling_regulation_is_applied = 1
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Short Selling Regulation Is Applied", enum_type::short_selling_regulation_is_applied},
        {"Short Selling Regulation Is Not Applied", enum_type::short_selling_regulation_is_not_applied}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::short_selling_regulation_is_not_applied: return "Short Selling Regulation Is Not Applied";
            case enum_type::short_selling_regulation_is_applied: return "Short Selling Regulation Is Applied";
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

    static constexpr const char* name = "short_selling_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<short_selling_status::enum_type>;
    using storage_type = result_type;

    constexpr short_selling_status()
     : value{ enum_type::short_selling_regulation_is_not_applied } {}

    constexpr short_selling_status(enum_type v)
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
            set(enum_type::short_selling_regulation_is_applied);
    }

  protected:
    enum_type value;
};
}
