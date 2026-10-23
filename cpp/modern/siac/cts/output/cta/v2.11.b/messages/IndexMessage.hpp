#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/IndexSymbol.hpp"
#include "../types/IndexValue.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// The Index message contains the index and the index value
struct IndexMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    IndexSymbol index_symbol;
    IndexValue index_value;

    // parse method
    static IndexMessage* parse(std::byte* buffer) {
        return reinterpret_cast<IndexMessage*>(buffer);
    }

    // parse method const
    static const IndexMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const IndexMessage*>(buffer);
    }
};

#pragma pack(pop)
}
