#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// multi_leg_price_method
struct multi_leg_price_method {

    enum class enum_type : std::uint8_t {
        net_price = 0,
        reversed_net_price = 1,
        yield_difference = 2,
        individual = 3,
        contract_weighted_average_price = 4,
        multiplied_price = 5,
        no_value = 255
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Contract Weighted Average Price", enum_type::contract_weighted_average_price},
        {"Individual", enum_type::individual},
        {"Multiplied Price", enum_type::multiplied_price},
        {"Net Price", enum_type::net_price},
        {"No Value", enum_type::no_value},
        {"Reversed Net Price", enum_type::reversed_net_price},
        {"Yield Difference", enum_type::yield_difference}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::net_price: return "Net Price";
            case enum_type::reversed_net_price: return "Reversed Net Price";
            case enum_type::yield_difference: return "Yield Difference";
            case enum_type::individual: return "Individual";
            case enum_type::contract_weighted_average_price: return "Contract Weighted Average Price";
            case enum_type::multiplied_price: return "Multiplied Price";
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

    static constexpr const char* name = "multi_leg_price_method";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<multi_leg_price_method::enum_type>;
    using storage_type = result_type;

    constexpr multi_leg_price_method()
     : value{ enum_type::net_price } {}

    constexpr multi_leg_price_method(enum_type v)
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
            set(static_cast<enum_type>(255));
    }

  protected:
    enum_type value;
};
}
