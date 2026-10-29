#pragma once

#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/QuoteReqIdOptional.hpp"
#include "../types/QuoteIdOptional.hpp"
#include "../types/Account.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTrader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

// QuoteCancelMessage
struct QuoteCancelMessage {

    BidirectionalBusinessHeader bidirectional_business_header;
    SecurityId security_id;
    QuoteReqIdOptional quote_req_id_optional;
    QuoteIdOptional quote_id_optional;
    Account account;
    SenderLocation sender_location;
    EnteringTrader entering_trader;
    ExecutingTrader executing_trader;

    // parse method
    static QuoteCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteCancelMessage*>(buffer);
    }

    // parse method const
    static const QuoteCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteCancelMessage*>(buffer);
    }
};

#pragma pack(pop)
}
