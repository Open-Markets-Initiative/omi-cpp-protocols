#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// status
struct status {

    enum class enum_type : char {
        accepted = '0',
        rejected = '1',
        invalid_sequence_range = '2',
        maximum_sequence_range = '3',
        maximum_request_in_a_day = '4',
        maximum_refresh_requests_in_a_day = '5',
        old_seq_num_ttl = '6',
        invalid_channel_id = '7',
        invalid_product_id = '8',
        invalid_msg_type_or_msg_size = '9'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 10> from_string_map = {{
        {"Accepted", enum_type::accepted},
        {"Invalid Channel Id", enum_type::invalid_channel_id},
        {"Invalid Msg Type Or Msg Size", enum_type::invalid_msg_type_or_msg_size},
        {"Invalid Product Id", enum_type::invalid_product_id},
        {"Invalid Sequence Range", enum_type::invalid_sequence_range},
        {"Maximum Refresh Requests In A Day", enum_type::maximum_refresh_requests_in_a_day},
        {"Maximum Request In A Day", enum_type::maximum_request_in_a_day},
        {"Maximum Sequence Range", enum_type::maximum_sequence_range},
        {"Old Seq Num Ttl", enum_type::old_seq_num_ttl},
        {"Rejected", enum_type::rejected}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::accepted: return "Accepted";
            case enum_type::rejected: return "Rejected";
            case enum_type::invalid_sequence_range: return "Invalid Sequence Range";
            case enum_type::maximum_sequence_range: return "Maximum Sequence Range";
            case enum_type::maximum_request_in_a_day: return "Maximum Request In A Day";
            case enum_type::maximum_refresh_requests_in_a_day: return "Maximum Refresh Requests In A Day";
            case enum_type::old_seq_num_ttl: return "Old Seq Num Ttl";
            case enum_type::invalid_channel_id: return "Invalid Channel Id";
            case enum_type::invalid_product_id: return "Invalid Product Id";
            case enum_type::invalid_msg_type_or_msg_size: return "Invalid Msg Type Or Msg Size";
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

    static constexpr const char* name = "status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<status::enum_type>;
    using storage_type = result_type;

    constexpr status()
     : value{ enum_type{} } {}

    constexpr status(enum_type v)
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
            set(enum_type::invalid_msg_type_or_msg_size);
    }

  protected:
    enum_type value;
};
}
