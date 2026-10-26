#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/HaltReason.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/LimitUpLimitDownLuldIndicator.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../messages/TradeMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_11_b {

class TradeMessagePayloadVisitor;

// Transmitted when a Participant in a CTA eligible security, Local Issue or a Bond elects to
// notify CTS of a Trading Halt, a Trading Resume, a Price Indication or a Market Imbalance
class TradingStatusMessage : public TradeMessagePayload {
  public:
    // The code that selects this message
    static constexpr TradeMessagePayloadCode message_type = TradeMessageType::TradingStatus;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 72;

    TradingStatusMessage() = default;
    TradingStatusMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, Decimal last_price, Decimal high_indication_price_upper_limit_price_band, Decimal low_indication_price_lower_limit_price_band, std::uint32_t buy_volume, std::uint32_t sell_volume, SecurityStatus security_status, HaltReason halt_reason, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, LimitUpLimitDownLuldIndicator limit_up_limit_down_luld_indicator);

    // Participant Id: Identifies the Participant or Processor that initiated the message
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Timestamp 1: Timestamp 1
    const Timestamp1& timestamp_1() const;
    Timestamp1& timestamp_1();
    void set_timestamp_1(const Timestamp1& value);

    // Message Id: The Message ID identifies the individual message within the block beginning
    // with number one
    std::uint8_t message_id() const;
    void set_message_id(std::uint8_t value);

    // Transaction Id: Identifies the transaction
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Contains the Participant Reference Number
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Security Symbol: Identifies the Security Symbol. Left justified, space-filled
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Instrument Type: Identifies the instrument type relevant to the trade
    InstrumentType instrument_type() const;
    void set_instrument_type(InstrumentType value);

    // Last Price: Represents the last price for that security either on a Consolidated or an
    // individual Participant basis at the time it is disseminated. Has implied 6 decimal
    // places
    Decimal last_price() const;
    void set_last_price(Decimal value);

    // High Indication Price Upper Limit Price Band: Represents an approximation of what the
    // high end Offer price of a security's trading range may be, or the upper price band value
    // for a security. Has implied 6 decimal places
    Decimal high_indication_price_upper_limit_price_band() const;
    void set_high_indication_price_upper_limit_price_band(Decimal value);

    // Low Indication Price Lower Limit Price Band: Represents an approximation of what the low
    // end Bid price of a security's trading range may be, or the lower price band value for a
    // security. Has implied 6 decimal places
    Decimal low_indication_price_lower_limit_price_band() const;
    void set_low_indication_price_lower_limit_price_band(Decimal value);

    // Buy Volume: Represents the reported imbalance of buy orders without matching sell orders
    // for the security for a Participant
    std::uint32_t buy_volume() const;
    void set_buy_volume(std::uint32_t value);

    // Sell Volume: Represents the reported imbalance of sell orders without matching buy
    // orders for the security for a Participant
    std::uint32_t sell_volume() const;
    void set_sell_volume(std::uint32_t value);

    // Security Status: Identifies the trading status applicable to the transaction
    SecurityStatus security_status() const;
    void set_security_status(SecurityStatus value);

    // Halt Reason: Denotes the reason for the Trading Halt
    HaltReason halt_reason() const;
    void set_halt_reason(HaltReason value);

    // Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is
    // in effect for a security
    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const;
    void set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market of the
    // security symbol
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Financial Status Indicator: Identifies the financial status of the security
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Limit Up Limit Down Luld Indicator: Identifies the Limit Up-Limit Down action related to
    // a security
    LimitUpLimitDownLuldIndicator limit_up_limit_down_luld_indicator() const;
    void set_limit_up_limit_down_luld_indicator(LimitUpLimitDownLuldIndicator value);

    // TradeMessagePayload
    TradeMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(TradeMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<TradeMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const TradeMessagePayload& other) const override;

    bool operator==(const TradingStatusMessage& other) const;
    bool operator!=(const TradingStatusMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    Decimal last_price_{ 0, -6 };
    Decimal high_indication_price_upper_limit_price_band_{ 0, -6 };
    Decimal low_indication_price_lower_limit_price_band_{ 0, -6 };
    std::uint32_t buy_volume_{};
    std::uint32_t sell_volume_{};
    SecurityStatus security_status_{};
    HaltReason halt_reason_{};
    ShortSaleRestrictionIndicator short_sale_restriction_indicator_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    FinancialStatusIndicator financial_status_indicator_{};
    LimitUpLimitDownLuldIndicator limit_up_limit_down_luld_indicator_{};
};

} // namespace siac::cts::output::cta::v2_11_b
