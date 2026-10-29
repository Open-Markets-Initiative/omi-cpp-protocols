#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// order_capacity
struct order_capacity {

    enum class enum_type : char {
        customer = 'C',
        customer_professional = 'D',
        firm = 'F',
        broker_dealer_customer = 'B',
        broker_dealer_firm = 'K',
        proprietary = 'E',
        away_market_maker = 'N',
        market_maker = 'M'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Away Market Maker", enum_type::away_market_maker},
        {"Broker Dealer Customer", enum_type::broker_dealer_customer},
        {"Broker Dealer Firm", enum_type::broker_dealer_firm},
        {"Customer", enum_type::customer},
        {"Customer Professional", enum_type::customer_professional},
        {"Firm", enum_type::firm},
        {"Market Maker", enum_type::market_maker},
        {"Proprietary", enum_type::proprietary}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::customer: return "Customer";
            case enum_type::customer_professional: return "Customer Professional";
            case enum_type::firm: return "Firm";
            case enum_type::broker_dealer_customer: return "Broker Dealer Customer";
            case enum_type::broker_dealer_firm: return "Broker Dealer Firm";
            case enum_type::proprietary: return "Proprietary";
            case enum_type::away_market_maker: return "Away Market Maker";
            case enum_type::market_maker: return "Market Maker";
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

    static constexpr const char* name = "order_capacity";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<order_capacity::enum_type>;
    using storage_type = result_type;

    constexpr order_capacity()
     : value{ enum_type{} } {}

    constexpr order_capacity(enum_type v)
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
            set(enum_type::market_maker);
    }

  protected:
    enum_type value;
};
}
