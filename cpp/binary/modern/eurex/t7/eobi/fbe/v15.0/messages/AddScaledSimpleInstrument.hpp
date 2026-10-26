#pragma once

#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityDesc.hpp"
#include "../types/SecurityType.hpp"
#include "../types/Pad1.hpp"
#include "../types/QuantityScalingFactor.hpp"
#include "../types/Pad4.hpp"
#include "../structs/RelatedInstrumentGrpComp.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

#pragma pack(push, 1)

// 
struct AddScaledSimpleInstrument {

    SecurityId security_id;
    TransactTime transact_time;
    SecurityDesc security_desc;
    SecurityType security_type;
    Pad1 pad1;
    QuantityScalingFactor quantity_scaling_factor;
    Pad4 pad4;
    RelatedInstrumentGrpComp related_instrument_grp_comp;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13402;

    // parse method
    static AddScaledSimpleInstrument* parse(std::byte* buffer) {
        return reinterpret_cast<AddScaledSimpleInstrument*>(buffer);
    }

    // parse method const
    static const AddScaledSimpleInstrument* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddScaledSimpleInstrument*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddScaledSimpleInstrument* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const AddScaledSimpleInstrument*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
