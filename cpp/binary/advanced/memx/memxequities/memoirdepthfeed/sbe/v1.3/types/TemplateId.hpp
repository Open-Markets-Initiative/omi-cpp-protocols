#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// template_id
struct template_id {

    enum class enum_type : std::uint8_t {
        instrument_directory_message = 1,
        reg_sho_restriction_message = 2,
        security_trading_status_message = 3,
        trading_session_status_message = 5,
        order_added_message = 10,
        order_deleted_message = 11,
        order_reduced_message = 12,
        order_executed_message = 13,
        trade_message = 14,
        broken_trade_message = 15,
        corrected_trade_message = 16,
        clear_book_message = 18,
        snapshot_complete_message = 100
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 13> from_string_map = {{
        {"Broken Trade Message", enum_type::broken_trade_message},
        {"Clear Book Message", enum_type::clear_book_message},
        {"Corrected Trade Message", enum_type::corrected_trade_message},
        {"Instrument Directory Message", enum_type::instrument_directory_message},
        {"Order Added Message", enum_type::order_added_message},
        {"Order Deleted Message", enum_type::order_deleted_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Reduced Message", enum_type::order_reduced_message},
        {"Reg Sho Restriction Message", enum_type::reg_sho_restriction_message},
        {"Security Trading Status Message", enum_type::security_trading_status_message},
        {"Snapshot Complete Message", enum_type::snapshot_complete_message},
        {"Trade Message", enum_type::trade_message},
        {"Trading Session Status Message", enum_type::trading_session_status_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::instrument_directory_message: return "Instrument Directory Message";
            case enum_type::reg_sho_restriction_message: return "Reg Sho Restriction Message";
            case enum_type::security_trading_status_message: return "Security Trading Status Message";
            case enum_type::trading_session_status_message: return "Trading Session Status Message";
            case enum_type::order_added_message: return "Order Added Message";
            case enum_type::order_deleted_message: return "Order Deleted Message";
            case enum_type::order_reduced_message: return "Order Reduced Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::trade_message: return "Trade Message";
            case enum_type::broken_trade_message: return "Broken Trade Message";
            case enum_type::corrected_trade_message: return "Corrected Trade Message";
            case enum_type::clear_book_message: return "Clear Book Message";
            case enum_type::snapshot_complete_message: return "Snapshot Complete Message";
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
    static constexpr std::size_t size = 1;
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
            set(enum_type::snapshot_complete_message);
    }

  protected:
    enum_type value;
};
}
