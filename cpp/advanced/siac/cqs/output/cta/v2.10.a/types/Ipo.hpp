#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// ipo
struct ipo {

    enum class enum_type : char {
        not_an_ipo_symbol = '0',
        ipo_symbol = '1'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Ipo Symbol", enum_type::ipo_symbol},
        {"Not An Ipo Symbol", enum_type::not_an_ipo_symbol}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_an_ipo_symbol: return "Not An Ipo Symbol";
            case enum_type::ipo_symbol: return "Ipo Symbol";
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

    static constexpr const char* name = "ipo";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<ipo::enum_type>;
    using storage_type = result_type;

    constexpr ipo()
     : value{ enum_type{} } {}

    constexpr ipo(enum_type v)
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
            set(enum_type::ipo_symbol);
    }

  protected:
    enum_type value;
};
}
