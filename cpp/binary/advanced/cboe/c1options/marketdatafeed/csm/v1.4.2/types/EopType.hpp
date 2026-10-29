#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// eop_type
struct eop_type {

    enum class enum_type : std::uint8_t {
        undefined = 0,
        opening_price = 1,
        need_more_sellers = 2,
        need_more_buyers = 3,
        no_opening_trades = 4,
        multiple_opening_prices = 5,
        need_quote_to_open = 6,
        price_not_in_quote_range = 7,
        need_dpm_quote_to_open = 8,
        dpm_quote_invalid = 9,
        price_not_in_botr_range = 10
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Dpm Quote Invalid", enum_type::dpm_quote_invalid},
        {"Multiple Opening Prices", enum_type::multiple_opening_prices},
        {"Need Dpm Quote To Open", enum_type::need_dpm_quote_to_open},
        {"Need More Buyers", enum_type::need_more_buyers},
        {"Need More Sellers", enum_type::need_more_sellers},
        {"Need Quote To Open", enum_type::need_quote_to_open},
        {"No Opening Trades", enum_type::no_opening_trades},
        {"Opening Price", enum_type::opening_price},
        {"Price Not In Botr Range", enum_type::price_not_in_botr_range},
        {"Price Not In Quote Range", enum_type::price_not_in_quote_range},
        {"Undefined", enum_type::undefined}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::undefined: return "Undefined";
            case enum_type::opening_price: return "Opening Price";
            case enum_type::need_more_sellers: return "Need More Sellers";
            case enum_type::need_more_buyers: return "Need More Buyers";
            case enum_type::no_opening_trades: return "No Opening Trades";
            case enum_type::multiple_opening_prices: return "Multiple Opening Prices";
            case enum_type::need_quote_to_open: return "Need Quote To Open";
            case enum_type::price_not_in_quote_range: return "Price Not In Quote Range";
            case enum_type::need_dpm_quote_to_open: return "Need Dpm Quote To Open";
            case enum_type::dpm_quote_invalid: return "Dpm Quote Invalid";
            case enum_type::price_not_in_botr_range: return "Price Not In Botr Range";
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

    static constexpr const char* name = "eop_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<eop_type::enum_type>;
    using storage_type = result_type;

    constexpr eop_type()
     : value{ enum_type{} } {}

    constexpr eop_type(enum_type v)
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
            set(enum_type::price_not_in_botr_range);
    }

  protected:
    enum_type value;
};
}
