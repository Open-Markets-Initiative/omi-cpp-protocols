#pragma once

#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecuritySubType.hpp"
#include "../types/ProductComplex.hpp"
#include "../types/ImpliedMarketIndicator.hpp"
#include "../types/NoLegs.hpp"
#include "../types/Pad1.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published whenever a new complex instrument is created intraday or an existing complex instrument is modified.
struct AddComplexInstrumentMessage {

    SecurityId security_id;
    TransactTime transact_time;
    SecuritySubType security_sub_type;
    ProductComplex product_complex;
    ImpliedMarketIndicator implied_market_indicator;
    NoLegs no_legs;
    Pad1 pad_1;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13400;

    // parse method
    static AddComplexInstrumentMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddComplexInstrumentMessage*>(buffer);
    }

    // parse method const
    static const AddComplexInstrumentMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddComplexInstrumentMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddComplexInstrumentMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddComplexInstrumentMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
