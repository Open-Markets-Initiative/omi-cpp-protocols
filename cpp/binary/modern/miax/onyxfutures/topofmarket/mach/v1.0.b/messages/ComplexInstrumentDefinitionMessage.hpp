#pragma once

#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/UnderlyingAssetType.hpp"
#include "../types/UnderlyingAsset.hpp"
#include "../types/ProductGroupCode.hpp"
#include "../types/SpreadType.hpp"
#include "../types/Exchange.hpp"
#include "../types/InstrumentIdSource.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/Currency.hpp"
#include "../types/SettlementCurrency.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinimumSize.hpp"
#include "../types/MaximumSize.hpp"
#include "../types/Tick.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQuantity.hpp"
#include "../types/TradingCollarVariationType.hpp"
#include "../types/TradingCollarVariation.hpp"
#include "../types/Reserved16.hpp"
#include "../types/NumberOfLegs.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

#pragma pack(push, 1)

// Used to disseminate all Complex Instruments traded on MIAX Futures Onyx for the current trading session
struct ComplexInstrumentDefinitionMessage {

    Timestamp timestamp;
    StrategyId strategy_id;
    UnderlyingAssetType underlying_asset_type;
    UnderlyingAsset underlying_asset;
    ProductGroupCode product_group_code;
    SpreadType spread_type;
    Exchange exchange;
    InstrumentIdSource instrument_id_source;
    InstrumentType instrument_type;
    Currency currency;
    SettlementCurrency settlement_currency;
    MatchAlgorithm match_algorithm;
    MinimumSize minimum_size;
    MaximumSize maximum_size;
    Tick tick;
    UnitOfMeasure unit_of_measure;
    UnitOfMeasureQuantity unit_of_measure_quantity;
    TradingCollarVariationType trading_collar_variation_type;
    TradingCollarVariation trading_collar_variation;
    Reserved16 reserved_16;
    NumberOfLegs number_of_legs;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 2;

    // parse method
    static ComplexInstrumentDefinitionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexInstrumentDefinitionMessage*>(buffer);
    }

    // parse method const
    static const ComplexInstrumentDefinitionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexInstrumentDefinitionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexInstrumentDefinitionMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const ComplexInstrumentDefinitionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
