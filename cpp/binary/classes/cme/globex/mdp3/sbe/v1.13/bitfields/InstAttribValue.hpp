#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_13 {

// InstAttribValue bit set
class InstAttribValue {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 4;

    InstAttribValue() = default;
    explicit InstAttribValue(std::uint32_t raw);

    // Electronic Match Eligible: ElectronicMatchEligible
    bool electronic_match_eligible() const;
    void set_electronic_match_eligible(bool value);

    // Order Cross Eligible: OrderCrossEligible
    bool order_cross_eligible() const;
    void set_order_cross_eligible(bool value);

    // Block Trade Eligible: BlockTradeEligible
    bool block_trade_eligible() const;
    void set_block_trade_eligible(bool value);

    // Efp Eligible: EFPEligible
    bool efp_eligible() const;
    void set_efp_eligible(bool value);

    // Ebf Eligible: EBFEligible
    bool ebf_eligible() const;
    void set_ebf_eligible(bool value);

    // Efs Eligible: EFSEligible
    bool efs_eligible() const;
    void set_efs_eligible(bool value);

    // Efr Eligible: EFREligible
    bool efr_eligible() const;
    void set_efr_eligible(bool value);

    // Otc Eligible: OTCEligible
    bool otc_eligible() const;
    void set_otc_eligible(bool value);

    // ILink Indicative Mass Quoting Eligible: iLinkIndicativeMassQuotingEligible
    bool ilink_indicative_mass_quoting_eligible() const;
    void set_ilink_indicative_mass_quoting_eligible(bool value);

    // Negative Strike Eligible: NegativeStrikeEligible
    bool negative_strike_eligible() const;
    void set_negative_strike_eligible(bool value);

    // Negative Price Outright Eligible: NegativePriceOutrightEligible
    bool negative_price_outright_eligible() const;
    void set_negative_price_outright_eligible(bool value);

    // Is Fractional: IsFractional
    bool is_fractional() const;
    void set_is_fractional(bool value);

    // Volatility Quoted Option: VolatilityQuotedOption
    bool volatility_quoted_option() const;
    void set_volatility_quoted_option(bool value);

    // Rfq Cross Eligible: RFQCrossEligible
    bool rfq_cross_eligible() const;
    void set_rfq_cross_eligible(bool value);

    // Zero Price Outright Eligible: ZeroPriceOutrightEligible
    bool zero_price_outright_eligible() const;
    void set_zero_price_outright_eligible(bool value);

    // Decaying Product Eligibility: DecayingProductEligibility
    bool decaying_product_eligibility() const;
    void set_decaying_product_eligibility(bool value);

    // Variable Product Eligibility: VariableProductEligibility
    bool variable_product_eligibility() const;
    void set_variable_product_eligibility(bool value);

    // Daily Product Eligibility: DailyProductEligibility
    bool daily_product_eligibility() const;
    void set_daily_product_eligibility(bool value);

    // Gt Orders Eligibility: GTOrdersEligibility
    bool gt_orders_eligibility() const;
    void set_gt_orders_eligibility(bool value);

    // Implied Matching Eligibility: ImpliedMatchingEligibility
    bool implied_matching_eligibility() const;
    void set_implied_matching_eligibility(bool value);

    // Triangulation Eligible: TriangulationEligible
    bool triangulation_eligible() const;
    void set_triangulation_eligible(bool value);

    // Variable Cab Eligible: VariableCabEligible
    bool variable_cab_eligible() const;
    void set_variable_cab_eligible(bool value);

    // Inverted Book: InvertedBook
    bool inverted_book() const;
    void set_inverted_book(bool value);

    // Is Aon Instrument: IsAoNInstrument
    bool is_aon_instrument() const;
    void set_is_aon_instrument(bool value);

    // Sef Regulated: SEFRegulated
    bool sef_regulated() const;
    void set_sef_regulated(bool value);

    // Mtf Regulated: MTFRegulated
    bool mtf_regulated() const;
    void set_mtf_regulated(bool value);

    // Efix Instrument: eFIXInstrument
    bool efix_instrument() const;
    void set_efix_instrument(bool value);

    // Hedge Instrument: HedgeInstrument
    bool hedge_instrument() const;
    void set_hedge_instrument(bool value);

    // Reserved 4: 4 reserved bits
    std::uint8_t reserved_4() const;
    void set_reserved_4(std::uint8_t value);

    // The whole bitfield as its wire integer
    std::uint32_t raw() const;
    void set_raw(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const InstAttribValue& other) const;
    bool operator!=(const InstAttribValue& other) const;

  private:
    std::uint32_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const InstAttribValue& value);

} // namespace cme::globex::mdp3::sbe::v1_13
