#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// inverse_indicator
struct inverse_indicator {

    enum class enum_type : char {
        inverse = 'Y',
        not_inverse = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Inverse", enum_type::inverse},
        {"Not Inverse", enum_type::not_inverse}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::inverse: return "Inverse";
            case enum_type::not_inverse: return "Not Inverse";
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

    static constexpr const char* name = "inverse_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<inverse_indicator::enum_type>;
    using storage_type = result_type;

    constexpr inverse_indicator()
     : value{ enum_type{} } {}

    constexpr inverse_indicator(enum_type v)
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
            set(enum_type::not_inverse);
    }

  protected:
    enum_type value;
};
}
