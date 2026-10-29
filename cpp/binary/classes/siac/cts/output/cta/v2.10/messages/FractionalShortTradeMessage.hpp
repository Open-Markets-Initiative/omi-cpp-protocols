#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ConsolidatedHighLowLastIndicator.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/ParticipantOpenHighLowLastIndicator.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/SaleCondition.hpp"
#include "../enums/SaleConditionCategory.hpp"
#include "../messages/TradeMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_10 {

class TradeMessagePayloadVisitor;

// The Short Trade message is used to report trade information for Cta eligible Equity only
// (not used for Local Issues or Bonds) if the trade meets message format requirements
// otherwise Long Trade message is used.
class FractionalShortTradeMessage : public TradeMessagePayload {
  public:
    // The code that selects this message
    static constexpr TradeMessagePayloadCode message_type = TradeMessageType::FractionalShortTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 38;

    FractionalShortTradeMessage() = default;
    FractionalShortTradeMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol_short, SaleCondition sale_condition, SaleConditionCategory sale_condition_category, Decimal trade_price_short, Decimal fractional_trade_volume_short, PrimaryListingMarketParticipantId primary_listing_market_participant_id, ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator, ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator);

    // Participant Id: Participant or Processor that generated the message
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

    // Transaction Id: The Transaction Id will be populated by CQS and is Reserved for Internal
    // Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Participant Reference Number is a pass-thru of the inbound
    // Participant Reference number assigned to a transaction
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Security Symbol Short: Contains the security symbol
    const std::string& security_symbol_short() const;
    std::string& security_symbol_short();
    void set_security_symbol_short(const std::string& value);

    // Sale Condition: Denotes the sale condition associated with a trade
    SaleCondition sale_condition() const;
    void set_sale_condition(SaleCondition value);

    // Sale Condition Category: Identifies the Sale Condition Category level associated with a
    // trade
    SaleConditionCategory sale_condition_category() const;
    void set_sale_condition_category(SaleConditionCategory value);

    // Trade Price Short: The Trade Price is the monetary value of an individual share of
    // security at the time of the trade
    Decimal trade_price_short() const;
    void set_trade_price_short(Decimal value);

    // Fractional Trade Volume Short: The Fractional Trade Volume contains the total number of
    // shares which traded in a single transaction for an individual security.
    Decimal fractional_trade_volume_short() const;
    void set_fractional_trade_volume_short(Decimal value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market of the
    // security symbol
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Consolidated High Low Last Indicator: Identifies the Consolidated High/Low/Last Price
    // applicable to the trade.
    ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator() const;
    void set_consolidated_high_low_last_indicator(ConsolidatedHighLowLastIndicator value);

    // Participant Open High Low Last Indicator: Identifies the Participant Open/High/Low/Last
    // applicable to the transaction
    ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator() const;
    void set_participant_open_high_low_last_indicator(ParticipantOpenHighLowLastIndicator value);

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

    bool operator==(const FractionalShortTradeMessage& other) const;
    bool operator!=(const FractionalShortTradeMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_short_{};
    SaleCondition sale_condition_{};
    SaleConditionCategory sale_condition_category_{};
    Decimal trade_price_short_{ 0, -2 };
    Decimal fractional_trade_volume_short_{ 0, -6 };
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator_{};
    ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator_{};
};

} // namespace siac::cts::output::cta::v2_10
