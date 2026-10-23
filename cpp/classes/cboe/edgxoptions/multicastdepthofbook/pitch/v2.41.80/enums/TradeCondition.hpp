#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Options Only (byte not sent in Equities). See Options Trade Condition Codes on page 180
// section for details about new codes.
enum class TradeCondition : char {
    SingleLegAuctionNonIsoCboeAuctionTypesIncludeAimSam = 'a',                                                                                      // Single Leg Auction Non Iso Cboe Auction Types Include Aim Sam
    SingleLegAuctionIsoCboeAuctionTypesAreAimIsoSamIso = 'b',                                                                                       // Single Leg Auction Iso Cboe Auction Types Are Aim Iso Sam Iso
    SingleLegCrossNonIsoCboeAuctionTypesIncludeCustToCustAimQcc = 'c',                                                                              // Single Leg Cross Non Iso Cboe Auction Types Include Cust To Cust Aim Qcc
    SingleLegCrossIsoCboeOrderTypeIsCustToCustAimIso = 'd',                                                                                         // Single Leg Cross Iso Cboe Order Type Is Cust To Cust Aim Iso
    SingleLegFloorTrade = 'e',                                                                                                                      // Single Leg Floor Trade
    ComplexToComplexElectronicTrade = 'f',                                                                                                          // Complex To Complex Electronic Trade
    ComplexAuctionTrade = 'g',                                                                                                                      // Complex Auction Trade
    ComplexCross = 'h',                                                                                                                             // Complex Cross
    ComplexElectronicTradeAgainstSingleLegs = 'j',                                                                                                  // Complex Electronic Trade Against Single Legs
    ComplexWithStockOptionsAuctionTrade = 'k',                                                                                                      // Complex With Stock Options Auction Trade
    ComplexFloorTradeAgainstSingleLegs = 'm',                                                                                                       // Complex Floor Trade Against Single Legs
    ComplexWithStockElectronicTrade = 'n',                                                                                                          // Complex With Stock Electronic Trade
    ComplexWithStockCross = 'o',                                                                                                                    // Complex With Stock Cross
    ComplexWithStockFloorTrade = 'p',                                                                                                               // Complex With Stock Floor Trade
    ComplexFloorTradeOfProprietaryProductsMarkedAsComboOrder = 't',                                                                                 // Complex Floor Trade Of Proprietary Products Marked As Combo Order
    MultilateralCompressionTradeOfProprietaryProducts = 'u',                                                                                        // Multilateral Compression Trade Of Proprietary Products
    ExtendedHoursTrade = 'v',                                                                                                                       // Extended Hours Trade
    ElectronicTrade = 'I',                                                                                                                          // Electronic Trade
    CabinetOrder = 'K',                                                                                                                             // Cabinet Order
    FutureOptionsAuctionTradeElectronicExecutionOfAMultiLegFutureoptionsOrderTradedInATwoSidedAuction = 'M',                                        // Future Options Auction Trade Electronic Execution Of A Multi Leg Futureoptions Order Traded In A Two Sided Auction
    FutureOptionsAutoElectronicTradeElectronicExecutionOfAMultiLegFutureoptionsOrderTradedOnTheComplexBookOrInACoa = 'N',                           // Future Options Auto Electronic Trade Electronic Execution Of A Multi Leg Futureoptions Order Traded On The Complex Book Or In A Coa
    FutureOptionsCrossElectronicExecutionOfAMultiLegFutureoptionsOrderTradedInATwoSidedCrossingMechanismThatDoesNotGoThroughAnExposurePeriod = 'P', // Future Options Cross Electronic Execution Of A Multi Leg Futureoptions Order Traded In A Two Sided Crossing Mechanism That Does Not Go Through An Exposure Period
    OpeningTrade = 'O',                                                                                                                             // Opening Trade
    Iso = 'S',                                                                                                                                      // Iso
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCondition value);

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
