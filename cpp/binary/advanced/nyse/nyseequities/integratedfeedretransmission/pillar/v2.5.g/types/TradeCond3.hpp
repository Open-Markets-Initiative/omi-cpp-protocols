#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// trade_cond_3
struct trade_cond_3 {

    enum class enum_type : char {
        na = ' ',
        extended_hours_trade = 'T',
        extended_hours_sold_out_of_sequence = 'U',
        sold = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Extended Hours Sold Out Of Sequence", enum_type::extended_hours_sold_out_of_sequence},
        {"Extended Hours Trade", enum_type::extended_hours_trade},
        {"Na", enum_type::na},
        {"Sold", enum_type::sold}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::na: return "Na";
            case enum_type::extended_hours_trade: return "Extended Hours Trade";
            case enum_type::extended_hours_sold_out_of_sequence: return "Extended Hours Sold Out Of Sequence";
            case enum_type::sold: return "Sold";
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

    static constexpr const char* name = "trade_cond_3";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_cond_3::enum_type>;
    using storage_type = result_type;

    constexpr trade_cond_3()
     : value{ enum_type{} } {}

    constexpr trade_cond_3(enum_type v)
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
            set(enum_type::sold);
    }

  protected:
    enum_type value;
};
}
