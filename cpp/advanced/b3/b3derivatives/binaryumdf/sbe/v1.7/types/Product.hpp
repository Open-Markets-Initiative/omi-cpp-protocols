#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// product
struct product {

    enum class enum_type : std::uint8_t {
        commodity = 2,
        corporate = 3,
        currency = 4,
        equity = 5,
        government = 6,
        index = 7,
        economic_indicator = 15,
        multileg = 16
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Commodity", enum_type::commodity},
        {"Corporate", enum_type::corporate},
        {"Currency", enum_type::currency},
        {"Economic Indicator", enum_type::economic_indicator},
        {"Equity", enum_type::equity},
        {"Government", enum_type::government},
        {"Index", enum_type::index},
        {"Multileg", enum_type::multileg}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::commodity: return "Commodity";
            case enum_type::corporate: return "Corporate";
            case enum_type::currency: return "Currency";
            case enum_type::equity: return "Equity";
            case enum_type::government: return "Government";
            case enum_type::index: return "Index";
            case enum_type::economic_indicator: return "Economic Indicator";
            case enum_type::multileg: return "Multileg";
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

    static constexpr const char* name = "product";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<product::enum_type>;
    using storage_type = result_type;

    constexpr product()
     : value{ enum_type::commodity } {}

    constexpr product(enum_type v)
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
            set(enum_type::multileg);
    }

  protected:
    enum_type value;
};
}
