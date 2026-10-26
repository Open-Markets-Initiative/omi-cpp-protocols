#pragma once

#include "../types/InstrumentScopeProductComplex.hpp"
#include "../types/SecurityMassStatus.hpp"
#include "../types/SecurityMassTradingStatus.hpp"
#include "../types/MassMarketCondition.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/SecurityMassTradingEvent.hpp"
#include "../types/MassSoldOutIndicator.hpp"
#include "../types/TesSecurityMassStatus.hpp"
#include "../types/TransactTime.hpp"
#include "../types/LastFragment.hpp"
#include "../types/NoRelatedSym.hpp"
#include "../types/Pad6.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

// 
struct MassInstrumentStateChange {

    InstrumentScopeProductComplex instrument_scope_product_complex;
    SecurityMassStatus security_mass_status;
    SecurityMassTradingStatus security_mass_trading_status;
    MassMarketCondition mass_market_condition;
    FastMarketIndicator fast_market_indicator;
    SecurityMassTradingEvent security_mass_trading_event;
    MassSoldOutIndicator mass_sold_out_indicator;
    TesSecurityMassStatus tes_security_mass_status;
    TransactTime transact_time;
    LastFragment last_fragment;
    NoRelatedSym no_related_sym;
    Pad6 pad6;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13302;

    // parse method
    static MassInstrumentStateChange* parse(std::byte* buffer) {
        return reinterpret_cast<MassInstrumentStateChange*>(buffer);
    }

    // parse method const
    static const MassInstrumentStateChange* parse(const std::byte* buffer) {
        return reinterpret_cast<const MassInstrumentStateChange*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MassInstrumentStateChange* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const MassInstrumentStateChange*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
