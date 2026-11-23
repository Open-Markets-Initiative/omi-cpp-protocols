// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/Bypass.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// bypass
struct bypass {

    enum class enum_type : char {
        the_order_is_a_bypass = 'Y',
        the_order_is_not_a_bypass = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"The Order Is A Bypass", enum_type::the_order_is_a_bypass},
        {"The Order Is Not A Bypass", enum_type::the_order_is_not_a_bypass}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::the_order_is_a_bypass: return "The Order Is A Bypass";
            case enum_type::the_order_is_not_a_bypass: return "The Order Is Not A Bypass";
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

    static constexpr const char* name = "bypass";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<bypass::enum_type>;
    using storage_type = result_type;

    constexpr bypass()
     : value{ enum_type{} } {}

    constexpr bypass(enum_type v)
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
            set(enum_type::the_order_is_not_a_bypass);
    }

  protected:
    enum_type value;
};
}
