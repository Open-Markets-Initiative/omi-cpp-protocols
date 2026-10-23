#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// md_entry_type_statistics
struct md_entry_type_statistics {

    enum class enum_type : char {
        open_price = '4',
        high_trade = '7',
        low_trade = '8',
        vwap = '9',
        highest_bid = 'N',
        lowest_offer = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"High Trade", enum_type::high_trade},
        {"Highest Bid", enum_type::highest_bid},
        {"Low Trade", enum_type::low_trade},
        {"Lowest Offer", enum_type::lowest_offer},
        {"Open Price", enum_type::open_price},
        {"Vwap", enum_type::vwap}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::open_price: return "Open Price";
            case enum_type::high_trade: return "High Trade";
            case enum_type::low_trade: return "Low Trade";
            case enum_type::vwap: return "Vwap";
            case enum_type::highest_bid: return "Highest Bid";
            case enum_type::lowest_offer: return "Lowest Offer";
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

    static constexpr const char* name = "md_entry_type_statistics";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_entry_type_statistics::enum_type>;
    using storage_type = result_type;

    constexpr md_entry_type_statistics()
     : value{ enum_type{} } {}

    constexpr md_entry_type_statistics(enum_type v)
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
            set(enum_type::lowest_offer);
    }

  protected:
    enum_type value;
};
}
