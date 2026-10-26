#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// cross_type
struct cross_type {

    enum class enum_type : char {
        opening_cross = 'O',
        scheduled_intraday_cross = 'I',
        closing_cross = 'C',
        cross_for_halted_securities = 'H',
        auction_on_demand = 'A'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Auction On Demand", enum_type::auction_on_demand},
        {"Closing Cross", enum_type::closing_cross},
        {"Cross For Halted Securities", enum_type::cross_for_halted_securities},
        {"Opening Cross", enum_type::opening_cross},
        {"Scheduled Intraday Cross", enum_type::scheduled_intraday_cross}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening_cross: return "Opening Cross";
            case enum_type::scheduled_intraday_cross: return "Scheduled Intraday Cross";
            case enum_type::closing_cross: return "Closing Cross";
            case enum_type::cross_for_halted_securities: return "Cross For Halted Securities";
            case enum_type::auction_on_demand: return "Auction On Demand";
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

    static constexpr const char* name = "cross_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<cross_type::enum_type>;
    using storage_type = result_type;

    constexpr cross_type()
     : value{ enum_type{} } {}

    constexpr cross_type(enum_type v)
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
            set(enum_type::auction_on_demand);
    }

  protected:
    enum_type value;
};
}
