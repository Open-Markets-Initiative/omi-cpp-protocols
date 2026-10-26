#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// option_type
struct option_type {

    enum class enum_type : char {
        put = 'P',
        call = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Call", enum_type::call},
        {"Put", enum_type::put}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::put: return "Put";
            case enum_type::call: return "Call";
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

    static constexpr const char* name = "option_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<option_type::enum_type>;
    using storage_type = result_type;

    constexpr option_type()
     : value{ enum_type{} } {}

    constexpr option_type(enum_type v)
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
            set(enum_type::call);
    }

  protected:
    enum_type value;
};
}
