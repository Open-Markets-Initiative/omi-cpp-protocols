#pragma once

#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecuritySubType.hpp"
#include "../types/ProductComplex.hpp"
#include "../types/ImpliedMarketIndicator.hpp"
#include "../types/NoLegs.hpp"
#include "../types/Pad1.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

// 
struct AddComplexInstrument {

    SecurityId security_id;
    TransactTime transact_time;
    SecuritySubType security_sub_type;
    ProductComplex product_complex;
    ImpliedMarketIndicator implied_market_indicator;
    NoLegs no_legs;
    Pad1 pad1;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13400;

    // parse method
    static AddComplexInstrument* parse(std::byte* buffer) {
        return reinterpret_cast<AddComplexInstrument*>(buffer);
    }

    // parse method const
    static const AddComplexInstrument* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddComplexInstrument*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddComplexInstrument* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const AddComplexInstrument*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
