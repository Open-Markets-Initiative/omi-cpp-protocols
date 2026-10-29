#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// auction_opening_type
struct auction_opening_type {

    enum class enum_type : char {
        gth = 'G',
        rth = 'O',
        halt_reopening = 'H'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Gth", enum_type::gth},
        {"Halt Reopening", enum_type::halt_reopening},
        {"Rth", enum_type::rth}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::gth: return "Gth";
            case enum_type::rth: return "Rth";
            case enum_type::halt_reopening: return "Halt Reopening";
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

    static constexpr const char* name = "auction_opening_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<auction_opening_type::enum_type>;
    using storage_type = result_type;

    constexpr auction_opening_type()
     : value{ enum_type{} } {}

    constexpr auction_opening_type(enum_type v)
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
            set(enum_type::halt_reopening);
    }

  protected:
    enum_type value;
};
}
