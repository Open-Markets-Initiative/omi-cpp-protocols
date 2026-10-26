#pragma once

#include "../types/MessageIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/Reserved1.hpp"
#include "../types/IndexValueDenominatorCode.hpp"
#include "../types/IndexValue.hpp"
#include "../types/Reserved4.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

// Underlying Value last sale Message
struct UnderlyingValueLastSaleMessage {

    MessageIndicator message_indicator;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    Reserved1 reserved_1;
    IndexValueDenominatorCode index_value_denominator_code;
    IndexValue index_value;
    Reserved4 reserved_4;

    // parse method
    static UnderlyingValueLastSaleMessage* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingValueLastSaleMessage*>(buffer);
    }

    // parse method const
    static const UnderlyingValueLastSaleMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingValueLastSaleMessage*>(buffer);
    }
};

#pragma pack(pop)
}
