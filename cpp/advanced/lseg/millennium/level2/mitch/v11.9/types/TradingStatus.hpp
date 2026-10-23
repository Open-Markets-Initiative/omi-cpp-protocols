#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// trading_status
struct trading_status {

    enum class enum_type : char {
        active = ' ',
        halt = 'H',
        regular_trading_start_of_trade_reporting = 'T',
        opening_first_auction_call = 'a',
        post_close = 'b',
        market_close_system_shutdown = 'c',
        closing_auction_call = 'd',
        aesp_auction_call = 'e',
        resume_auction_call = 'f',
        pause = 'l',
        pre_mandatory = 'm',
        mandatory = 'n',
        post_mandatory = 'o',
        edsp_auction_call = 'q',
        periodic_auction_call = 'r',
        end_trade_reporting = 't',
        no_active_session = 'w',
        end_of_post_close = 'x',
        closing_price_crossing = 'u',
        scheduled_level_1_only_auction = 'G'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 20> from_string_map = {{
        {"Active", enum_type::active},
        {"Aesp Auction Call", enum_type::aesp_auction_call},
        {"Closing Auction Call", enum_type::closing_auction_call},
        {"Closing Price Crossing", enum_type::closing_price_crossing},
        {"Edsp Auction Call", enum_type::edsp_auction_call},
        {"End Of Post Close", enum_type::end_of_post_close},
        {"End Trade Reporting", enum_type::end_trade_reporting},
        {"Halt", enum_type::halt},
        {"Mandatory", enum_type::mandatory},
        {"Market Close System Shutdown", enum_type::market_close_system_shutdown},
        {"No Active Session", enum_type::no_active_session},
        {"Opening First Auction Call", enum_type::opening_first_auction_call},
        {"Pause", enum_type::pause},
        {"Periodic Auction Call", enum_type::periodic_auction_call},
        {"Post Close", enum_type::post_close},
        {"Post Mandatory", enum_type::post_mandatory},
        {"Pre Mandatory", enum_type::pre_mandatory},
        {"Regular Trading Start Of Trade Reporting", enum_type::regular_trading_start_of_trade_reporting},
        {"Resume Auction Call", enum_type::resume_auction_call},
        {"Scheduled Level 1 Only Auction", enum_type::scheduled_level_1_only_auction}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::active: return "Active";
            case enum_type::halt: return "Halt";
            case enum_type::regular_trading_start_of_trade_reporting: return "Regular Trading Start Of Trade Reporting";
            case enum_type::opening_first_auction_call: return "Opening First Auction Call";
            case enum_type::post_close: return "Post Close";
            case enum_type::market_close_system_shutdown: return "Market Close System Shutdown";
            case enum_type::closing_auction_call: return "Closing Auction Call";
            case enum_type::aesp_auction_call: return "Aesp Auction Call";
            case enum_type::resume_auction_call: return "Resume Auction Call";
            case enum_type::pause: return "Pause";
            case enum_type::pre_mandatory: return "Pre Mandatory";
            case enum_type::mandatory: return "Mandatory";
            case enum_type::post_mandatory: return "Post Mandatory";
            case enum_type::edsp_auction_call: return "Edsp Auction Call";
            case enum_type::periodic_auction_call: return "Periodic Auction Call";
            case enum_type::end_trade_reporting: return "End Trade Reporting";
            case enum_type::no_active_session: return "No Active Session";
            case enum_type::end_of_post_close: return "End Of Post Close";
            case enum_type::closing_price_crossing: return "Closing Price Crossing";
            case enum_type::scheduled_level_1_only_auction: return "Scheduled Level 1 Only Auction";
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

    static constexpr const char* name = "trading_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trading_status::enum_type>;
    using storage_type = result_type;

    constexpr trading_status()
     : value{ enum_type{} } {}

    constexpr trading_status(enum_type v)
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
            set(enum_type::scheduled_level_1_only_auction);
    }

  protected:
    enum_type value;
};
}
