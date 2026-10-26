#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// message_category
struct message_category {

    enum class enum_type : char {
        administrative = 'C',
        control = 'H',
        equity_and_index_last_sale = 'a',
        open_interest = 'd',
        equity_and_index_end_of_day_summary = 'f',
        long_equity_and_index_quote = 'k',
        short_equity_and_index_quote = 'q',
        underlying_value = 'Y'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Administrative", enum_type::administrative},
        {"Control", enum_type::control},
        {"Equity And Index End Of Day Summary", enum_type::equity_and_index_end_of_day_summary},
        {"Equity And Index Last Sale", enum_type::equity_and_index_last_sale},
        {"Long Equity And Index Quote", enum_type::long_equity_and_index_quote},
        {"Open Interest", enum_type::open_interest},
        {"Short Equity And Index Quote", enum_type::short_equity_and_index_quote},
        {"Underlying Value", enum_type::underlying_value}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::administrative: return "Administrative";
            case enum_type::control: return "Control";
            case enum_type::equity_and_index_last_sale: return "Equity And Index Last Sale";
            case enum_type::open_interest: return "Open Interest";
            case enum_type::equity_and_index_end_of_day_summary: return "Equity And Index End Of Day Summary";
            case enum_type::long_equity_and_index_quote: return "Long Equity And Index Quote";
            case enum_type::short_equity_and_index_quote: return "Short Equity And Index Quote";
            case enum_type::underlying_value: return "Underlying Value";
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

    static constexpr const char* name = "message_category";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<message_category::enum_type>;
    using storage_type = result_type;

    constexpr message_category()
     : value{ enum_type{} } {}

    constexpr message_category(enum_type v)
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
            set(enum_type::underlying_value);
    }

  protected:
    enum_type value;
};
}
