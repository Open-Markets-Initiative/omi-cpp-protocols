#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

// template_id
struct template_id {

    enum class enum_type : std::uint16_t {
        no_value = 0xFFFF,
        add_complex_instrument = 13400,
        auction_bbo = 13500,
        auction_clearing_price = 13501,
        cross_request = 13502,
        execution_summary = 13202,
        full_order_execution = 13104,
        heartbeat = 13001,
        instrument_state_change = 13301,
        instrument_summary = 13601,
        order_add = 13100,
        order_delete = 13102,
        order_mass_delete = 13103,
        order_modify = 13101,
        order_modify_same_prio = 13106,
        packet_header = 13002,
        partial_order_execution = 13105,
        product_state_change = 13300,
        product_summary = 13600,
        quote_request = 13503,
        snapshot_order = 13602,
        top_of_book = 13504,
        trade_report = 13201,
        trade_reversal = 13200
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 24> from_string_map = {{
        {"Add Complex Instrument", enum_type::add_complex_instrument},
        {"Auction Bbo", enum_type::auction_bbo},
        {"Auction Clearing Price", enum_type::auction_clearing_price},
        {"Cross Request", enum_type::cross_request},
        {"Execution Summary", enum_type::execution_summary},
        {"Full Order Execution", enum_type::full_order_execution},
        {"Heartbeat", enum_type::heartbeat},
        {"Instrument State Change", enum_type::instrument_state_change},
        {"Instrument Summary", enum_type::instrument_summary},
        {"No Value", enum_type::no_value},
        {"Order Add", enum_type::order_add},
        {"Order Delete", enum_type::order_delete},
        {"Order Mass Delete", enum_type::order_mass_delete},
        {"Order Modify", enum_type::order_modify},
        {"Order Modify Same Prio", enum_type::order_modify_same_prio},
        {"Packet Header", enum_type::packet_header},
        {"Partial Order Execution", enum_type::partial_order_execution},
        {"Product State Change", enum_type::product_state_change},
        {"Product Summary", enum_type::product_summary},
        {"Quote Request", enum_type::quote_request},
        {"Snapshot Order", enum_type::snapshot_order},
        {"Top Of Book", enum_type::top_of_book},
        {"Trade Report", enum_type::trade_report},
        {"Trade Reversal", enum_type::trade_reversal}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_value: return "No Value";
            case enum_type::add_complex_instrument: return "Add Complex Instrument";
            case enum_type::auction_bbo: return "Auction Bbo";
            case enum_type::auction_clearing_price: return "Auction Clearing Price";
            case enum_type::cross_request: return "Cross Request";
            case enum_type::execution_summary: return "Execution Summary";
            case enum_type::full_order_execution: return "Full Order Execution";
            case enum_type::heartbeat: return "Heartbeat";
            case enum_type::instrument_state_change: return "Instrument State Change";
            case enum_type::instrument_summary: return "Instrument Summary";
            case enum_type::order_add: return "Order Add";
            case enum_type::order_delete: return "Order Delete";
            case enum_type::order_mass_delete: return "Order Mass Delete";
            case enum_type::order_modify: return "Order Modify";
            case enum_type::order_modify_same_prio: return "Order Modify Same Prio";
            case enum_type::packet_header: return "Packet Header";
            case enum_type::partial_order_execution: return "Partial Order Execution";
            case enum_type::product_state_change: return "Product State Change";
            case enum_type::product_summary: return "Product Summary";
            case enum_type::quote_request: return "Quote Request";
            case enum_type::snapshot_order: return "Snapshot Order";
            case enum_type::top_of_book: return "Top Of Book";
            case enum_type::trade_report: return "Trade Report";
            case enum_type::trade_reversal: return "Trade Reversal";
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
            set(static_cast<enum_type>(0xFFFF));
    }

  protected:
    enum_type value;
};
}
