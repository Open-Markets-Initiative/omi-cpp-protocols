#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// triggered_side
struct triggered_side {

    enum class enum_type : char {
        sell_order = 'S',
        buy_order = 'B',
        itayose_execution = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Buy Order", enum_type::buy_order},
        {"Itayose Execution", enum_type::itayose_execution},
        {"Sell Order", enum_type::sell_order}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::sell_order: return "Sell Order";
            case enum_type::buy_order: return "Buy Order";
            case enum_type::itayose_execution: return "Itayose Execution";
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

    static constexpr const char* name = "triggered_side";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<triggered_side::enum_type>;
    using storage_type = result_type;

    constexpr triggered_side()
     : value{ enum_type::sell_order } {}

    constexpr triggered_side(enum_type v)
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
            set(enum_type::itayose_execution);
    }

  protected:
    enum_type value;
};
}
