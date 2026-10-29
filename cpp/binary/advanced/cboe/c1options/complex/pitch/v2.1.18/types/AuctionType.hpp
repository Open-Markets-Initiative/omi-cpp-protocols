#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// auction_type
struct auction_type {

    enum class enum_type : char {
        complex_auction = 'C',
        complex_solicitation_auction = 'S',
        complex_aim = 'B',
        coa_all_or_none = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Coa All Or None", enum_type::coa_all_or_none},
        {"Complex Aim", enum_type::complex_aim},
        {"Complex Auction", enum_type::complex_auction},
        {"Complex Solicitation Auction", enum_type::complex_solicitation_auction}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::complex_auction: return "Complex Auction";
            case enum_type::complex_solicitation_auction: return "Complex Solicitation Auction";
            case enum_type::complex_aim: return "Complex Aim";
            case enum_type::coa_all_or_none: return "Coa All Or None";
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

    static constexpr const char* name = "auction_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<auction_type::enum_type>;
    using storage_type = result_type;

    constexpr auction_type()
     : value{ enum_type{} } {}

    constexpr auction_type(enum_type v)
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
            set(enum_type::coa_all_or_none);
    }

  protected:
    enum_type value;
};
}
