#pragma once

#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityDesc.hpp"
#include "../types/SecurityType.hpp"
#include "../types/PutOrCall.hpp"
#include "../types/ExerciseStyle.hpp"
#include "../types/SettlMethod.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/OptAttribute.hpp"
#include "../types/ContractDate.hpp"
#include "../types/SecurityReferenceDataSupplement.hpp"
#include "../types/Pad4.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

// 
struct AddFlexibleInstrument {

    SecurityId security_id;
    TransactTime transact_time;
    SecurityDesc security_desc;
    SecurityType security_type;
    PutOrCall put_or_call;
    ExerciseStyle exercise_style;
    SettlMethod settl_method;
    MaturityDate maturity_date;
    StrikePrice strike_price;
    OptAttribute opt_attribute;
    ContractDate contract_date;
    SecurityReferenceDataSupplement security_reference_data_supplement;
    Pad4 pad4;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13401;

    // parse method
    static AddFlexibleInstrument* parse(std::byte* buffer) {
        return reinterpret_cast<AddFlexibleInstrument*>(buffer);
    }

    // parse method const
    static const AddFlexibleInstrument* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddFlexibleInstrument*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddFlexibleInstrument* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const AddFlexibleInstrument*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
