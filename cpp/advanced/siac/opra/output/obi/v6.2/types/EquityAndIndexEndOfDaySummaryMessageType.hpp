#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// equity_and_index_end_of_day_summary_message_type
struct equity_and_index_end_of_day_summary_message_type {

    enum class enum_type : char {
        equity_and_index_end_of_day_summary = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 1> from_string_map = {{
        {"Equity And Index End Of Day Summary", enum_type::equity_and_index_end_of_day_summary}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::equity_and_index_end_of_day_summary: return "Equity And Index End Of Day Summary";
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

    static constexpr const char* name = "equity_and_index_end_of_day_summary_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<equity_and_index_end_of_day_summary_message_type::enum_type>;
    using storage_type = result_type;

    constexpr equity_and_index_end_of_day_summary_message_type()
     : value{ enum_type{} } {}

    constexpr equity_and_index_end_of_day_summary_message_type(enum_type v)
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
            set(enum_type::equity_and_index_end_of_day_summary);
    }

  protected:
    enum_type value;
};
}
