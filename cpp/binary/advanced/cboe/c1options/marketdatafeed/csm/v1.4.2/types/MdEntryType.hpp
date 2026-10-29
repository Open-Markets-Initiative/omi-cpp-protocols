#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// md_entry_type
struct md_entry_type {

    enum class enum_type : char {
        bid = '0',
        ask = '1',
        trade = '2',
        index_value = '3',
        opening_price = '4',
        settlement_value = '6',
        high = '7',
        low = '8'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Ask", enum_type::ask},
        {"Bid", enum_type::bid},
        {"High", enum_type::high},
        {"Index Value", enum_type::index_value},
        {"Low", enum_type::low},
        {"Opening Price", enum_type::opening_price},
        {"Settlement Value", enum_type::settlement_value},
        {"Trade", enum_type::trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::bid: return "Bid";
            case enum_type::ask: return "Ask";
            case enum_type::trade: return "Trade";
            case enum_type::index_value: return "Index Value";
            case enum_type::opening_price: return "Opening Price";
            case enum_type::settlement_value: return "Settlement Value";
            case enum_type::high: return "High";
            case enum_type::low: return "Low";
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

    static constexpr const char* name = "md_entry_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_entry_type::enum_type>;
    using storage_type = result_type;

    constexpr md_entry_type()
     : value{ enum_type{} } {}

    constexpr md_entry_type(enum_type v)
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
            set(enum_type::low);
    }

  protected:
    enum_type value;
};
}
