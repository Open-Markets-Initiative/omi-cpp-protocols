#include "TradeCondition.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

std::string_view to_string(TradeCondition value) {
    switch (value) {
        case TradeCondition::SingleLegAuctionNonIsoCboeAuctionTypesIncludeAimSam: return "Single Leg Auction Non Iso Cboe Auction Types Include Aim Sam";
        case TradeCondition::SingleLegAuctionIsoCboeAuctionTypesAreAimIsoSamIso: return "Single Leg Auction Iso Cboe Auction Types Are Aim Iso Sam Iso";
        case TradeCondition::SingleLegCrossNonIsoCboeAuctionTypesIncludeCustToCustAimQcc: return "Single Leg Cross Non Iso Cboe Auction Types Include Cust To Cust Aim Qcc";
        case TradeCondition::SingleLegCrossIsoCboeOrderTypeIsCustToCustAimIso: return "Single Leg Cross Iso Cboe Order Type Is Cust To Cust Aim Iso";
        case TradeCondition::SingleLegFloorTrade: return "Single Leg Floor Trade";
        case TradeCondition::ComplexToComplexElectronicTrade: return "Complex To Complex Electronic Trade";
        case TradeCondition::ComplexAuctionTrade: return "Complex Auction Trade";
        case TradeCondition::ComplexCross: return "Complex Cross";
        case TradeCondition::ComplexElectronicTradeAgainstSingleLegs: return "Complex Electronic Trade Against Single Legs";
        case TradeCondition::ComplexWithStockOptionsAuctionTrade: return "Complex With Stock Options Auction Trade";
        case TradeCondition::ComplexFloorTradeAgainstSingleLegs: return "Complex Floor Trade Against Single Legs";
        case TradeCondition::ComplexWithStockElectronicTrade: return "Complex With Stock Electronic Trade";
        case TradeCondition::ComplexWithStockCross: return "Complex With Stock Cross";
        case TradeCondition::ComplexWithStockFloorTrade: return "Complex With Stock Floor Trade";
        case TradeCondition::ComplexFloorTradeOfProprietaryProductsMarkedAsComboOrder: return "Complex Floor Trade Of Proprietary Products Marked As Combo Order";
        case TradeCondition::MultilateralCompressionTradeOfProprietaryProducts: return "Multilateral Compression Trade Of Proprietary Products";
        case TradeCondition::ExtendedHoursTrade: return "Extended Hours Trade";
        case TradeCondition::ElectronicTrade: return "Electronic Trade";
        case TradeCondition::CabinetOrder: return "Cabinet Order";
        case TradeCondition::FutureOptionsAuctionTradeElectronicExecutionOfAMultiLegFutureoptionsOrderTradedInATwoSidedAuction: return "Future Options Auction Trade Electronic Execution Of A Multi Leg Futureoptions Order Traded In A Two Sided Auction";
        case TradeCondition::FutureOptionsAutoElectronicTradeElectronicExecutionOfAMultiLegFutureoptionsOrderTradedOnTheComplexBookOrInACoa: return "Future Options Auto Electronic Trade Electronic Execution Of A Multi Leg Futureoptions Order Traded On The Complex Book Or In A Coa";
        case TradeCondition::FutureOptionsCrossElectronicExecutionOfAMultiLegFutureoptionsOrderTradedInATwoSidedCrossingMechanismThatDoesNotGoThroughAnExposurePeriod: return "Future Options Cross Electronic Execution Of A Multi Leg Futureoptions Order Traded In A Two Sided Crossing Mechanism That Does Not Go Through An Exposure Period";
        case TradeCondition::OpeningTrade: return "Opening Trade";
        case TradeCondition::Iso: return "Iso";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
