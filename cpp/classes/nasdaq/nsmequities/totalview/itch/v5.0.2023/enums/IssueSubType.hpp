#pragma once

#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Identifies the security sub-type for the issue as assigned by NASDAQ
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct IssueSubType {
    static constexpr std::string_view PreferredTrustSecurities = "A";                      // Preferred Trust Securities
    static constexpr std::string_view AlphaIndexEtNs = "AI";                               // Alpha Index Et Ns
    static constexpr std::string_view IndexBasedDerivative = "B";                          // Index Based Derivative
    static constexpr std::string_view CommonShares = "C";                                  // Common Shares
    static constexpr std::string_view CommodityBasedTrustShares = "CB";                    // Commodity Based Trust Shares
    static constexpr std::string_view CommodityFuturesTrustShares = "CF";                  // Commodity Futures Trust Shares
    static constexpr std::string_view CommodityLinkedSecurities = "CL";                    // Commodity Linked Securities
    static constexpr std::string_view CommodityIndexTrustShares = "CM";                    // Commodity Index Trust Shares
    static constexpr std::string_view CollateralizedMortgageObligation = "CO";             // Collateralized Mortgage Obligation
    static constexpr std::string_view CurrencyTrustShares = "CT";                          // Currency Trust Shares
    static constexpr std::string_view CommodityCurrencyLinkedSecurities = "CU";            // Commodity Currency Linked Securities
    static constexpr std::string_view CurrencyWarrants = "CW";                             // Currency Warrants
    static constexpr std::string_view GlobalDepositaryShares = "D";                        // Global Depositary Shares
    static constexpr std::string_view EtfPortfolioDepositaryReceipt = "E";                 // Etf Portfolio Depositary Receipt
    static constexpr std::string_view EquityGoldShares = "EG";                             // Equity Gold Shares
    static constexpr std::string_view EtnEquityIndexLinkedSecurities = "EI";               // Etn Equity Index Linked Securities
    static constexpr std::string_view NextSharesExchangeTradedManagedFund = "EM";          // Next Shares Exchange Traded Managed Fund
    static constexpr std::string_view ExchangeTradedNotes = "EN";                          // Exchange Traded Notes
    static constexpr std::string_view EquityUnits = "EU";                                  // Equity Units
    static constexpr std::string_view Holdrs = "F";                                        // Holdrs
    static constexpr std::string_view EtnFixedIncomeLinkedSecurities = "FI";               // Etn Fixed Income Linked Securities
    static constexpr std::string_view EtnFuturesLinkedSecurities = "FL";                   // Etn Futures Linked Securities
    static constexpr std::string_view GlobalShares = "G";                                  // Global Shares
    static constexpr std::string_view EtfIndexFundShares = "I";                            // Etf Index Fund Shares
    static constexpr std::string_view InterestRate = "IR";                                 // Interest Rate
    static constexpr std::string_view IndexWarrant = "IW";                                 // Index Warrant
    static constexpr std::string_view IndexLinkedExchangeableNotes = "IX";                 // Index Linked Exchangeable Notes
    static constexpr std::string_view CorporateBackedTrustSecurity = "J";                  // Corporate Backed Trust Security
    static constexpr std::string_view ContingentLitigationRight = "L";                     // Contingent Litigation Right
    static constexpr std::string_view LimitedLiabilityCompany = "LL";                      // Limited Liability Company
    static constexpr std::string_view EquityBasedDerivative = "M";                         // Equity Based Derivative
    static constexpr std::string_view ManagedFundShares = "MF";                            // Managed Fund Shares
    static constexpr std::string_view EtnMultiFactorIndexLinkedSecurities = "ML";          // Etn Multi Factor Index Linked Securities
    static constexpr std::string_view ManagedTrustSecurities = "MT";                       // Managed Trust Securities
    static constexpr std::string_view NyRegistryShares = "N";                              // Ny Registry Shares
    static constexpr std::string_view OpenEndedMutualFund = "O";                           // Open Ended Mutual Fund
    static constexpr std::string_view PrivatelyHeldSecurity = "P";                         // Privately Held Security
    static constexpr std::string_view PoisonPill = "PP";                                   // Poison Pill
    static constexpr std::string_view PartnershipUnits = "PU";                             // Partnership Units
    static constexpr std::string_view ClosedEndFunds = "Q";                                // Closed End Funds
    static constexpr std::string_view RegS = "R";                                          // Reg S
    static constexpr std::string_view CommodityRedeemableCommodityLinkedSecurities = "RC"; // Commodity Redeemable Commodity Linked Securities
    static constexpr std::string_view EtnRedeemableFuturesLinkedSecurities = "RF";         // Etn Redeemable Futures Linked Securities
    static constexpr std::string_view Reit = "RT";                                         // Reit
    static constexpr std::string_view CommodityRedeemableCurrencyLinkedSecurities = "RU";  // Commodity Redeemable Currency Linked Securities
    static constexpr std::string_view Seed = "S";                                          // Seed
    static constexpr std::string_view SpotRateClosing = "SC";                              // Spot Rate Closing
    static constexpr std::string_view SpotRateIntraday = "SI";                             // Spot Rate Intraday
    static constexpr std::string_view TrackingStock = "T";                                 // Tracking Stock
    static constexpr std::string_view TrustCertificates = "TC";                            // Trust Certificates
    static constexpr std::string_view TrustUnits = "TU";                                   // Trust Units
    static constexpr std::string_view Portal = "U";                                        // Portal
    static constexpr std::string_view ContingentValueRight = "V";                          // Contingent Value Right
    static constexpr std::string_view TrustIssuedReceipts = "W";                           // Trust Issued Receipts
    static constexpr std::string_view WorldCurrencyOption = "WC";                          // World Currency Option
    static constexpr std::string_view Trust = "X";                                         // Trust
    static constexpr std::string_view Other = "Y";                                         // Other
    static constexpr std::string_view NotApplicable = "Z";                                 // Not Applicable

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == PreferredTrustSecurities) { return "Preferred Trust Securities"; }
        if (code == AlphaIndexEtNs) { return "Alpha Index Et Ns"; }
        if (code == IndexBasedDerivative) { return "Index Based Derivative"; }
        if (code == CommonShares) { return "Common Shares"; }
        if (code == CommodityBasedTrustShares) { return "Commodity Based Trust Shares"; }
        if (code == CommodityFuturesTrustShares) { return "Commodity Futures Trust Shares"; }
        if (code == CommodityLinkedSecurities) { return "Commodity Linked Securities"; }
        if (code == CommodityIndexTrustShares) { return "Commodity Index Trust Shares"; }
        if (code == CollateralizedMortgageObligation) { return "Collateralized Mortgage Obligation"; }
        if (code == CurrencyTrustShares) { return "Currency Trust Shares"; }
        if (code == CommodityCurrencyLinkedSecurities) { return "Commodity Currency Linked Securities"; }
        if (code == CurrencyWarrants) { return "Currency Warrants"; }
        if (code == GlobalDepositaryShares) { return "Global Depositary Shares"; }
        if (code == EtfPortfolioDepositaryReceipt) { return "Etf Portfolio Depositary Receipt"; }
        if (code == EquityGoldShares) { return "Equity Gold Shares"; }
        if (code == EtnEquityIndexLinkedSecurities) { return "Etn Equity Index Linked Securities"; }
        if (code == NextSharesExchangeTradedManagedFund) { return "Next Shares Exchange Traded Managed Fund"; }
        if (code == ExchangeTradedNotes) { return "Exchange Traded Notes"; }
        if (code == EquityUnits) { return "Equity Units"; }
        if (code == Holdrs) { return "Holdrs"; }
        if (code == EtnFixedIncomeLinkedSecurities) { return "Etn Fixed Income Linked Securities"; }
        if (code == EtnFuturesLinkedSecurities) { return "Etn Futures Linked Securities"; }
        if (code == GlobalShares) { return "Global Shares"; }
        if (code == EtfIndexFundShares) { return "Etf Index Fund Shares"; }
        if (code == InterestRate) { return "Interest Rate"; }
        if (code == IndexWarrant) { return "Index Warrant"; }
        if (code == IndexLinkedExchangeableNotes) { return "Index Linked Exchangeable Notes"; }
        if (code == CorporateBackedTrustSecurity) { return "Corporate Backed Trust Security"; }
        if (code == ContingentLitigationRight) { return "Contingent Litigation Right"; }
        if (code == LimitedLiabilityCompany) { return "Limited Liability Company"; }
        if (code == EquityBasedDerivative) { return "Equity Based Derivative"; }
        if (code == ManagedFundShares) { return "Managed Fund Shares"; }
        if (code == EtnMultiFactorIndexLinkedSecurities) { return "Etn Multi Factor Index Linked Securities"; }
        if (code == ManagedTrustSecurities) { return "Managed Trust Securities"; }
        if (code == NyRegistryShares) { return "Ny Registry Shares"; }
        if (code == OpenEndedMutualFund) { return "Open Ended Mutual Fund"; }
        if (code == PrivatelyHeldSecurity) { return "Privately Held Security"; }
        if (code == PoisonPill) { return "Poison Pill"; }
        if (code == PartnershipUnits) { return "Partnership Units"; }
        if (code == ClosedEndFunds) { return "Closed End Funds"; }
        if (code == RegS) { return "Reg S"; }
        if (code == CommodityRedeemableCommodityLinkedSecurities) { return "Commodity Redeemable Commodity Linked Securities"; }
        if (code == EtnRedeemableFuturesLinkedSecurities) { return "Etn Redeemable Futures Linked Securities"; }
        if (code == Reit) { return "Reit"; }
        if (code == CommodityRedeemableCurrencyLinkedSecurities) { return "Commodity Redeemable Currency Linked Securities"; }
        if (code == Seed) { return "Seed"; }
        if (code == SpotRateClosing) { return "Spot Rate Closing"; }
        if (code == SpotRateIntraday) { return "Spot Rate Intraday"; }
        if (code == TrackingStock) { return "Tracking Stock"; }
        if (code == TrustCertificates) { return "Trust Certificates"; }
        if (code == TrustUnits) { return "Trust Units"; }
        if (code == Portal) { return "Portal"; }
        if (code == ContingentValueRight) { return "Contingent Value Right"; }
        if (code == TrustIssuedReceipts) { return "Trust Issued Receipts"; }
        if (code == WorldCurrencyOption) { return "World Currency Option"; }
        if (code == Trust) { return "Trust"; }
        if (code == Other) { return "Other"; }
        if (code == NotApplicable) { return "Not Applicable"; }
        return {};
    }
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
