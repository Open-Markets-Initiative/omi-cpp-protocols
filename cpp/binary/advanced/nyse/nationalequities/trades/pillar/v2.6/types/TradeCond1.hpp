#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

// trade_cond_1
struct trade_cond_1 {

    enum class enum_type : char {
        regular_sale = '@',
        cash = 'C',
        regular_sale_trf_only = ' ',
        seller_trf_only = 'R'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Cash", enum_type::cash},
        {"Regular Sale", enum_type::regular_sale},
        {"Regular Sale Trf Only", enum_type::regular_sale_trf_only},
        {"Seller Trf Only", enum_type::seller_trf_only}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular_sale: return "Regular Sale";
            case enum_type::cash: return "Cash";
            case enum_type::regular_sale_trf_only: return "Regular Sale Trf Only";
            case enum_type::seller_trf_only: return "Seller Trf Only";
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

    static constexpr const char* name = "trade_cond_1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_cond_1::enum_type>;
    using storage_type = result_type;

    constexpr trade_cond_1()
     : value{ enum_type{} } {}

    constexpr trade_cond_1(enum_type v)
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
            set(enum_type::seller_trf_only);
    }

  protected:
    enum_type value;
};
}
