// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/MarketState.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// market_state
struct market_state {

    enum class enum_type : char {
        pre_open = 'P',
        opening = 'O',
        open = 'S',
        moc_imbalance = 'M',
        ccp_determination = 'A',
        price_movement_extension = 'E',
        closing = 'L',
        extended_hours_cxls = 'N',
        extended_hours_open = 'R',
        extended_hours_close = 'F',
        closed = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Ccp Determination", enum_type::ccp_determination},
        {"Closed", enum_type::closed},
        {"Closing", enum_type::closing},
        {"Extended Hours Close", enum_type::extended_hours_close},
        {"Extended Hours Cxls", enum_type::extended_hours_cxls},
        {"Extended Hours Open", enum_type::extended_hours_open},
        {"Moc Imbalance", enum_type::moc_imbalance},
        {"Open", enum_type::open},
        {"Opening", enum_type::opening},
        {"Pre Open", enum_type::pre_open},
        {"Price Movement Extension", enum_type::price_movement_extension}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::pre_open: return "Pre Open";
            case enum_type::opening: return "Opening";
            case enum_type::open: return "Open";
            case enum_type::moc_imbalance: return "Moc Imbalance";
            case enum_type::ccp_determination: return "Ccp Determination";
            case enum_type::price_movement_extension: return "Price Movement Extension";
            case enum_type::closing: return "Closing";
            case enum_type::extended_hours_cxls: return "Extended Hours Cxls";
            case enum_type::extended_hours_open: return "Extended Hours Open";
            case enum_type::extended_hours_close: return "Extended Hours Close";
            case enum_type::closed: return "Closed";
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

    static constexpr const char* name = "market_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<market_state::enum_type>;
    using storage_type = result_type;

    constexpr market_state()
     : value{ enum_type{} } {}

    constexpr market_state(enum_type v)
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
            set(enum_type::closed);
    }

  protected:
    enum_type value;
};
}
