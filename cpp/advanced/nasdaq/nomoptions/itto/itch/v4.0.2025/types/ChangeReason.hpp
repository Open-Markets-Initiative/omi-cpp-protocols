#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// change_reason
struct change_reason {

    enum class enum_type : char {
        user = 'U',
        reprice = 'R',
        suspend = 'S'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Reprice", enum_type::reprice},
        {"Suspend", enum_type::suspend},
        {"User", enum_type::user}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::user: return "User";
            case enum_type::reprice: return "Reprice";
            case enum_type::suspend: return "Suspend";
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

    static constexpr const char* name = "change_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<change_reason::enum_type>;
    using storage_type = result_type;

    constexpr change_reason()
     : value{ enum_type{} } {}

    constexpr change_reason(enum_type v)
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
            set(enum_type::suspend);
    }

  protected:
    enum_type value;
};
}
