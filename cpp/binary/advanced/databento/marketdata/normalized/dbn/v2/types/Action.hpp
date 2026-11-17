// Databento.MarketData.Normalized.Dbn.v2: types/Action.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// action
struct action {

    enum class enum_type : char {
        add = 'A',
        cancel = 'C',
        fill = 'F',
        modify = 'M',
        none = 'N',
        clear = 'R',
        trade = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Add", enum_type::add},
        {"Cancel", enum_type::cancel},
        {"Clear", enum_type::clear},
        {"Fill", enum_type::fill},
        {"Modify", enum_type::modify},
        {"None", enum_type::none},
        {"Trade", enum_type::trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::add: return "Add";
            case enum_type::cancel: return "Cancel";
            case enum_type::fill: return "Fill";
            case enum_type::modify: return "Modify";
            case enum_type::none: return "None";
            case enum_type::clear: return "Clear";
            case enum_type::trade: return "Trade";
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

    static constexpr const char* name = "action";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<action::enum_type>;
    using storage_type = result_type;

    constexpr action()
     : value{ enum_type{} } {}

    constexpr action(enum_type v)
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
            set(enum_type::trade);
    }

  protected:
    enum_type value;
};
}
