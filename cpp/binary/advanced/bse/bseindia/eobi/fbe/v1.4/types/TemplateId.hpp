#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// template_id
struct template_id {

    enum class enum_type : std::uint16_t {
        heartbeat_message = 13001,
        product_summary_message = 13600,
        snapshot_order_message = 13602,
        instrument_summary_message = 13601,
        auction_best_bid_offer_message = 13500,
        auction_clearing_price_message = 13501,
        top_of_book_message = 13504,
        order_add_message = 13100,
        order_modify_message = 13101,
        order_modify_same_priority_message = 13106,
        order_delete_message = 13102,
        order_mass_delete_message = 13103,
        partial_order_execution_message = 13105,
        full_order_execution_message = 13104,
        trade_reversal_message = 13200,
        execution_summary_message = 13202,
        instrument_info_message = 13203,
        lpp_range_message = 13204,
        product_state_change_message = 13300,
        instrument_state_change_message = 13301,
        add_complex_instrument_message = 13400,
        packet_header = 13002
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 22> from_string_map = {{
        {"Add Complex Instrument Message", enum_type::add_complex_instrument_message},
        {"Auction Best Bid Offer Message", enum_type::auction_best_bid_offer_message},
        {"Auction Clearing Price Message", enum_type::auction_clearing_price_message},
        {"Execution Summary Message", enum_type::execution_summary_message},
        {"Full Order Execution Message", enum_type::full_order_execution_message},
        {"Heartbeat Message", enum_type::heartbeat_message},
        {"Instrument Info Message", enum_type::instrument_info_message},
        {"Instrument State Change Message", enum_type::instrument_state_change_message},
        {"Instrument Summary Message", enum_type::instrument_summary_message},
        {"Lpp Range Message", enum_type::lpp_range_message},
        {"Order Add Message", enum_type::order_add_message},
        {"Order Delete Message", enum_type::order_delete_message},
        {"Order Mass Delete Message", enum_type::order_mass_delete_message},
        {"Order Modify Message", enum_type::order_modify_message},
        {"Order Modify Same Priority Message", enum_type::order_modify_same_priority_message},
        {"Packet Header", enum_type::packet_header},
        {"Partial Order Execution Message", enum_type::partial_order_execution_message},
        {"Product State Change Message", enum_type::product_state_change_message},
        {"Product Summary Message", enum_type::product_summary_message},
        {"Snapshot Order Message", enum_type::snapshot_order_message},
        {"Top Of Book Message", enum_type::top_of_book_message},
        {"Trade Reversal Message", enum_type::trade_reversal_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::heartbeat_message: return "Heartbeat Message";
            case enum_type::product_summary_message: return "Product Summary Message";
            case enum_type::snapshot_order_message: return "Snapshot Order Message";
            case enum_type::instrument_summary_message: return "Instrument Summary Message";
            case enum_type::auction_best_bid_offer_message: return "Auction Best Bid Offer Message";
            case enum_type::auction_clearing_price_message: return "Auction Clearing Price Message";
            case enum_type::top_of_book_message: return "Top Of Book Message";
            case enum_type::order_add_message: return "Order Add Message";
            case enum_type::order_modify_message: return "Order Modify Message";
            case enum_type::order_modify_same_priority_message: return "Order Modify Same Priority Message";
            case enum_type::order_delete_message: return "Order Delete Message";
            case enum_type::order_mass_delete_message: return "Order Mass Delete Message";
            case enum_type::partial_order_execution_message: return "Partial Order Execution Message";
            case enum_type::full_order_execution_message: return "Full Order Execution Message";
            case enum_type::trade_reversal_message: return "Trade Reversal Message";
            case enum_type::execution_summary_message: return "Execution Summary Message";
            case enum_type::instrument_info_message: return "Instrument Info Message";
            case enum_type::lpp_range_message: return "Lpp Range Message";
            case enum_type::product_state_change_message: return "Product State Change Message";
            case enum_type::instrument_state_change_message: return "Instrument State Change Message";
            case enum_type::add_complex_instrument_message: return "Add Complex Instrument Message";
            case enum_type::packet_header: return "Packet Header";
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
            set(enum_type::packet_header);
    }

  protected:
    enum_type value;
};
}
