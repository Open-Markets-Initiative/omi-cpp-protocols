#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// template_id
struct template_id {

    enum class enum_type : std::uint8_t {
        security_definition_message = 13,
        current_market_refresh_message = 11,
        market_data_refresh_message = 20,
        current_market_update_message = 12,
        recap_update_message = 21,
        ticker_message = 14,
        expected_opening_price_and_size_message = 15,
        index_value_message = 22,
        settlement_value_message = 23,
        summary_message = 24,
        market_data_control_message = 25,
        heartbeat_message = 16
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Current Market Refresh Message", enum_type::current_market_refresh_message},
        {"Current Market Update Message", enum_type::current_market_update_message},
        {"Expected Opening Price And Size Message", enum_type::expected_opening_price_and_size_message},
        {"Heartbeat Message", enum_type::heartbeat_message},
        {"Index Value Message", enum_type::index_value_message},
        {"Market Data Control Message", enum_type::market_data_control_message},
        {"Market Data Refresh Message", enum_type::market_data_refresh_message},
        {"Recap Update Message", enum_type::recap_update_message},
        {"Security Definition Message", enum_type::security_definition_message},
        {"Settlement Value Message", enum_type::settlement_value_message},
        {"Summary Message", enum_type::summary_message},
        {"Ticker Message", enum_type::ticker_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::security_definition_message: return "Security Definition Message";
            case enum_type::current_market_refresh_message: return "Current Market Refresh Message";
            case enum_type::market_data_refresh_message: return "Market Data Refresh Message";
            case enum_type::current_market_update_message: return "Current Market Update Message";
            case enum_type::recap_update_message: return "Recap Update Message";
            case enum_type::ticker_message: return "Ticker Message";
            case enum_type::expected_opening_price_and_size_message: return "Expected Opening Price And Size Message";
            case enum_type::index_value_message: return "Index Value Message";
            case enum_type::settlement_value_message: return "Settlement Value Message";
            case enum_type::summary_message: return "Summary Message";
            case enum_type::market_data_control_message: return "Market Data Control Message";
            case enum_type::heartbeat_message: return "Heartbeat Message";
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
            set(enum_type::heartbeat_message);
    }

  protected:
    enum_type value;
};
}
