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
#include "../enums/SaleCondition1.hpp"
#include "../enums/SaleConditionCategory.hpp"
#include "../messages/TradeMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_11_b {

class TradeMessagePayloadVisitor;

// Used to report trade information for CTA eligible Equity only. To be descoped when
// Fractional Trade Volume publication is activated
class ShortTradeMessage : public TradeMessagePayload {
  public:
    // The code that selects this message
    static constexpr TradeMessagePayloadCode message_type = TradeMessageType::ShortTrade;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    ShortTradeMessage() = default;
    ShortTradeMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol_5, SaleCondition1 sale_condition_1, SaleConditionCategory sale_condition_category, Decimal trade_price_2, std::uint16_t trade_volume_2, PrimaryListingMarketParticipantId primary_listing_market_participant_id, ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator, ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator);

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

    // Security Symbol 5: Identifies the Security Symbol. Left justified, space-filled
    const std::string& security_symbol_5() const;
    std::string& security_symbol_5();
    void set_security_symbol_5(const std::string& value);

    // Sale Condition 1: Denotes the sale condition associated with a trade
    SaleCondition1 sale_condition_1() const;
    void set_sale_condition_1(SaleCondition1 value);

    // Sale Condition Category: In the Short Trade format, identifies the Sale Condition
    // Category level associated with a trade
    SaleConditionCategory sale_condition_category() const;
    void set_sale_condition_category(SaleConditionCategory value);

    // Trade Price 2: Represents the monetary value of an individual share of security at the
    // time of the trade. Has implied 2 decimal places
    Decimal trade_price_2() const;
    void set_trade_price_2(Decimal value);

    // Trade Volume 2: Contains the total number of shares traded in a single transaction for
    // an individual security (short form)
    std::uint16_t trade_volume_2() const;
    void set_trade_volume_2(std::uint16_t value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market of the
    // security symbol
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Consolidated High Low Last Indicator: Identifies the Consolidated High/Low/Last Price
    // applicable to the trade
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

    bool operator==(const ShortTradeMessage& other) const;
    bool operator!=(const ShortTradeMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_5_{};
    SaleCondition1 sale_condition_1_{};
    SaleConditionCategory sale_condition_category_{};
    Decimal trade_price_2_{ 0, -2 };
    std::uint16_t trade_volume_2_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator_{};
    ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator_{};
};

} // namespace siac::cts::output::cta::v2_11_b
