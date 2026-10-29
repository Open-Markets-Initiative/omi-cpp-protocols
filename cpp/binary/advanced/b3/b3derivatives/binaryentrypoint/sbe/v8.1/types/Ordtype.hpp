#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// ordtype
struct ordtype {

    enum class enum_type : char {
        market = '1',
        limit = '2',
        stop_loss = '3',
        stop_limit = '4',
        market_with_leftover_as_limit = 'K',
        rlp = 'W',
        pegged_midpoint = 'P'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Limit", enum_type::limit},
        {"Market", enum_type::market},
        {"Market With Leftover As Limit", enum_type::market_with_leftover_as_limit},
        {"Pegged Midpoint", enum_type::pegged_midpoint},
        {"Rlp", enum_type::rlp},
        {"Stop Limit", enum_type::stop_limit},
        {"Stop Loss", enum_type::stop_loss}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::market: return "Market";
            case enum_type::limit: return "Limit";
            case enum_type::stop_loss: return "Stop Loss";
            case enum_type::stop_limit: return "Stop Limit";
            case enum_type::market_with_leftover_as_limit: return "Market With Leftover As Limit";
            case enum_type::rlp: return "Rlp";
            case enum_type::pegged_midpoint: return "Pegged Midpoint";
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

    static constexpr const char* name = "ordtype";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<ordtype::enum_type>;
    using storage_type = result_type;

    constexpr ordtype()
     : value{ enum_type{} } {}

    constexpr ordtype(enum_type v)
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
            set(enum_type::pegged_midpoint);
    }

  protected:
    enum_type value;
};
}
