#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// pricing_method
struct pricing_method {

    enum class enum_type : std::uint8_t {
        itayose_method = 1,
        zaraba_method = 2,
        sell_special_quote_displayed = 3,
        buy_special_quote_displayed = 4,
        sell_sequential_trade_quote_displayed = 5,
        buy_sequential_trade_quote_displayed = 6,
        other_than_the_above = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Buy Sequential Trade Quote Displayed", enum_type::buy_sequential_trade_quote_displayed},
        {"Buy Special Quote Displayed", enum_type::buy_special_quote_displayed},
        {"Itayose Method", enum_type::itayose_method},
        {"Other Than The Above", enum_type::other_than_the_above},
        {"Sell Sequential Trade Quote Displayed", enum_type::sell_sequential_trade_quote_displayed},
        {"Sell Special Quote Displayed", enum_type::sell_special_quote_displayed},
        {"Zaraba Method", enum_type::zaraba_method}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::itayose_method: return "Itayose Method";
            case enum_type::zaraba_method: return "Zaraba Method";
            case enum_type::sell_special_quote_displayed: return "Sell Special Quote Displayed";
            case enum_type::buy_special_quote_displayed: return "Buy Special Quote Displayed";
            case enum_type::sell_sequential_trade_quote_displayed: return "Sell Sequential Trade Quote Displayed";
            case enum_type::buy_sequential_trade_quote_displayed: return "Buy Sequential Trade Quote Displayed";
            case enum_type::other_than_the_above: return "Other Than The Above";
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

    static constexpr const char* name = "pricing_method";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<pricing_method::enum_type>;
    using storage_type = result_type;

    constexpr pricing_method()
     : value{ enum_type::itayose_method } {}

    constexpr pricing_method(enum_type v)
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
            set(enum_type::other_than_the_above);
    }

  protected:
    enum_type value;
};
}
