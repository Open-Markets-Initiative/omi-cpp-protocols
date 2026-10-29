#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// message_type
struct message_type {

    enum class enum_type : std::uint16_t {
        outright_market_depth_buy_message = 403,
        outright_market_depth_sell_message = 405,
        underlying_status_message = 419,
        outright_series_status_message = 421,
        refresh_outright_market_depth_buy_message = 503,
        refresh_outright_market_depth_sell_message = 505,
        underlying_index_mapping_message = 435,
        series_index_mapping_message = 437,
        stream_id_message = 455,
        sequence_number_reset_message = 1
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 10> from_string_map = {{
        {"Outright Market Depth Buy Message", enum_type::outright_market_depth_buy_message},
        {"Outright Market Depth Sell Message", enum_type::outright_market_depth_sell_message},
        {"Outright Series Status Message", enum_type::outright_series_status_message},
        {"Refresh Outright Market Depth Buy Message", enum_type::refresh_outright_market_depth_buy_message},
        {"Refresh Outright Market Depth Sell Message", enum_type::refresh_outright_market_depth_sell_message},
        {"Sequence Number Reset Message", enum_type::sequence_number_reset_message},
        {"Series Index Mapping Message", enum_type::series_index_mapping_message},
        {"Stream Id Message", enum_type::stream_id_message},
        {"Underlying Index Mapping Message", enum_type::underlying_index_mapping_message},
        {"Underlying Status Message", enum_type::underlying_status_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::outright_market_depth_buy_message: return "Outright Market Depth Buy Message";
            case enum_type::outright_market_depth_sell_message: return "Outright Market Depth Sell Message";
            case enum_type::underlying_status_message: return "Underlying Status Message";
            case enum_type::outright_series_status_message: return "Outright Series Status Message";
            case enum_type::refresh_outright_market_depth_buy_message: return "Refresh Outright Market Depth Buy Message";
            case enum_type::refresh_outright_market_depth_sell_message: return "Refresh Outright Market Depth Sell Message";
            case enum_type::underlying_index_mapping_message: return "Underlying Index Mapping Message";
            case enum_type::series_index_mapping_message: return "Series Index Mapping Message";
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
