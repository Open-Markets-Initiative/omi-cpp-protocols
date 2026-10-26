#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v9 {

// template_id
struct template_id {

    enum class enum_type : std::uint16_t {
        channel_reset = 4,
        admin_heartbeat = 12,
        admin_login = 15,
        admin_logout = 16,
        md_instrument_definition_future_legacy = 27,
        md_instrument_definition_spread_legacy = 29,
        security_status = 30,
        md_incremental_refresh_book_legacy = 32,
        md_incremental_refresh_daily_statistics_legacy = 33,
        md_incremental_refresh_limits_banding_legacy = 34,
        md_incremental_refresh_session_statistics_legacy = 35,
        md_incremental_refresh_volume = 37,
        snapshot_full_refresh_legacy = 38,
        quote_request = 39,
        md_instrument_definition_option_legacy = 41,
        md_incremental_refresh_trade_summary_legacy = 42,
        md_incremental_refresh_order_book_legacy = 43,
        snapshot_full_refresh_order_book_legacy = 44,
        md_incremental_refresh_book = 46,
        md_incremental_refresh_order_book = 47,
        md_incremental_refresh_trade_summary = 48,
        md_incremental_refresh_daily_statistics = 49,
        md_incremental_refresh_limits_banding = 50,
        md_incremental_refresh_session_statistics = 51,
        snapshot_full_refresh = 52,
        snapshot_full_refresh_order_book = 53,
        md_instrument_definition_future = 54,
        md_instrument_definition_option = 55,
        md_instrument_definition_spread = 56,
        negotiate = 200,
        negotiation_reject = 201,
        negotiation_response = 202,
        terminate = 203,
        market_data_request = 205,
        request_ack = 206,
        request_reject = 207,
        security_list_request = 208,
        security_status_request = 209,
        subscriber_heartbeat = 210
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 39> from_string_map = {{
        {"Admin Heartbeat", enum_type::admin_heartbeat},
        {"Admin Login", enum_type::admin_login},
        {"Admin Logout", enum_type::admin_logout},
        {"Channel Reset", enum_type::channel_reset},
        {"Market Data Request", enum_type::market_data_request},
        {"Md Incremental Refresh Book", enum_type::md_incremental_refresh_book},
        {"Md Incremental Refresh Book Legacy", enum_type::md_incremental_refresh_book_legacy},
        {"Md Incremental Refresh Daily Statistics", enum_type::md_incremental_refresh_daily_statistics},
        {"Md Incremental Refresh Daily Statistics Legacy", enum_type::md_incremental_refresh_daily_statistics_legacy},
        {"Md Incremental Refresh Limits Banding", enum_type::md_incremental_refresh_limits_banding},
        {"Md Incremental Refresh Limits Banding Legacy", enum_type::md_incremental_refresh_limits_banding_legacy},
        {"Md Incremental Refresh Order Book", enum_type::md_incremental_refresh_order_book},
        {"Md Incremental Refresh Order Book Legacy", enum_type::md_incremental_refresh_order_book_legacy},
        {"Md Incremental Refresh Session Statistics", enum_type::md_incremental_refresh_session_statistics},
        {"Md Incremental Refresh Session Statistics Legacy", enum_type::md_incremental_refresh_session_statistics_legacy},
        {"Md Incremental Refresh Trade Summary", enum_type::md_incremental_refresh_trade_summary},
        {"Md Incremental Refresh Trade Summary Legacy", enum_type::md_incremental_refresh_trade_summary_legacy},
        {"Md Incremental Refresh Volume", enum_type::md_incremental_refresh_volume},
        {"Md Instrument Definition Future", enum_type::md_instrument_definition_future},
        {"Md Instrument Definition Future Legacy", enum_type::md_instrument_definition_future_legacy},
        {"Md Instrument Definition Option", enum_type::md_instrument_definition_option},
        {"Md Instrument Definition Option Legacy", enum_type::md_instrument_definition_option_legacy},
        {"Md Instrument Definition Spread", enum_type::md_instrument_definition_spread},
        {"Md Instrument Definition Spread Legacy", enum_type::md_instrument_definition_spread_legacy},
        {"Negotiate", enum_type::negotiate},
        {"Negotiation Reject", enum_type::negotiation_reject},
        {"Negotiation Response", enum_type::negotiation_response},
        {"Quote Request", enum_type::quote_request},
        {"Request Ack", enum_type::request_ack},
        {"Request Reject", enum_type::request_reject},
        {"Security List Request", enum_type::security_list_request},
        {"Security Status", enum_type::security_status},
        {"Security Status Request", enum_type::security_status_request},
        {"Snapshot Full Refresh", enum_type::snapshot_full_refresh},
        {"Snapshot Full Refresh Legacy", enum_type::snapshot_full_refresh_legacy},
        {"Snapshot Full Refresh Order Book", enum_type::snapshot_full_refresh_order_book},
        {"Snapshot Full Refresh Order Book Legacy", enum_type::snapshot_full_refresh_order_book_legacy},
        {"Subscriber Heartbeat", enum_type::subscriber_heartbeat},
        {"Terminate", enum_type::terminate}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::channel_reset: return "Channel Reset";
            case enum_type::admin_heartbeat: return "Admin Heartbeat";
            case enum_type::admin_login: return "Admin Login";
            case enum_type::admin_logout: return "Admin Logout";
            case enum_type::md_instrument_definition_future_legacy: return "Md Instrument Definition Future Legacy";
            case enum_type::md_instrument_definition_spread_legacy: return "Md Instrument Definition Spread Legacy";
            case enum_type::security_status: return "Security Status";
            case enum_type::md_incremental_refresh_book_legacy: return "Md Incremental Refresh Book Legacy";
            case enum_type::md_incremental_refresh_daily_statistics_legacy: return "Md Incremental Refresh Daily Statistics Legacy";
            case enum_type::md_incremental_refresh_limits_banding_legacy: return "Md Incremental Refresh Limits Banding Legacy";
            case enum_type::md_incremental_refresh_session_statistics_legacy: return "Md Incremental Refresh Session Statistics Legacy";
            case enum_type::md_incremental_refresh_volume: return "Md Incremental Refresh Volume";
            case enum_type::snapshot_full_refresh_legacy: return "Snapshot Full Refresh Legacy";
            case enum_type::quote_request: return "Quote Request";
            case enum_type::md_instrument_definition_option_legacy: return "Md Instrument Definition Option Legacy";
            case enum_type::md_incremental_refresh_trade_summary_legacy: return "Md Incremental Refresh Trade Summary Legacy";
            case enum_type::md_incremental_refresh_order_book_legacy: return "Md Incremental Refresh Order Book Legacy";
            case enum_type::snapshot_full_refresh_order_book_legacy: return "Snapshot Full Refresh Order Book Legacy";
            case enum_type::md_incremental_refresh_book: return "Md Incremental Refresh Book";
            case enum_type::md_incremental_refresh_order_book: return "Md Incremental Refresh Order Book";
            case enum_type::md_incremental_refresh_trade_summary: return "Md Incremental Refresh Trade Summary";
            case enum_type::md_incremental_refresh_daily_statistics: return "Md Incremental Refresh Daily Statistics";
            case enum_type::md_incremental_refresh_limits_banding: return "Md Incremental Refresh Limits Banding";
            case enum_type::md_incremental_refresh_session_statistics: return "Md Incremental Refresh Session Statistics";
            case enum_type::snapshot_full_refresh: return "Snapshot Full Refresh";
            case enum_type::snapshot_full_refresh_order_book: return "Snapshot Full Refresh Order Book";
            case enum_type::md_instrument_definition_future: return "Md Instrument Definition Future";
            case enum_type::md_instrument_definition_option: return "Md Instrument Definition Option";
            case enum_type::md_instrument_definition_spread: return "Md Instrument Definition Spread";
            case enum_type::negotiate: return "Negotiate";
            case enum_type::negotiation_reject: return "Negotiation Reject";
            case enum_type::negotiation_response: return "Negotiation Response";
            case enum_type::terminate: return "Terminate";
            case enum_type::market_data_request: return "Market Data Request";
            case enum_type::request_ack: return "Request Ack";
            case enum_type::request_reject: return "Request Reject";
            case enum_type::security_list_request: return "Security List Request";
            case enum_type::security_status_request: return "Security Status Request";
            case enum_type::subscriber_heartbeat: return "Subscriber Heartbeat";
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

    static constexpr const char* name = "template_id";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<template_id::enum_type>;
    using storage_type = result_type;

    constexpr template_id()
     : value{ enum_type{} } {}

    constexpr template_id(enum_type v)
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
            set(enum_type::subscriber_heartbeat);
    }

  protected:
    enum_type value;
};
}
