#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// luld_tier
struct luld_tier {

    enum class enum_type : char {
        luld_not_applicable = '0',
        luld_tier_1_security = '1',
        luld_tier_2_security = '2'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Luld Not Applicable", enum_type::luld_not_applicable},
        {"Luld Tier 1 Security", enum_type::luld_tier_1_security},
        {"Luld Tier 2 Security", enum_type::luld_tier_2_security}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::luld_not_applicable: return "Luld Not Applicable";
            case enum_type::luld_tier_1_security: return "Luld Tier 1 Security";
            case enum_type::luld_tier_2_security: return "Luld Tier 2 Security";
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
     : value{ enum_type{} } {}

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
            set(enum_type::luld_tier_2_security);
    }

  protected:
    enum_type value;
};
}
