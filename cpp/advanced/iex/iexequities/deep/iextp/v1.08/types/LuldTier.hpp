#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

// luld_tier
struct luld_tier {

    enum class enum_type : std::uint8_t {
        not_applicable = 0,
        tier_1_nms_stock = 1,
        tier_2_nms_stock = 2
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Not Applicable", enum_type::not_applicable},
        {"Tier 1 Nms Stock", enum_type::tier_1_nms_stock},
        {"Tier 2 Nms Stock", enum_type::tier_2_nms_stock}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::tier_1_nms_stock: return "Tier 1 Nms Stock";
            case enum_type::tier_2_nms_stock: return "Tier 2 Nms Stock";
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

    static constexpr const char* name = "luld_tier";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<luld_tier::enum_type>;
    using storage_type = result_type;

    constexpr luld_tier()
     : value{ enum_type::not_applicable } {}

    constexpr luld_tier(enum_type v)
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
            set(enum_type::tier_2_nms_stock);
    }

  protected:
    enum_type value;
};
}
