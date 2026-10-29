#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

// auction_type
struct auction_type {

    enum class enum_type : char {
        early_opening_auction = 'O',
        core_opening_auction = 'M',
        reopening_auction_halt_resume = 'H',
        closing_auction = 'C',
        extreme_closing_imbalance = 'P',
        significant_closing_imbalance = 'R'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Closing Auction", enum_type::closing_auction},
        {"Core Opening Auction", enum_type::core_opening_auction},
        {"Early Opening Auction", enum_type::early_opening_auction},
        {"Extreme Closing Imbalance", enum_type::extreme_closing_imbalance},
        {"Reopening Auction Halt Resume", enum_type::reopening_auction_halt_resume},
        {"Significant Closing Imbalance", enum_type::significant_closing_imbalance}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::early_opening_auction: return "Early Opening Auction";
            case enum_type::core_opening_auction: return "Core Opening Auction";
            case enum_type::reopening_auction_halt_resume: return "Reopening Auction Halt Resume";
            case enum_type::closing_auction: return "Closing Auction";
            case enum_type::extreme_closing_imbalance: return "Extreme Closing Imbalance";
            case enum_type::significant_closing_imbalance: return "Significant Closing Imbalance";
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
            set(enum_type::significant_closing_imbalance);
    }

  protected:
    enum_type value;
};
}
