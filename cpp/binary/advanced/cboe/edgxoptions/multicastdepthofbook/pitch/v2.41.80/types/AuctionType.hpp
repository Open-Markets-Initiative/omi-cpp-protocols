#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// auction_type
struct auction_type {

    enum class enum_type : char {
        opening_auction = 'O',
        closing_auction = 'C',
        gth_opening = 'G',
        halt_auction = 'H',
        ipo_auction = 'I',
        cboe_market_close = 'M',
        volitility_auction = 'V',
        periodic_auction = 'P'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 8> from_string_map = {{
        {"Cboe Market Close", enum_type::cboe_market_close},
        {"Closing Auction", enum_type::closing_auction},
        {"Gth Opening", enum_type::gth_opening},
        {"Halt Auction", enum_type::halt_auction},
        {"Ipo Auction", enum_type::ipo_auction},
        {"Opening Auction", enum_type::opening_auction},
        {"Periodic Auction", enum_type::periodic_auction},
        {"Volitility Auction", enum_type::volitility_auction}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening_auction: return "Opening Auction";
            case enum_type::closing_auction: return "Closing Auction";
            case enum_type::gth_opening: return "Gth Opening";
            case enum_type::halt_auction: return "Halt Auction";
            case enum_type::ipo_auction: return "Ipo Auction";
            case enum_type::cboe_market_close: return "Cboe Market Close";
            case enum_type::volitility_auction: return "Volitility Auction";
            case enum_type::periodic_auction: return "Periodic Auction";
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
     : value{ enum_type{} } {}

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
            set(enum_type::periodic_auction);
    }

  protected:
    enum_type value;
};
}
