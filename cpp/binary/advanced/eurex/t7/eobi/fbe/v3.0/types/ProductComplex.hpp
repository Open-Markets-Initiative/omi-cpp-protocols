#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

// product_complex
struct product_complex {

    enum class enum_type : std::uint8_t {
        futures_spread = 5,
        inter_product_spread = 6,
        standard_futures_strategy = 7,
        pack_and_bundle = 8,
        strip = 9,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Futures Spread", enum_type::futures_spread},
        {"Inter Product Spread", enum_type::inter_product_spread},
        {"No Value", enum_type::no_value},
        {"Pack And Bundle", enum_type::pack_and_bundle},
        {"Standard Futures Strategy", enum_type::standard_futures_strategy},
        {"Strip", enum_type::strip}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::futures_spread: return "Futures Spread";
            case enum_type::inter_product_spread: return "Inter Product Spread";
            case enum_type::standard_futures_strategy: return "Standard Futures Strategy";
            case enum_type::pack_and_bundle: return "Pack And Bundle";
            case enum_type::strip: return "Strip";
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
