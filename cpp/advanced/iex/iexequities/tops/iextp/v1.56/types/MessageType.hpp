#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

// message_type
struct message_type {

    enum class enum_type : char {
        quote_update_message = 'Q',
        trade_report_message = 'T',
        trade_break_message = 'B'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Quote Update Message", enum_type::quote_update_message},
        {"Trade Break Message", enum_type::trade_break_message},
        {"Trade Report Message", enum_type::trade_report_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::quote_update_message: return "Quote Update Message";
            case enum_type::trade_report_message: return "Trade Report Message";
            case enum_type::trade_break_message: return "Trade Break Message";
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

    static constexpr const char* name = "message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<message_type::enum_type>;
    using storage_type = result_type;

    constexpr message_type()
     : value{ enum_type::quote_update_message } {}

    constexpr message_type(enum_type v)
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
            set(enum_type::trade_break_message);
    }

  protected:
    enum_type value;
};
}
