#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// message_type
struct message_type {

    enum class enum_type : std::uint16_t {
        sequence_number_reset_message = 1,
        source_time_reference_message = 2,
        symbol_index_mapping_message = 3,
        symbol_clear_message = 32,
        security_status_message = 34,
        outright_series_index_mapping_message = 50,
        options_status_message = 51,
        complex_series_index_mapping_message = 60,
        retransmission_request_message = 10,
        refresh_header_message = 35,
        refresh_request_message = 15,
        symbol_index_mapping_request_message = 13,
        message_unavailable_message = 31,
        request_response_message = 11,
        heartbeat_response_message = 12,
        options_add_order_message = 300,
        options_modify_order_message = 301,
        options_delete_order_message = 302,
        options_order_execution_message = 303,
        options_replace_order_message = 304,
        options_imbalance_message = 305,
        options_add_order_refresh_message = 306,
        options_series_rfq_message = 307,
        options_non_displayed_trade_message = 310,
        options_cross_trade_message = 311,
        options_trade_cancel_message = 312,
        options_outright_series_summary_message = 323
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 27> from_string_map = {{
        {"Complex Series Index Mapping Message", enum_type::complex_series_index_mapping_message},
        {"Heartbeat Response Message", enum_type::heartbeat_response_message},
        {"Message Unavailable Message", enum_type::message_unavailable_message},
        {"Options Add Order Message", enum_type::options_add_order_message},
        {"Options Add Order Refresh Message", enum_type::options_add_order_refresh_message},
        {"Options Cross Trade Message", enum_type::options_cross_trade_message},
        {"Options Delete Order Message", enum_type::options_delete_order_message},
        {"Options Imbalance Message", enum_type::options_imbalance_message},
        {"Options Modify Order Message", enum_type::options_modify_order_message},
        {"Options Non Displayed Trade Message", enum_type::options_non_displayed_trade_message},
        {"Options Order Execution Message", enum_type::options_order_execution_message},
        {"Options Outright Series Summary Message", enum_type::options_outright_series_summary_message},
        {"Options Replace Order Message", enum_type::options_replace_order_message},
        {"Options Series Rfq Message", enum_type::options_series_rfq_message},
        {"Options Status Message", enum_type::options_status_message},
        {"Options Trade Cancel Message", enum_type::options_trade_cancel_message},
        {"Outright Series Index Mapping Message", enum_type::outright_series_index_mapping_message},
        {"Refresh Header Message", enum_type::refresh_header_message},
        {"Refresh Request Message", enum_type::refresh_request_message},
        {"Request Response Message", enum_type::request_response_message},
        {"Retransmission Request Message", enum_type::retransmission_request_message},
        {"Security Status Message", enum_type::security_status_message},
        {"Sequence Number Reset Message", enum_type::sequence_number_reset_message},
        {"Source Time Reference Message", enum_type::source_time_reference_message},
        {"Symbol Clear Message", enum_type::symbol_clear_message},
        {"Symbol Index Mapping Message", enum_type::symbol_index_mapping_message},
        {"Symbol Index Mapping Request Message", enum_type::symbol_index_mapping_request_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::sequence_number_reset_message: return "Sequence Number Reset Message";
            case enum_type::source_time_reference_message: return "Source Time Reference Message";
            case enum_type::symbol_index_mapping_message: return "Symbol Index Mapping Message";
            case enum_type::symbol_clear_message: return "Symbol Clear Message";
            case enum_type::security_status_message: return "Security Status Message";
            case enum_type::outright_series_index_mapping_message: return "Outright Series Index Mapping Message";
            case enum_type::options_status_message: return "Options Status Message";
            case enum_type::complex_series_index_mapping_message: return "Complex Series Index Mapping Message";
            case enum_type::retransmission_request_message: return "Retransmission Request Message";
            case enum_type::refresh_header_message: return "Refresh Header Message";
            case enum_type::refresh_request_message: return "Refresh Request Message";
            case enum_type::symbol_index_mapping_request_message: return "Symbol Index Mapping Request Message";
            case enum_type::message_unavailable_message: return "Message Unavailable Message";
            case enum_type::request_response_message: return "Request Response Message";
            case enum_type::heartbeat_response_message: return "Heartbeat Response Message";
            case enum_type::options_add_order_message: return "Options Add Order Message";
            case enum_type::options_modify_order_message: return "Options Modify Order Message";
            case enum_type::options_delete_order_message: return "Options Delete Order Message";
            case enum_type::options_order_execution_message: return "Options Order Execution Message";
            case enum_type::options_replace_order_message: return "Options Replace Order Message";
            case enum_type::options_imbalance_message: return "Options Imbalance Message";
            case enum_type::options_add_order_refresh_message: return "Options Add Order Refresh Message";
            case enum_type::options_series_rfq_message: return "Options Series Rfq Message";
            case enum_type::options_non_displayed_trade_message: return "Options Non Displayed Trade Message";
            case enum_type::options_cross_trade_message: return "Options Cross Trade Message";
            case enum_type::options_trade_cancel_message: return "Options Trade Cancel Message";
            case enum_type::options_outright_series_summary_message: return "Options Outright Series Summary Message";
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
            set(enum_type::options_outright_series_summary_message);
    }

  protected:
    enum_type value;
};
}
