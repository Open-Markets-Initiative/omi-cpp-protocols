#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/TotalTrades.hpp"
#include "../types/DollarValue.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

// The Approximate Trades and Total Dollar Value message allows a Participant to report the total trades and total dollar value of trades at their respective market centers.
struct ApproximateTradesAndTotalDollarValueMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    TotalTrades total_trades;
    DollarValue dollar_value;

    // parse method
    static ApproximateTradesAndTotalDollarValueMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ApproximateTradesAndTotalDollarValueMessage*>(buffer);
    }

    // parse method const
    static const ApproximateTradesAndTotalDollarValueMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ApproximateTradesAndTotalDollarValueMessage*>(buffer);
    }
};

#pragma pack(pop)
}
