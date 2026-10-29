#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

// message_type
struct message_type {

    enum class enum_type : std::uint16_t {
        sequence_number_reset_message = 1,
        source_time_reference_message = 2,
        symbol_index_mapping_message = 3,
        symbol_clear_message = 32,
        security_status_message = 34,
        add_order_message = 100,
        modify_order_message = 101,
        delete_order_message = 102,
        order_execution_message = 103,
        replace_order_message = 104,
        imbalance_message = 105,
        add_order_refresh_message = 106,
        non_displayed_trade_message = 110,
        cross_trade_message = 111,
        trade_cancel_message = 112,
        cross_correction_message = 113,
        retail_price_improvement_message = 114
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Add Order Message", enum_type::add_order_message},
        {"Add Order Refresh Message", enum_type::add_order_refresh_message},
        {"Cross Correction Message", enum_type::cross_correction_message},
        {"Cross Trade Message", enum_type::cross_trade_message},
        {"Delete Order Message", enum_type::delete_order_message},
        {"Imbalance Message", enum_type::imbalance_message},
        {"Modify Order Message", enum_type::modify_order_message},
        {"Non Displayed Trade Message", enum_type::non_displayed_trade_message},
        {"Order Execution Message", enum_type::order_execution_message},
        {"Replace Order Message", enum_type::replace_order_message},
        {"Retail Price Improvement Message", enum_type::retail_price_improvement_message},
        {"Security Status Message", enum_type::security_status_message},
        {"Sequence Number Reset Message", enum_type::sequence_number_reset_message},
        {"Source Time Reference Message", enum_type::source_time_reference_message},
        {"Symbol Clear Message", enum_type::symbol_clear_message},
        {"Symbol Index Mapping Message", enum_type::symbol_index_mapping_message},
        {"Trade Cancel Message", enum_type::trade_cancel_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::sequence_number_reset_message: return "Sequence Number Reset Message";
            case enum_type::source_time_reference_message: return "Source Time Reference Message";
            case enum_type::symbol_index_mapping_message: return "Symbol Index Mapping Message";
            case enum_type::symbol_clear_message: return "Symbol Clear Message";
            case enum_type::security_status_message: return "Security Status Message";
            case enum_type::add_order_message: return "Add Order Message";
            case enum_type::modify_order_message: return "Modify Order Message";
            case enum_type::delete_order_message: return "Delete Order Message";
            case enum_type::order_execution_message: return "Order Execution Message";
            case enum_type::replace_order_message: return "Replace Order Message";
            case enum_type::imbalance_message: return "Imbalance Message";
            case enum_type::add_order_refresh_message: return "Add Order Refresh Message";
            case enum_type::non_displayed_trade_message: return "Non Displayed Trade Message";
            case enum_type::cross_trade_message: return "Cross Trade Message";
            case enum_type::trade_cancel_message: return "Trade Cancel Message";
            case enum_type::cross_correction_message: return "Cross Correction Message";
            case enum_type::retail_price_improvement_message: return "Retail Price Improvement Message";
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

    static constexpr const char* name = "message_type";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<message_type::enum_type>;
    using storage_type = result_type;

    constexpr message_type()
     : value{ enum_type{} } {}

    constexpr message_type(enum_type v)
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
            set(enum_type::retail_price_improvement_message);
    }

  protected:
    enum_type value;
};
}
