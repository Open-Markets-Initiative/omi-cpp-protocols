#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// trading_status
struct trading_status {

    enum class enum_type : char {
        halt = 'H',
        halt_matching_partition_suspended = 'J',
        halt_system_suspended = 'K',
        regular_trading_start_trade_reporting = 'T',
        halt_regulatory = 'P',
        end_trade_reporting = 't',
        opening_auction_call = 'a',
        post_close = 'b',
        closed = 'c',
        closing_auction_call = 'd',
        aesp_auction_call = 'e',
        resume_auction = 'f',
        pre_mandatory = 'm',
        mandatory = 'n',
        post_mandatory = 'o',
        edsp_auction_call = 'q',
        periodic_auction_call = 'r',
        inactive = '1',
        suspended = '2',
        no_active_session = 'w',
        end_of_post_close = 'x',
        closing_price_crossing_session = 'u'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 22> from_string_map = {{
        {"Aesp Auction Call", enum_type::aesp_auction_call},
        {"Closed", enum_type::closed},
        {"Closing Auction Call", enum_type::closing_auction_call},
        {"Closing Price Crossing Session", enum_type::closing_price_crossing_session},
        {"Edsp Auction Call", enum_type::edsp_auction_call},
        {"End Of Post Close", enum_type::end_of_post_close},
        {"End Trade Reporting", enum_type::end_trade_reporting},
        {"Halt", enum_type::halt},
        {"Halt Matching Partition Suspended", enum_type::halt_matching_partition_suspended},
        {"Halt Regulatory", enum_type::halt_regulatory},
        {"Halt System Suspended", enum_type::halt_system_suspended},
        {"Inactive", enum_type::inactive},
        {"Mandatory", enum_type::mandatory},
        {"No Active Session", enum_type::no_active_session},
        {"Opening Auction Call", enum_type::opening_auction_call},
        {"Periodic Auction Call", enum_type::periodic_auction_call},
        {"Post Close", enum_type::post_close},
        {"Post Mandatory", enum_type::post_mandatory},
        {"Pre Mandatory", enum_type::pre_mandatory},
        {"Regular Trading Start Trade Reporting", enum_type::regular_trading_start_trade_reporting},
        {"Resume Auction", enum_type::resume_auction},
        {"Suspended", enum_type::suspended}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::halt: return "Halt";
            case enum_type::halt_matching_partition_suspended: return "Halt Matching Partition Suspended";
            case enum_type::halt_system_suspended: return "Halt System Suspended";
            case enum_type::regular_trading_start_trade_reporting: return "Regular Trading Start Trade Reporting";
            case enum_type::halt_regulatory: return "Halt Regulatory";
            case enum_type::end_trade_reporting: return "End Trade Reporting";
            case enum_type::opening_auction_call: return "Opening Auction Call";
            case enum_type::post_close: return "Post Close";
            case enum_type::closed: return "Closed";
            case enum_type::closing_auction_call: return "Closing Auction Call";
            case enum_type::aesp_auction_call: return "Aesp Auction Call";
            case enum_type::resume_auction: return "Resume Auction";
            case enum_type::pre_mandatory: return "Pre Mandatory";
            case enum_type::mandatory: return "Mandatory";
            case enum_type::post_mandatory: return "Post Mandatory";
            case enum_type::edsp_auction_call: return "Edsp Auction Call";
            case enum_type::periodic_auction_call: return "Periodic Auction Call";
            case enum_type::inactive: return "Inactive";
            case enum_type::suspended: return "Suspended";
            case enum_type::no_active_session: return "No Active Session";
            case enum_type::end_of_post_close: return "End Of Post Close";
            case enum_type::closing_price_crossing_session: return "Closing Price Crossing Session";
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
            set(enum_type::closing_price_crossing_session);
    }

  protected:
    enum_type value;
};
}
