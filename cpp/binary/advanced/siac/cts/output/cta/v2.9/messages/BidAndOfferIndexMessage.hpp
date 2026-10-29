#pragma once

#include <cstddef>
#include "../structs/BlockHeader.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/IndexSymbol.hpp"
#include "../types/BidIndexValue.hpp"
#include "../types/OfferIndexValue.hpp"
#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"
#include "../types/IndicesMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

namespace cta_output = ::siac::cts::output::cta::v2_9;

#pragma pack(push, 1)

// Bid And Offer Index Message
struct bid_and_offer_index_message {

    struct fields_type {
        cta_output::participant_id participant_id;
        cta_output::timestamp_1 timestamp_1;
        cta_output::message_id message_id;
        cta_output::transaction_id transaction_id;
        cta_output::participant_reference_number participant_reference_number;
        cta_output::index_symbol index_symbol;
        cta_output::bid_index_value bid_index_value;
        cta_output::offer_index_value offer_index_value;
    };

    cta_output::block_header header = {{}, {}, {}, {}, {}, {}, {}, {}};
    // Transport framing: message size precedes the SBE header on the wire
    cta_output::message_length message_length;
    cta_output::message_category message_category = cta_output::message_category::enum_type::indices;
    cta_output::indices_message_type indices_message_type = cta_output::indices_message_type::enum_type::bid_and_offer_index_message;

    fields_type fields;

    // parse method
    static bid_and_offer_index_message* parse(std::byte* buffer) {
        return reinterpret_cast<bid_and_offer_index_message*>(buffer);
    }

    // parse method const
    static const bid_and_offer_index_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const bid_and_offer_index_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(bid_and_offer_index_message::fields_type, participant_id) == 0, "unexpected offset of bid_and_offer_index_message::fields_type::participant_id");
static_assert(offsetof(bid_and_offer_index_message::fields_type, timestamp_1) == 1, "unexpected offset of bid_and_offer_index_message::fields_type::timestamp_1");
static_assert(offsetof(bid_and_offer_index_message::fields_type, message_id) == 9, "unexpected offset of bid_and_offer_index_message::fields_type::message_id");
static_assert(offsetof(bid_and_offer_index_message::fields_type, transaction_id) == 10, "unexpected offset of bid_and_offer_index_message::fields_type::transaction_id");
static_assert(offsetof(bid_and_offer_index_message::fields_type, participant_reference_number) == 14, "unexpected offset of bid_and_offer_index_message::fields_type::participant_reference_number");
static_assert(offsetof(bid_and_offer_index_message::fields_type, index_symbol) == 22, "unexpected offset of bid_and_offer_index_message::fields_type::index_symbol");
static_assert(offsetof(bid_and_offer_index_message::fields_type, bid_index_value) == 33, "unexpected offset of bid_and_offer_index_message::fields_type::bid_index_value");
static_assert(offsetof(bid_and_offer_index_message::fields_type, offer_index_value) == 41, "unexpected offset of bid_and_offer_index_message::fields_type::offer_index_value");
static_assert(sizeof(bid_and_offer_index_message::fields_type) == 49, "unexpected sizeof bid_and_offer_index_message::fields_type");
static_assert(sizeof(bid_and_offer_index_message) == sizeof(cta_output::block_header) + sizeof(cta_output::message_length) + sizeof(cta_output::message_category) + sizeof(cta_output::indices_message_type) + 49, "unexpected sizeof bid_and_offer_index_message");

#pragma pack(pop)
}
