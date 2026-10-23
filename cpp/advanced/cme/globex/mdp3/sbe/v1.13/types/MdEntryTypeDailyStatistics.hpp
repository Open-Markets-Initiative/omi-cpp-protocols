#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// md_entry_type_daily_statistics
struct md_entry_type_daily_statistics {

    enum class enum_type : char {
        settlement_price = '6',
        cleared_volume = 'B',
        open_interest = 'C',
        fixing_price = 'W'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Cleared Volume", enum_type::cleared_volume},
        {"Fixing Price", enum_type::fixing_price},
        {"Open Interest", enum_type::open_interest},
        {"Settlement Price", enum_type::settlement_price}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::settlement_price: return "Settlement Price";
            case enum_type::cleared_volume: return "Cleared Volume";
            case enum_type::open_interest: return "Open Interest";
            case enum_type::fixing_price: return "Fixing Price";
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

    static constexpr const char* name = "md_entry_type_daily_statistics";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_entry_type_daily_statistics::enum_type>;
    using storage_type = result_type;

    constexpr md_entry_type_daily_statistics()
     : value{ enum_type{} } {}

    constexpr md_entry_type_daily_statistics(enum_type v)
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
            set(enum_type::fixing_price);
    }

  protected:
    enum_type value;
};
}
