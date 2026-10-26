#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// short_sale_restriction_indicator
struct short_sale_restriction_indicator {

    enum class enum_type : char {
        short_sale_restriction_not_in_effect = ' ',
        short_sale_restriction_activated = 'A',
        short_sale_restriction_continued = 'C',
        short_sale_restriction_deactivated = 'D',
        short_sale_restriction_in_effect = 'E'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Short Sale Restriction Activated", enum_type::short_sale_restriction_activated},
        {"Short Sale Restriction Continued", enum_type::short_sale_restriction_continued},
        {"Short Sale Restriction Deactivated", enum_type::short_sale_restriction_deactivated},
        {"Short Sale Restriction In Effect", enum_type::short_sale_restriction_in_effect},
        {"Short Sale Restriction Not In Effect", enum_type::short_sale_restriction_not_in_effect}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::short_sale_restriction_not_in_effect: return "Short Sale Restriction Not In Effect";
            case enum_type::short_sale_restriction_activated: return "Short Sale Restriction Activated";
            case enum_type::short_sale_restriction_continued: return "Short Sale Restriction Continued";
            case enum_type::short_sale_restriction_deactivated: return "Short Sale Restriction Deactivated";
            case enum_type::short_sale_restriction_in_effect: return "Short Sale Restriction In Effect";
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

    static constexpr const char* name = "short_sale_restriction_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<short_sale_restriction_indicator::enum_type>;
    using storage_type = result_type;

    constexpr short_sale_restriction_indicator()
     : value{ enum_type{} } {}

    constexpr short_sale_restriction_indicator(enum_type v)
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
            set(enum_type::short_sale_restriction_in_effect);
    }

  protected:
    enum_type value;
};
}
