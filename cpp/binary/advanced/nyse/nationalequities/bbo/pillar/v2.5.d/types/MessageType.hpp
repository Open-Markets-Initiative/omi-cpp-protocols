#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

// message_type
struct message_type {

    enum class enum_type : std::uint16_t {
        sequence_number_reset_message = 1,
        source_time_reference_message = 2,
        symbol_index_mapping_message = 3,
        symbol_clear_message = 32,
        security_status_message = 34,
        retransmission_request_message = 10,
        symbol_index_mapping_request_message = 13,
        refresh_request_message = 15,
        message_unavailable_message = 31,
        refresh_header_message = 35,
        request_response_message = 11,
        heartbeat_response_message = 12,
        quote_message = 140
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 13> from_string_map = {{
        {"Heartbeat Response Message", enum_type::heartbeat_response_message},
        {"Message Unavailable Message", enum_type::message_unavailable_message},
        {"Quote Message", enum_type::quote_message},
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
            case enum_type::retransmission_request_message: return "Retransmission Request Message";
            case enum_type::symbol_index_mapping_request_message: return "Symbol Index Mapping Request Message";
            case enum_type::refresh_request_message: return "Refresh Request Message";
            case enum_type::message_unavailable_message: return "Message Unavailable Message";
            case enum_type::refresh_header_message: return "Refresh Header Message";
            case enum_type::request_response_message: return "Request Response Message";
            case enum_type::heartbeat_response_message: return "Heartbeat Response Message";
            case enum_type::quote_message: return "Quote Message";
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
            set(enum_type::quote_message);
    }

  protected:
    enum_type value;
};
}
