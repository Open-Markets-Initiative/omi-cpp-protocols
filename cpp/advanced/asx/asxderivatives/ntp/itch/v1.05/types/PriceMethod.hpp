#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// price_method
struct price_method {

    enum class enum_type : std::uint8_t {
        net_price = 0,
        yield_difference = 2,
        individual = 3,
        average_price = 4
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Average Price", enum_type::average_price},
        {"Individual", enum_type::individual},
        {"Net Price", enum_type::net_price},
        {"Yield Difference", enum_type::yield_difference}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::net_price: return "Net Price";
            case enum_type::yield_difference: return "Yield Difference";
            case enum_type::individual: return "Individual";
            case enum_type::average_price: return "Average Price";
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

    static constexpr const char* name = "price_method";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<price_method::enum_type>;
    using storage_type = result_type;

    constexpr price_method()
     : value{ enum_type{} } {}

    constexpr price_method(enum_type v)
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
            set(enum_type::average_price);
    }

  protected:
    enum_type value;
};
}
