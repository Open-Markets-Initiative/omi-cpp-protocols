#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// quote_message_type
struct quote_message_type {

    enum class enum_type : char {
        auction_status = 'A',
        long_quote = 'L',
        short_quote = 'Q',
        special_long_quote = 'S'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Auction Status", enum_type::auction_status},
        {"Long Quote", enum_type::long_quote},
        {"Short Quote", enum_type::short_quote},
        {"Special Long Quote", enum_type::special_long_quote}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::auction_status: return "Auction Status";
            case enum_type::long_quote: return "Long Quote";
            case enum_type::short_quote: return "Short Quote";
            case enum_type::special_long_quote: return "Special Long Quote";
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
            set(enum_type::special_long_quote);
    }

  protected:
    enum_type value;
};
}
