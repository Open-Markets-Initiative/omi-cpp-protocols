#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// ipo_flag
struct ipo_flag {

    enum class enum_type : char {
        set_up_for_ipo_release = 'Y',
        not_set_up_for_ipo_release = 'N',
        not_available = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Not Available", enum_type::not_available},
        {"Not Set Up For Ipo Release", enum_type::not_set_up_for_ipo_release},
        {"Set Up For Ipo Release", enum_type::set_up_for_ipo_release}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::set_up_for_ipo_release: return "Set Up For Ipo Release";
            case enum_type::not_set_up_for_ipo_release: return "Not Set Up For Ipo Release";
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

    static constexpr const char* name = "ipo_flag";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<ipo_flag::enum_type>;
    using storage_type = result_type;

    constexpr ipo_flag()
     : value{ enum_type::set_up_for_ipo_release } {}

    constexpr ipo_flag(enum_type v)
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
