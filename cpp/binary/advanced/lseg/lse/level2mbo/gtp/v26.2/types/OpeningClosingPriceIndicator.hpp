#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// opening_closing_price_indicator
struct opening_closing_price_indicator {

    enum class enum_type : char {
        ut = 'A',
        at = 'B',
        mid_of_bbo = 'C',
        last_at = 'D',
        last_ut = 'E',
        manual = 'F',
        previous_close = 'I'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"At", enum_type::at},
        {"Last At", enum_type::last_at},
        {"Last Ut", enum_type::last_ut},
        {"Manual", enum_type::manual},
        {"Mid Of Bbo", enum_type::mid_of_bbo},
        {"Previous Close", enum_type::previous_close},
        {"Ut", enum_type::ut}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::ut: return "Ut";
            case enum_type::at: return "At";
            case enum_type::mid_of_bbo: return "Mid Of Bbo";
            case enum_type::last_at: return "Last At";
            case enum_type::last_ut: return "Last Ut";
            case enum_type::manual: return "Manual";
            case enum_type::previous_close: return "Previous Close";
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

    static constexpr const char* name = "opening_closing_price_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<opening_closing_price_indicator::enum_type>;
    using storage_type = result_type;

    constexpr opening_closing_price_indicator()
     : value{ enum_type{} } {}

    constexpr opening_closing_price_indicator(enum_type v)
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
            set(enum_type::previous_close);
    }

  protected:
    enum_type value;
};
}
