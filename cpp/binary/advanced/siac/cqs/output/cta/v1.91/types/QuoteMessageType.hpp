#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// quote_message_type
struct quote_message_type {

    enum class enum_type : char {
        auction_status_message = 'A',
        long_quote_message = 'L',
        short_quote_message = 'Q',
        special_long_quote_message = 'S'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Auction Status Message", enum_type::auction_status_message},
        {"Long Quote Message", enum_type::long_quote_message},
        {"Short Quote Message", enum_type::short_quote_message},
        {"Special Long Quote Message", enum_type::special_long_quote_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::auction_status_message: return "Auction Status Message";
            case enum_type::long_quote_message: return "Long Quote Message";
            case enum_type::short_quote_message: return "Short Quote Message";
            case enum_type::special_long_quote_message: return "Special Long Quote Message";
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

    static constexpr const char* name = "quote_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<quote_message_type::enum_type>;
    using storage_type = result_type;

    constexpr quote_message_type()
     : value{ enum_type{} } {}

    constexpr quote_message_type(enum_type v)
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
            set(enum_type::special_long_quote_message);
    }

  protected:
    enum_type value;
};
}
