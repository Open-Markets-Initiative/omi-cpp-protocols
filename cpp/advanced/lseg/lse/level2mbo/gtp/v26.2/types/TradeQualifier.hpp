#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// trade_qualifier
struct trade_qualifier {

    enum class enum_type : char {
        na = ' ',
        closing_price_cross_cpx = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Closing Price Cross Cpx", enum_type::closing_price_cross_cpx},
        {"Na", enum_type::na}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::na: return "Na";
            case enum_type::closing_price_cross_cpx: return "Closing Price Cross Cpx";
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

    static constexpr const char* name = "trade_qualifier";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_qualifier::enum_type>;
    using storage_type = result_type;

    constexpr trade_qualifier()
     : value{ enum_type{} } {}

    constexpr trade_qualifier(enum_type v)
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
            set(enum_type::closing_price_cross_cpx);
    }

  protected:
    enum_type value;
};
}
