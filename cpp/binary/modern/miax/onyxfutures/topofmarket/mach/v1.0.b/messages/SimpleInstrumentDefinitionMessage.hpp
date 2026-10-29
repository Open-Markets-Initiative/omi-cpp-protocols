#pragma once

#include "../types/Timestamp.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/UnderlyingAssetType.hpp"
#include "../types/UnderlyingAsset.hpp"
#include "../types/ProductGroupCode.hpp"
#include "../types/Exchange.hpp"
#include "../types/InstrumentIdSource.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/MaturityMonthYear.hpp"
#include "../types/Currency.hpp"
#include "../types/SettlementCurrency.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinimumSize.hpp"
#include "../types/MaximumSize.hpp"
#include "../types/Tick.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQuantity.hpp"
#include "../types/SettlementPrice.hpp"
#include "../types/SettlementPriceTypeCalcMethod.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/OpenInterestQuantity.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/TradingCollarVariationType.hpp"
#include "../types/TradingCollarVariation.hpp"
#include "../types/Reserved16.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

#pragma pack(push, 1)

// used to disseminate all Simple Instruments traded on MIAX FuturesOnyx for the current trading session
struct SimpleInstrumentDefinitionMessage {

    Timestamp timestamp;
    InstrumentId instrument_id;
    UnderlyingAssetType underlying_asset_type;
    UnderlyingAsset underlying_asset;
    ProductGroupCode product_group_code;
    Exchange exchange;
    InstrumentIdSource instrument_id_source;
    InstrumentType instrument_type;
    MaturityMonthYear maturity_month_year;
    Currency currency;
    SettlementCurrency settlement_currency;
    MatchAlgorithm match_algorithm;
    MinimumSize minimum_size;
    MaximumSize maximum_size;
    Tick tick;
    UnitOfMeasure unit_of_measure;
    UnitOfMeasureQuantity unit_of_measure_quantity;
    SettlementPrice settlement_price;
    SettlementPriceTypeCalcMethod settlement_price_type_calc_method;
    TotalVolume total_volume;
    OpenInterestQuantity open_interest_quantity;
    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    TradingCollarVariationType trading_collar_variation_type;
    TradingCollarVariation trading_collar_variation;
    Reserved16 reserved_16;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 1;

    // parse method
    static SimpleInstrumentDefinitionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SimpleInstrumentDefinitionMessage*>(buffer);
    }

    // parse method const
    static const SimpleInstrumentDefinitionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SimpleInstrumentDefinitionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SimpleInstrumentDefinitionMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SimpleInstrumentDefinitionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
