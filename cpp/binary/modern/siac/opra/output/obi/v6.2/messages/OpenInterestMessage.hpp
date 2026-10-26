#pragma once

#include "../types/MessageIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/ExpirationBlock.hpp"
#include "../types/StrikePriceDenominatorCode.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/OpenInterestVolume.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

// Open Interest Message
struct OpenInterestMessage {

    MessageIndicator message_indicator;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    Reserved1 reserved_1;
    ExpirationBlock expiration_block;
    StrikePriceDenominatorCode strike_price_denominator_code;
    StrikePrice strike_price;
    OpenInterestVolume open_interest_volume;

    // parse method
    static OpenInterestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OpenInterestMessage*>(buffer);
    }

    // parse method const
    static const OpenInterestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OpenInterestMessage*>(buffer);
    }
};

#pragma pack(pop)
}
