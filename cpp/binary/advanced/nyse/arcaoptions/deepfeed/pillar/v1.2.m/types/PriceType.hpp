#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// price_type
struct price_type {

    enum class enum_type : std::uint8_t {
        strike_price_is_amount_0 = 0,
        strike_price_is_amount_1 = 1
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Strike Price Is Amount", enum_type::strike_price_is_amount_0},
        {"Strike Price Is Amount", enum_type::strike_price_is_amount_1}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::strike_price_is_amount_0: return "Strike Price Is Amount";
            case enum_type::strike_price_is_amount_1: return "Strike Price Is Amount";
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

    static constexpr const char* name = "price_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<price_type::enum_type>;
    using storage_type = result_type;

    constexpr price_type()
     : value{ enum_type{} } {}

    constexpr price_type(enum_type v)
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
            set(enum_type::strike_price_is_amount_1);
    }

  protected:
    enum_type value;
};
}
