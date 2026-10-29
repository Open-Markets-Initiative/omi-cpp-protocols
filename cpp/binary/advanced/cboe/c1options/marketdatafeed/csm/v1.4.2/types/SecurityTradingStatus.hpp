#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// security_trading_status
struct security_trading_status {

    enum class enum_type : std::uint8_t {
        halted = 2,
        open = 17,
        closed = 18,
        pre_open = 21,
        opening_rotation = 22,
        fast_market = 23,
        strategy_market_in_opening_rotation = 24,
        strategy_market_quotes_non_firm = 25,
        suspended = 26
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Closed", enum_type::closed},
        {"Fast Market", enum_type::fast_market},
        {"Halted", enum_type::halted},
        {"Open", enum_type::open},
        {"Opening Rotation", enum_type::opening_rotation},
        {"Pre Open", enum_type::pre_open},
        {"Strategy Market In Opening Rotation", enum_type::strategy_market_in_opening_rotation},
        {"Strategy Market Quotes Non Firm", enum_type::strategy_market_quotes_non_firm},
        {"Suspended", enum_type::suspended}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::halted: return "Halted";
            case enum_type::open: return "Open";
            case enum_type::closed: return "Closed";
            case enum_type::pre_open: return "Pre Open";
            case enum_type::opening_rotation: return "Opening Rotation";
            case enum_type::fast_market: return "Fast Market";
            case enum_type::strategy_market_in_opening_rotation: return "Strategy Market In Opening Rotation";
            case enum_type::strategy_market_quotes_non_firm: return "Strategy Market Quotes Non Firm";
            case enum_type::suspended: return "Suspended";
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

    static constexpr const char* name = "security_trading_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_trading_status::enum_type>;
    using storage_type = result_type;

    constexpr security_trading_status()
     : value{ enum_type{} } {}

    constexpr security_trading_status(enum_type v)
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
            set(enum_type::suspended);
    }

  protected:
    enum_type value;
};
}
