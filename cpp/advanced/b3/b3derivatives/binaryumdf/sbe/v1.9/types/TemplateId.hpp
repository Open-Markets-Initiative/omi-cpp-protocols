#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// template_id
struct template_id {

    enum class enum_type : std::uint16_t {
        sequence_reset_1_message = 1,
        sequence_2_message = 2,
        empty_book_9_message = 9,
        channel_reset_11_message = 11,
        security_status_3_message = 3,
        security_group_phase_10_message = 10,
        security_definition_message = 12,
        news_5_message = 5,
        opening_price_15_message = 15,
        theoretical_opening_price_16_message = 16,
        closing_price_17_message = 17,
        auction_imbalance_19_message = 19,
        quantity_band_21_message = 21,
        price_band_22_message = 22,
        high_price_24_message = 24,
        low_price_25_message = 25,
        last_trade_price_27_message = 27,
        settlement_price_28_message = 28,
        open_interest_29_message = 29,
        snapshot_full_refresh_header_30_message = 30,
        order_mb_o_50_message = 50,
        delete_order_mb_o_51_message = 51,
        mass_delete_orders_mb_o_52_message = 52,
        trade_53_message = 53,
        forward_trade_54_message = 54,
        execution_summary_55_message = 55,
        execution_statistics_56_message = 56,
        trade_bust_57_message = 57,
        snapshot_full_refresh_orders_mb_o_71_message = 71
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 29> from_string_map = {{
        {"Auction Imbalance 19 Message", enum_type::auction_imbalance_19_message},
        {"Channel Reset 11 Message", enum_type::channel_reset_11_message},
        {"Closing Price 17 Message", enum_type::closing_price_17_message},
        {"Delete Order Mb O 51 Message", enum_type::delete_order_mb_o_51_message},
        {"Empty Book 9 Message", enum_type::empty_book_9_message},
        {"Execution Statistics 56 Message", enum_type::execution_statistics_56_message},
        {"Execution Summary 55 Message", enum_type::execution_summary_55_message},
        {"Forward Trade 54 Message", enum_type::forward_trade_54_message},
        {"High Price 24 Message", enum_type::high_price_24_message},
        {"Last Trade Price 27 Message", enum_type::last_trade_price_27_message},
        {"Low Price 25 Message", enum_type::low_price_25_message},
        {"Mass Delete Orders Mb O 52 Message", enum_type::mass_delete_orders_mb_o_52_message},
        {"News 5 Message", enum_type::news_5_message},
        {"Open Interest 29 Message", enum_type::open_interest_29_message},
        {"Opening Price 15 Message", enum_type::opening_price_15_message},
        {"Order Mb O 50 Message", enum_type::order_mb_o_50_message},
        {"Price Band 22 Message", enum_type::price_band_22_message},
        {"Quantity Band 21 Message", enum_type::quantity_band_21_message},
        {"Security Definition Message", enum_type::security_definition_message},
        {"Security Group Phase 10 Message", enum_type::security_group_phase_10_message},
        {"Security Status 3 Message", enum_type::security_status_3_message},
        {"Sequence 2 Message", enum_type::sequence_2_message},
        {"Sequence Reset 1 Message", enum_type::sequence_reset_1_message},
        {"Settlement Price 28 Message", enum_type::settlement_price_28_message},
        {"Snapshot Full Refresh Header 30 Message", enum_type::snapshot_full_refresh_header_30_message},
        {"Snapshot Full Refresh Orders Mb O 71 Message", enum_type::snapshot_full_refresh_orders_mb_o_71_message},
        {"Theoretical Opening Price 16 Message", enum_type::theoretical_opening_price_16_message},
        {"Trade 53 Message", enum_type::trade_53_message},
        {"Trade Bust 57 Message", enum_type::trade_bust_57_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::sequence_reset_1_message: return "Sequence Reset 1 Message";
            case enum_type::sequence_2_message: return "Sequence 2 Message";
            case enum_type::empty_book_9_message: return "Empty Book 9 Message";
            case enum_type::channel_reset_11_message: return "Channel Reset 11 Message";
            case enum_type::security_status_3_message: return "Security Status 3 Message";
            case enum_type::security_group_phase_10_message: return "Security Group Phase 10 Message";
            case enum_type::security_definition_message: return "Security Definition Message";
            case enum_type::news_5_message: return "News 5 Message";
            case enum_type::opening_price_15_message: return "Opening Price 15 Message";
            case enum_type::theoretical_opening_price_16_message: return "Theoretical Opening Price 16 Message";
            case enum_type::closing_price_17_message: return "Closing Price 17 Message";
            case enum_type::auction_imbalance_19_message: return "Auction Imbalance 19 Message";
            case enum_type::quantity_band_21_message: return "Quantity Band 21 Message";
            case enum_type::price_band_22_message: return "Price Band 22 Message";
            case enum_type::high_price_24_message: return "High Price 24 Message";
            case enum_type::low_price_25_message: return "Low Price 25 Message";
            case enum_type::last_trade_price_27_message: return "Last Trade Price 27 Message";
            case enum_type::settlement_price_28_message: return "Settlement Price 28 Message";
            case enum_type::open_interest_29_message: return "Open Interest 29 Message";
            case enum_type::snapshot_full_refresh_header_30_message: return "Snapshot Full Refresh Header 30 Message";
            case enum_type::order_mb_o_50_message: return "Order Mb O 50 Message";
            case enum_type::delete_order_mb_o_51_message: return "Delete Order Mb O 51 Message";
            case enum_type::mass_delete_orders_mb_o_52_message: return "Mass Delete Orders Mb O 52 Message";
            case enum_type::trade_53_message: return "Trade 53 Message";
            case enum_type::forward_trade_54_message: return "Forward Trade 54 Message";
            case enum_type::execution_summary_55_message: return "Execution Summary 55 Message";
            case enum_type::execution_statistics_56_message: return "Execution Statistics 56 Message";
            case enum_type::trade_bust_57_message: return "Trade Bust 57 Message";
            case enum_type::snapshot_full_refresh_orders_mb_o_71_message: return "Snapshot Full Refresh Orders Mb O 71 Message";
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
     : value{ enum_type::sequence_reset_1_message } {}

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
            set(enum_type::snapshot_full_refresh_orders_mb_o_71_message);
    }

  protected:
    enum_type value;
};
}
