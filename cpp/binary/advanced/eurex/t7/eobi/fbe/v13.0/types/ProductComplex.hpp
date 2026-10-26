#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// product_complex
struct product_complex {

    enum class enum_type : std::uint8_t {
        simple_instrument = 1,
        standard_option_strategy = 2,
        non_standard_option_strategy = 3,
        volatility_strategy = 4,
        futures_spread = 5,
        inter_product_spread = 6,
        standard_futures_strategy = 7,
        pack_and_bundle = 8,
        strip = 9,
        flexible_instrument = 10,
        commodity_strip = 11,
        scaled_simple_instrument = 12,
        non_standard_volatility_strategy = 13,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 14> from_string_map = {{
        {"Commodity Strip", enum_type::commodity_strip},
        {"Flexible Instrument", enum_type::flexible_instrument},
        {"Futures Spread", enum_type::futures_spread},
        {"Inter Product Spread", enum_type::inter_product_spread},
        {"No Value", enum_type::no_value},
        {"Non Standard Option Strategy", enum_type::non_standard_option_strategy},
        {"Non Standard Volatility Strategy", enum_type::non_standard_volatility_strategy},
        {"Pack And Bundle", enum_type::pack_and_bundle},
        {"Scaled Simple Instrument", enum_type::scaled_simple_instrument},
        {"Simple Instrument", enum_type::simple_instrument},
        {"Standard Futures Strategy", enum_type::standard_futures_strategy},
        {"Standard Option Strategy", enum_type::standard_option_strategy},
        {"Strip", enum_type::strip},
        {"Volatility Strategy", enum_type::volatility_strategy}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::simple_instrument: return "Simple Instrument";
            case enum_type::standard_option_strategy: return "Standard Option Strategy";
            case enum_type::non_standard_option_strategy: return "Non Standard Option Strategy";
            case enum_type::volatility_strategy: return "Volatility Strategy";
            case enum_type::futures_spread: return "Futures Spread";
            case enum_type::inter_product_spread: return "Inter Product Spread";
            case enum_type::standard_futures_strategy: return "Standard Futures Strategy";
            case enum_type::pack_and_bundle: return "Pack And Bundle";
            case enum_type::strip: return "Strip";
            case enum_type::flexible_instrument: return "Flexible Instrument";
            case enum_type::commodity_strip: return "Commodity Strip";
            case enum_type::scaled_simple_instrument: return "Scaled Simple Instrument";
            case enum_type::non_standard_volatility_strategy: return "Non Standard Volatility Strategy";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "product_complex";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<product_complex::enum_type>;
    using storage_type = result_type;

    constexpr product_complex()
     : value{ enum_type{} } {}

    constexpr product_complex(enum_type v)
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
            set(static_cast<enum_type>(0xFF));
    }

  protected:
    enum_type value;
};
}
