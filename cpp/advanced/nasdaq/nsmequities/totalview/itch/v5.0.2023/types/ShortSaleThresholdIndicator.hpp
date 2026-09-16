#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// short_sale_threshold_indicator
struct short_sale_threshold_indicator {

    enum class enum_type : char {
        restricted = 'Y',
        not_restricted = 'N',
        not_available = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Not Available", enum_type::not_available},
        {"Not Restricted", enum_type::not_restricted},
        {"Restricted", enum_type::restricted}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::restricted: return "Restricted";
            case enum_type::not_restricted: return "Not Restricted";
            case enum_type::not_available: return "Not Available";
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

    static constexpr const char* name = "short_sale_threshold_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<short_sale_threshold_indicator::enum_type>;
    using storage_type = result_type;

    constexpr short_sale_threshold_indicator()
     : value{ enum_type::restricted } {}

    constexpr short_sale_threshold_indicator(enum_type v)
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
            set(enum_type::not_available);
    }

  protected:
    enum_type value;
};
}
