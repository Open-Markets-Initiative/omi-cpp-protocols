#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// issue
struct issue {

    enum class enum_type : char {
        periodic_indicative_settlement = 'i',
        indicative_settlement = 'I',
        initial_settlement = 'S',
        reissued_settlement = 'R'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Indicative Settlement", enum_type::indicative_settlement},
        {"Initial Settlement", enum_type::initial_settlement},
        {"Periodic Indicative Settlement", enum_type::periodic_indicative_settlement},
        {"Reissued Settlement", enum_type::reissued_settlement}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::periodic_indicative_settlement: return "Periodic Indicative Settlement";
            case enum_type::indicative_settlement: return "Indicative Settlement";
            case enum_type::initial_settlement: return "Initial Settlement";
            case enum_type::reissued_settlement: return "Reissued Settlement";
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

    static constexpr const char* name = "issue";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<issue::enum_type>;
    using storage_type = result_type;

    constexpr issue()
     : value{ enum_type{} } {}

    constexpr issue(enum_type v)
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
            set(enum_type::reissued_settlement);
    }

  protected:
    enum_type value;
};
}
