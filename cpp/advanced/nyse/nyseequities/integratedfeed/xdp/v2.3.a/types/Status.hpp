#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// status
struct status {

    enum class enum_type : char {
        message_was_accepted = '0',
        rejected_due_to_an_invalid_source_id = '1',
        maximum_sequence_range = '3',
        maximum_request_in_a_day = '4',
        maximum_refresh_requests_in_a_day = '5',
        old_seq_num_ttl = '6',
        invalid_channel_id = '7',
        invalid_product_id = '8',
        invalid_msg_type_or_msg_size_mismatch = '9'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Invalid Channel Id", enum_type::invalid_channel_id},
        {"Invalid Msg Type Or Msg Size Mismatch", enum_type::invalid_msg_type_or_msg_size_mismatch},
        {"Invalid Product Id", enum_type::invalid_product_id},
        {"Maximum Refresh Requests In A Day", enum_type::maximum_refresh_requests_in_a_day},
        {"Maximum Request In A Day", enum_type::maximum_request_in_a_day},
        {"Maximum Sequence Range", enum_type::maximum_sequence_range},
        {"Message Was Accepted", enum_type::message_was_accepted},
        {"Old Seq Num Ttl", enum_type::old_seq_num_ttl},
        {"Rejected Due To An Invalid Source Id", enum_type::rejected_due_to_an_invalid_source_id}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::message_was_accepted: return "Message Was Accepted";
            case enum_type::rejected_due_to_an_invalid_source_id: return "Rejected Due To An Invalid Source Id";
            case enum_type::maximum_sequence_range: return "Maximum Sequence Range";
            case enum_type::maximum_request_in_a_day: return "Maximum Request In A Day";
            case enum_type::maximum_refresh_requests_in_a_day: return "Maximum Refresh Requests In A Day";
            case enum_type::old_seq_num_ttl: return "Old Seq Num Ttl";
            case enum_type::invalid_channel_id: return "Invalid Channel Id";
            case enum_type::invalid_product_id: return "Invalid Product Id";
            case enum_type::invalid_msg_type_or_msg_size_mismatch: return "Invalid Msg Type Or Msg Size Mismatch";
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
            set(enum_type::invalid_msg_type_or_msg_size_mismatch);
    }

  protected:
    enum_type value;
};
}
