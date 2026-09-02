#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

// auction_type
struct auction_type {

    enum class enum_type : char {
        opening_auction = 'O',
        closing_auction = 'C',
        ipo_auction = 'I',
        halt_auction = 'H',
        volatility_auction = 'V'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Closing Auction", enum_type::closing_auction},
        {"Halt Auction", enum_type::halt_auction},
        {"Ipo Auction", enum_type::ipo_auction},
        {"Opening Auction", enum_type::opening_auction},
        {"Volatility Auction", enum_type::volatility_auction}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening_auction: return "Opening Auction";
            case enum_type::closing_auction: return "Closing Auction";
            case enum_type::ipo_auction: return "Ipo Auction";
            case enum_type::halt_auction: return "Halt Auction";
            case enum_type::volatility_auction: return "Volatility Auction";
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

    static constexpr const char* name = "auction_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<auction_type::enum_type>;
    using storage_type = result_type;

    constexpr auction_type()
     : value{ enum_type::opening_auction } {}

    constexpr auction_type(enum_type v)
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
            set(enum_type::volatility_auction);
    }

  protected:
    enum_type value;
};
}
