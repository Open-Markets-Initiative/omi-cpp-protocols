// Databento.MarketData.Normalized.Dbn.v2: types/StatusReason.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// status_reason
struct status_reason {

    enum class enum_type : std::uint16_t {
        none = 0,
        scheduled = 1,
        surveillance_intervention = 2,
        market_event = 3,
        instrument_activation = 4,
        instrument_expiration = 5,
        recovery_in_process = 6,
        regulatory = 10,
        administrative = 11,
        non_compliance = 12,
        filings_not_current = 13,
        sec_trading_suspension = 14,
        new_issue = 15,
        issue_available = 16,
        issues_reviewed = 17,
        filing_reqs_satisfied = 18,
        news_pending = 30,
        news_released = 31,
        news_and_resumption_times = 32,
        news_not_forthcoming = 33,
        order_imbalance = 40,
        luld_pause = 50,
        operational = 60,
        additional_information_requested = 70,
        merger_effective = 80,
        etf = 90,
        corporate_action = 100,
        new_security_offering = 110,
        market_wide_halt_level1 = 120,
        market_wide_halt_level2 = 121,
        market_wide_halt_level3 = 122,
        market_wide_halt_carryover = 123,
        market_wide_halt_resumption = 124,
        quotation_not_available = 130
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 34> from_string_map = {{
        {"Additional Information Requested", enum_type::additional_information_requested},
        {"Administrative", enum_type::administrative},
        {"Corporate Action", enum_type::corporate_action},
        {"Etf", enum_type::etf},
        {"Filing Reqs Satisfied", enum_type::filing_reqs_satisfied},
        {"Filings Not Current", enum_type::filings_not_current},
        {"Instrument Activation", enum_type::instrument_activation},
        {"Instrument Expiration", enum_type::instrument_expiration},
        {"Issue Available", enum_type::issue_available},
        {"Issues Reviewed", enum_type::issues_reviewed},
        {"Luld Pause", enum_type::luld_pause},
        {"Market Event", enum_type::market_event},
        {"Market Wide Halt Carryover", enum_type::market_wide_halt_carryover},
        {"Market Wide Halt Level1", enum_type::market_wide_halt_level1},
        {"Market Wide Halt Level2", enum_type::market_wide_halt_level2},
        {"Market Wide Halt Level3", enum_type::market_wide_halt_level3},
        {"Market Wide Halt Resumption", enum_type::market_wide_halt_resumption},
        {"Merger Effective", enum_type::merger_effective},
        {"New Issue", enum_type::new_issue},
        {"New Security Offering", enum_type::new_security_offering},
        {"News And Resumption Times", enum_type::news_and_resumption_times},
        {"News Not Forthcoming", enum_type::news_not_forthcoming},
        {"News Pending", enum_type::news_pending},
        {"News Released", enum_type::news_released},
        {"Non Compliance", enum_type::non_compliance},
        {"None", enum_type::none},
        {"Operational", enum_type::operational},
        {"Order Imbalance", enum_type::order_imbalance},
        {"Quotation Not Available", enum_type::quotation_not_available},
        {"Recovery In Process", enum_type::recovery_in_process},
        {"Regulatory", enum_type::regulatory},
        {"Scheduled", enum_type::scheduled},
        {"Sec Trading Suspension", enum_type::sec_trading_suspension},
        {"Surveillance Intervention", enum_type::surveillance_intervention}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::none: return "None";
            case enum_type::scheduled: return "Scheduled";
            case enum_type::surveillance_intervention: return "Surveillance Intervention";
            case enum_type::market_event: return "Market Event";
            case enum_type::instrument_activation: return "Instrument Activation";
            case enum_type::instrument_expiration: return "Instrument Expiration";
            case enum_type::recovery_in_process: return "Recovery In Process";
            case enum_type::regulatory: return "Regulatory";
            case enum_type::administrative: return "Administrative";
            case enum_type::non_compliance: return "Non Compliance";
            case enum_type::filings_not_current: return "Filings Not Current";
            case enum_type::sec_trading_suspension: return "Sec Trading Suspension";
            case enum_type::new_issue: return "New Issue";
            case enum_type::issue_available: return "Issue Available";
            case enum_type::issues_reviewed: return "Issues Reviewed";
            case enum_type::filing_reqs_satisfied: return "Filing Reqs Satisfied";
            case enum_type::news_pending: return "News Pending";
            case enum_type::news_released: return "News Released";
            case enum_type::news_and_resumption_times: return "News And Resumption Times";
            case enum_type::news_not_forthcoming: return "News Not Forthcoming";
            case enum_type::order_imbalance: return "Order Imbalance";
            case enum_type::luld_pause: return "Luld Pause";
            case enum_type::operational: return "Operational";
            case enum_type::additional_information_requested: return "Additional Information Requested";
            case enum_type::merger_effective: return "Merger Effective";
            case enum_type::etf: return "Etf";
            case enum_type::corporate_action: return "Corporate Action";
            case enum_type::new_security_offering: return "New Security Offering";
            case enum_type::market_wide_halt_level1: return "Market Wide Halt Level1";
            case enum_type::market_wide_halt_level2: return "Market Wide Halt Level2";
            case enum_type::market_wide_halt_level3: return "Market Wide Halt Level3";
            case enum_type::market_wide_halt_carryover: return "Market Wide Halt Carryover";
            case enum_type::market_wide_halt_resumption: return "Market Wide Halt Resumption";
            case enum_type::quotation_not_available: return "Quotation Not Available";
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

    static constexpr const char* name = "status_reason";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<status_reason::enum_type>;
    using storage_type = result_type;

    constexpr status_reason()
     : value{ enum_type{} } {}

    constexpr status_reason(enum_type v)
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
            set(enum_type::quotation_not_available);
    }

  protected:
    enum_type value;
};
}
