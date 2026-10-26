#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/CrossingSessionITotalTradesVolume.hpp"
#include "../types/CrossingSessionIiDollarValue.hpp"
#include "../types/CrossingSessionIiTotalTradesVolume.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

// Used to report the total volume and dollar value of trades transacted after the close of a Participant's regular session
struct CrossingSessionSummaryMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    CrossingSessionITotalTradesVolume crossing_session_i_total_trades_volume;
    CrossingSessionIiDollarValue crossing_session_ii_dollar_value;
    CrossingSessionIiTotalTradesVolume crossing_session_ii_total_trades_volume;

    // parse method
    static CrossingSessionSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CrossingSessionSummaryMessage*>(buffer);
    }

    // parse method const
    static const CrossingSessionSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CrossingSessionSummaryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
