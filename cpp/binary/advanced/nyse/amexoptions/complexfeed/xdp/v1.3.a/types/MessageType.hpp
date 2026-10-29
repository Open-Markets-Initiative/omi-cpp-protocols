#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// message_type
struct message_type {

    enum class enum_type : std::uint16_t {
        complex_quote_message = 423,
        complex_trade_message = 425,
        complex_crossing_rfq_message = 429,
        complex_cube_rfq_message = 472,
        complex_status_message = 433,
        refresh_complex_quote_message = 511,
        refresh_complex_trade_message = 513,
        complex_symbol_definition_message = 439,
        stream_id_message = 455,
        sequence_number_reset_message = 1
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 10> from_string_map = {{
        {"Complex Crossing Rfq Message", enum_type::complex_crossing_rfq_message},
        {"Complex Cube Rfq Message", enum_type::complex_cube_rfq_message},
        {"Complex Quote Message", enum_type::complex_quote_message},
        {"Complex Status Message", enum_type::complex_status_message},
        {"Complex Symbol Definition Message", enum_type::complex_symbol_definition_message},
        {"Complex Trade Message", enum_type::complex_trade_message},
        {"Refresh Complex Quote Message", enum_type::refresh_complex_quote_message},
        {"Refresh Complex Trade Message", enum_type::refresh_complex_trade_message},
        {"Sequence Number Reset Message", enum_type::sequence_number_reset_message},
        {"Stream Id Message", enum_type::stream_id_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::complex_quote_message: return "Complex Quote Message";
            case enum_type::complex_trade_message: return "Complex Trade Message";
            case enum_type::complex_crossing_rfq_message: return "Complex Crossing Rfq Message";
            case enum_type::complex_cube_rfq_message: return "Complex Cube Rfq Message";
            case enum_type::complex_status_message: return "Complex Status Message";
            case enum_type::refresh_complex_quote_message: return "Refresh Complex Quote Message";
            case enum_type::refresh_complex_trade_message: return "Refresh Complex Trade Message";
            case enum_type::complex_symbol_definition_message: return "Complex Symbol Definition Message";
            case enum_type::stream_id_message: return "Stream Id Message";
            case enum_type::sequence_number_reset_message: return "Sequence Number Reset Message";
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
            set(enum_type::sequence_number_reset_message);
    }

  protected:
    enum_type value;
};
}
