#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// long_term_option
struct long_term_option {

    enum class enum_type : char {
        far_month_expiration = 'Y',
        near_month_expiration = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Far Month Expiration", enum_type::far_month_expiration},
        {"Near Month Expiration", enum_type::near_month_expiration}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::far_month_expiration: return "Far Month Expiration";
            case enum_type::near_month_expiration: return "Near Month Expiration";
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

    static constexpr const char* name = "long_term_option";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<long_term_option::enum_type>;
    using storage_type = result_type;

    constexpr long_term_option()
     : value{ enum_type{} } {}

    constexpr long_term_option(enum_type v)
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
            set(enum_type::near_month_expiration);
    }

  protected:
    enum_type value;
};
}
