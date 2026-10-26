#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// sub_book
struct sub_book {

    enum class enum_type : std::uint8_t {
        regular_trades = 0,
        rfq_trades = 11
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Regular Trades", enum_type::regular_trades},
        {"Rfq Trades", enum_type::rfq_trades}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular_trades: return "Regular Trades";
            case enum_type::rfq_trades: return "Rfq Trades";
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

    static constexpr const char* name = "sub_book";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<sub_book::enum_type>;
    using storage_type = result_type;

    constexpr sub_book()
     : value{ enum_type{} } {}

    constexpr sub_book(enum_type v)
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
            set(enum_type::rfq_trades);
    }

  protected:
    enum_type value;
};
}
