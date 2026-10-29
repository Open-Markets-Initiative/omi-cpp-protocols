#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/ActiveOnMiax.hpp"
#include "../types/Reserved1.hpp"
#include "../types/UpdateReason.hpp"
#include "../types/Reserved10.hpp"
#include "../types/NumberOfLegs.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate stock option strategies traded on MIAX for the current session.
struct ComplexStrategyDefinitionMessage {

    Nanoseconds nanoseconds;
    StrategyId strategy_id;
    UnderlyingSymbol underlying_symbol;
    ActiveOnMiax active_on_miax;
    Reserved1 reserved_1;
    UpdateReason update_reason;
    Reserved10 reserved_10;
    NumberOfLegs number_of_legs;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'C';

    // parse method
    static ComplexStrategyDefinitionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexStrategyDefinitionMessage*>(buffer);
    }

    // parse method const
    static const ComplexStrategyDefinitionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexStrategyDefinitionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexStrategyDefinitionMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const ComplexStrategyDefinitionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
