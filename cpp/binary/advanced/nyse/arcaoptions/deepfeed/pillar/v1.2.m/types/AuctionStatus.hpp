#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// auction_status
struct auction_status {

    enum class enum_type : std::uint8_t {
        will_run_as_usual = 0,
        auction_will_not_run_because_legal_width_quote_does_not_exist = 4,
        auction_will_not_run_because_market_maker_quote_is_not_received = 5
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Auction Will Not Run Because Legal Width Quote Does Not Exist", enum_type::auction_will_not_run_because_legal_width_quote_does_not_exist},
        {"Auction Will Not Run Because Market Maker Quote Is Not Received", enum_type::auction_will_not_run_because_market_maker_quote_is_not_received},
        {"Will Run As Usual", enum_type::will_run_as_usual}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::will_run_as_usual: return "Will Run As Usual";
            case enum_type::auction_will_not_run_because_legal_width_quote_does_not_exist: return "Auction Will Not Run Because Legal Width Quote Does Not Exist";
            case enum_type::auction_will_not_run_because_market_maker_quote_is_not_received: return "Auction Will Not Run Because Market Maker Quote Is Not Received";
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
            set(enum_type::auction_will_not_run_because_market_maker_quote_is_not_received);
    }

  protected:
    enum_type value;
};
}
