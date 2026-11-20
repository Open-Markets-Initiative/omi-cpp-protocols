// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: iterators/SecurityDefinitionLegIterator.hpp
#pragma once

#include "../definitions.hpp"
#include "../structs/SecurityType.hpp"
#include "../types/SecurityExchange.hpp"
#include "../structs/Symbol.hpp"
#include "../structs/TargetLocationId.hpp"
#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/PriceType.hpp"
#include "../structs/StrikePrice.hpp"
#include "../types/PutOrCall.hpp"
#include "../structs/MinimumStrikePriceFraction.hpp"
#include "../structs/MaxStrikePrice.hpp"
#include "../structs/PremiumBreakPoint.hpp"
#include "../structs/MinimumAbovePremiumFraction.hpp"
#include "../structs/MinimumBelowPremiumFraction.hpp"
#include "../types/ExerciseStyle.hpp"
#include "../structs/CurrencyCode.hpp"
#include "../structs/UnderlyingSymbol.hpp"
#include "../structs/UnderlyingType.hpp"
#include "../types/ContractSize.hpp"
#include "../types/NoLegs.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {
// SecurityDefinitionLegIterator
struct SecurityDefinitionLegIterator {

    const std::byte* current = nullptr;

    const SecurityDefinitionMessage* security_definition_message = nullptr;

    std::uint8_t no_legs = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        security_definition_message = SecurityDefinitionMessage::parse(current);

        // no_legs lies behind what SecurityDefinitionMessage holds: step over what is in front of it
        current += sizeof(SecurityType) + SecurityType::parse(current)->security_type_length.get();
        current += sizeof(SecurityExchange);
        current += sizeof(Symbol) + Symbol::parse(current)->symbol_length.get();
        current += sizeof(TargetLocationId) + TargetLocationId::parse(current)->target_location_id_length.get();
        current += sizeof(ClassKey);
        current += sizeof(SecurityId);
        current += sizeof(MaturityDate);
        current += sizeof(PriceType);
        current += sizeof(StrikePrice);
        current += sizeof(PutOrCall);
        current += sizeof(MinimumStrikePriceFraction);
        current += sizeof(MaxStrikePrice);
        current += sizeof(PremiumBreakPoint);
        current += sizeof(MinimumAbovePremiumFraction);
        current += sizeof(MinimumBelowPremiumFraction);
        current += sizeof(ExerciseStyle);
        current += sizeof(CurrencyCode) + CurrencyCode::parse(current)->currency_code_length.get();
        current += sizeof(UnderlyingSymbol) + UnderlyingSymbol::parse(current)->underlying_symbol_length.get();
        current += sizeof(UnderlyingType) + UnderlyingType::parse(current)->underlying_type_length.get();
        current += sizeof(ContractSize);

        no_legs = reinterpret_cast<const NoLegs*>(current)->get();
        current += sizeof(NoLegs);
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= no_legs) {
            return false;
        }

        entry = current;
        entry_index++;

        return true;
    }

    // advance past processed entry
    void advance(std::size_t bytes) {
        current += bytes;
    }

    // reset iterator
    void reset() {
        current = nullptr;

        security_definition_message = nullptr;

        no_legs = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
