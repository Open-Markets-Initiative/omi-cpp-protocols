#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// status
struct status {

    enum class enum_type : char {
        message_was_accepted = '0',
        rejected_due_to_an_invalid_source_id = '1',
        rejected_due_to_maximum_sequence_range = '3',
        rejected_due_to_maximum_request_in_a_day = '4',
        rejected_due_to_maximum_number_of_refresh_requests_in_a_day = '5',
        rejected_request_message_seq_num_ttl_is_too_old = '6',
        rejected_due_to_an_invalid_channel_id = '7',
        rejected_due_to_an_invalid_product_id = '8',
        rejected_due_to_invalid_msg_type_or_mismatch_between_msg_type_and_msg_size = '9'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Message Was Accepted", enum_type::message_was_accepted},
        {"Rejected Due To An Invalid Channel Id", enum_type::rejected_due_to_an_invalid_channel_id},
        {"Rejected Due To An Invalid Product Id", enum_type::rejected_due_to_an_invalid_product_id},
        {"Rejected Due To An Invalid Source Id", enum_type::rejected_due_to_an_invalid_source_id},
        {"Rejected Due To Invalid Msg Type Or Mismatch Between Msg Type And Msg Size", enum_type::rejected_due_to_invalid_msg_type_or_mismatch_between_msg_type_and_msg_size},
        {"Rejected Due To Maximum Number Of Refresh Requests In A Day", enum_type::rejected_due_to_maximum_number_of_refresh_requests_in_a_day},
        {"Rejected Due To Maximum Request In A Day", enum_type::rejected_due_to_maximum_request_in_a_day},
        {"Rejected Due To Maximum Sequence Range", enum_type::rejected_due_to_maximum_sequence_range},
        {"Rejected Request Message Seq Num Ttl Is Too Old", enum_type::rejected_request_message_seq_num_ttl_is_too_old}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::message_was_accepted: return "Message Was Accepted";
            case enum_type::rejected_due_to_an_invalid_source_id: return "Rejected Due To An Invalid Source Id";
            case enum_type::rejected_due_to_maximum_sequence_range: return "Rejected Due To Maximum Sequence Range";
            case enum_type::rejected_due_to_maximum_request_in_a_day: return "Rejected Due To Maximum Request In A Day";
            case enum_type::rejected_due_to_maximum_number_of_refresh_requests_in_a_day: return "Rejected Due To Maximum Number Of Refresh Requests In A Day";
            case enum_type::rejected_request_message_seq_num_ttl_is_too_old: return "Rejected Request Message Seq Num Ttl Is Too Old";
            case enum_type::rejected_due_to_an_invalid_channel_id: return "Rejected Due To An Invalid Channel Id";
            case enum_type::rejected_due_to_an_invalid_product_id: return "Rejected Due To An Invalid Product Id";
            case enum_type::rejected_due_to_invalid_msg_type_or_mismatch_between_msg_type_and_msg_size: return "Rejected Due To Invalid Msg Type Or Mismatch Between Msg Type And Msg Size";
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
            set(enum_type::rejected_due_to_invalid_msg_type_or_mismatch_between_msg_type_and_msg_size);
    }

  protected:
    enum_type value;
};
}
