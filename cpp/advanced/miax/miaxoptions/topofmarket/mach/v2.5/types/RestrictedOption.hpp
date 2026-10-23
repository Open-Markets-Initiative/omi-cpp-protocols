#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// restricted_option
struct restricted_option {

    enum class enum_type : char {
        accept_position_closing = 'Y',
        accept_open_and_close = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Accept Open And Close", enum_type::accept_open_and_close},
        {"Accept Position Closing", enum_type::accept_position_closing}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::accept_position_closing: return "Accept Position Closing";
            case enum_type::accept_open_and_close: return "Accept Open And Close";
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

    static constexpr const char* name = "restricted_option";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<restricted_option::enum_type>;
    using storage_type = result_type;

    constexpr restricted_option()
     : value{ enum_type{} } {}

    constexpr restricted_option(enum_type v)
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
            set(enum_type::accept_open_and_close);
    }

  protected:
    enum_type value;
};
}
