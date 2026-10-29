#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/NumberOfParticipants.hpp"
#include "../types/FractionalTradeTotalVolume.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/MarketStatusMessageType.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)
struct fractional_approximate_adjusted_volume_market_center_message_fractional_participants_entry {
    cta_output::participant_id participant_id;
    cta_output::fractional_trade_total_volume fractional_trade_total_volume;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Fractional Approximate Adjusted Volume Market Center Message
struct fractional_approximate_adjusted_volume_market_center_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::number_of_participants number_of_participants;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::market_status;
    cta_output::market_status_message_type market_status_message_type = cta_output::market_status_message_type::enum_type::fractional_approximate_adjusted_volume_market_center_message;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(cta_output::block_header) - sizeof(fields_type) - sizeof(cta_output::message_length) - sizeof(cta_output::message_category) - sizeof(cta_output::market_status_message_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = message_length.get().value();
        return (sz + sizeof(cta_output::block_header)) == sizeof(cta_output::block_header) + sizeof(fields_type) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::market_status_message_type)
            ? tail + tail_capacity
            : tail + ((sz + sizeof(cta_output::block_header)) - sizeof(cta_output::block_header) - sizeof(fields_type) - sizeof(cta_output::message_length) - sizeof(cta_output::message_category) - sizeof(cta_output::market_status_message_type));
    }

    // sequential access to variable-length regions
    external_count_iterator<fractional_approximate_adjusted_volume_market_center_message_fractional_participants_entry> fractional_participants() const {
        return { tail_begin(), fields.number_of_participants.get().value(), tail_end() };
    }


    // parse method
    static fractional_approximate_adjusted_volume_market_center_message* parse(std::byte* buffer) {
        return reinterpret_cast<fractional_approximate_adjusted_volume_market_center_message*>(buffer);
    }

    // parse method const
    static const fractional_approximate_adjusted_volume_market_center_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const fractional_approximate_adjusted_volume_market_center_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(fractional_approximate_adjusted_volume_market_center_message::fields_type, participant_id) == 0, "unexpected offset of fractional_approximate_adjusted_volume_market_center_message::fields_type::participant_id");
static_assert(offsetof(fractional_approximate_adjusted_volume_market_center_message::fields_type, timestamp_1) == 1, "unexpected offset of fractional_approximate_adjusted_volume_market_center_message::fields_type::timestamp_1");
static_assert(offsetof(fractional_approximate_adjusted_volume_market_center_message::fields_type, message_id) == 9, "unexpected offset of fractional_approximate_adjusted_volume_market_center_message::fields_type::message_id");
static_assert(offsetof(fractional_approximate_adjusted_volume_market_center_message::fields_type, transaction_id) == 10, "unexpected offset of fractional_approximate_adjusted_volume_market_center_message::fields_type::transaction_id");
static_assert(offsetof(fractional_approximate_adjusted_volume_market_center_message::fields_type, participant_reference_number) == 14, "unexpected offset of fractional_approximate_adjusted_volume_market_center_message::fields_type::participant_reference_number");
static_assert(offsetof(fractional_approximate_adjusted_volume_market_center_message::fields_type, number_of_participants) == 22, "unexpected offset of fractional_approximate_adjusted_volume_market_center_message::fields_type::number_of_participants");
static_assert(sizeof(fractional_approximate_adjusted_volume_market_center_message::fields_type) == 23, "unexpected sizeof fractional_approximate_adjusted_volume_market_center_message::fields_type");

#pragma pack(pop)
}

#include "details/FractionalApproximateAdjustedVolumeMarketCenterMessageWriter.hpp"
#include "details/FractionalApproximateAdjustedVolumeMarketCenterMessageReader.hpp"
