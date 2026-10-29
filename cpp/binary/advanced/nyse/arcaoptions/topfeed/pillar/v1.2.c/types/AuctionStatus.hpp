#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// auction_status
struct auction_status {

    enum class enum_type : std::uint8_t {
        usual = 0,
        legal_width_quote_does_not_exist = 4,
        market_maker_quote_is_not_received = 5
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Legal Width Quote Does Not Exist", enum_type::legal_width_quote_does_not_exist},
        {"Market Maker Quote Is Not Received", enum_type::market_maker_quote_is_not_received},
        {"Usual", enum_type::usual}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::usual: return "Usual";
            case enum_type::legal_width_quote_does_not_exist: return "Legal Width Quote Does Not Exist";
            case enum_type::market_maker_quote_is_not_received: return "Market Maker Quote Is Not Received";
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

    static constexpr const char* name = "auction_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<auction_status::enum_type>;
    using storage_type = result_type;

    constexpr auction_status()
     : value{ enum_type{} } {}

    constexpr auction_status(enum_type v)
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
            set(enum_type::market_maker_quote_is_not_received);
    }

  protected:
    enum_type value;
};
}
