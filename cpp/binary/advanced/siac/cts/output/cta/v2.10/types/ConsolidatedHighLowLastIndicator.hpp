#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_10 {

// consolidated_high_low_last_indicator
struct consolidated_high_low_last_indicator {

    enum class enum_type : char {
        none = 'A',
        high = 'B',
        low = 'C',
        last = 'D',
        high_last = 'E',
        low_last = 'F',
        high_low_last = 'G',
        high_low = 'H'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"High", enum_type::high},
        {"High Last", enum_type::high_last},
        {"High Low", enum_type::high_low},
        {"High Low Last", enum_type::high_low_last},
        {"Last", enum_type::last},
        {"Low", enum_type::low},
        {"Low Last", enum_type::low_last},
        {"None", enum_type::none}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::none: return "None";
            case enum_type::high: return "High";
            case enum_type::low: return "Low";
            case enum_type::last: return "Last";
            case enum_type::high_last: return "High Last";
            case enum_type::low_last: return "Low Last";
            case enum_type::high_low_last: return "High Low Last";
            case enum_type::high_low: return "High Low";
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

    static constexpr const char* name = "consolidated_high_low_last_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<consolidated_high_low_last_indicator::enum_type>;
    using storage_type = result_type;

    constexpr consolidated_high_low_last_indicator()
     : value{ enum_type{} } {}

    constexpr consolidated_high_low_last_indicator(enum_type v)
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
            set(enum_type::high_low);
    }

  protected:
    enum_type value;
};
}
