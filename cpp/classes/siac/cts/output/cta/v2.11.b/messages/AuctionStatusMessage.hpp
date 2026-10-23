#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../messages/TradeMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_11_b {

class TradeMessagePayloadVisitor;

// Used when a Participant in a CTA eligible security, Local Issue or a Bond requires Auction
// Information
class AuctionStatusMessage : public TradeMessagePayload {
  public:
    // The code that selects this message
    static constexpr TradeMessagePayloadCode message_type = TradeMessageType::AuctionStatus;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 124;

    AuctionStatusMessage() = default;
    AuctionStatusMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, Decimal auction_collar_reference_price, Decimal auction_collar_upper_threshold_price, Decimal auction_collar_lower_threshold_price, std::uint8_t number_of_extensions, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, const std::string& reserved_62);

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

    // Auction Collar Reference Price: Represents the price used by the exchange to establish
    // the Auction Collar. Has implied 6 decimal places
    Decimal auction_collar_reference_price() const;
    void set_auction_collar_reference_price(Decimal value);

    // Auction Collar Upper Threshold Price: Represents the latest upper threshold price of the
    // Auction Collar. Has implied 6 decimal places
    Decimal auction_collar_upper_threshold_price() const;
    void set_auction_collar_upper_threshold_price(Decimal value);

    // Auction Collar Lower Threshold Price: Represents the latest lower threshold price of the
    // Auction Collar. Has implied 6 decimal places
    Decimal auction_collar_lower_threshold_price() const;
    void set_auction_collar_lower_threshold_price(Decimal value);

    // Number Of Extensions: Identifies the number of manual or automatic extensions the
    // applicable auction has received
    std::uint8_t number_of_extensions() const;
    void set_number_of_extensions(std::uint8_t value);

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

    // Reserved 62: Space-filled. Field is reserved for future use
    const std::string& reserved_62() const;
    std::string& reserved_62();
    void set_reserved_62(const std::string& value);

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

    bool operator==(const AuctionStatusMessage& other) const;
    bool operator!=(const AuctionStatusMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    Decimal auction_collar_reference_price_{ 0, -6 };
    Decimal auction_collar_upper_threshold_price_{ 0, -6 };
    Decimal auction_collar_lower_threshold_price_{ 0, -6 };
    std::uint8_t number_of_extensions_{};
    ShortSaleRestrictionIndicator short_sale_restriction_indicator_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    FinancialStatusIndicator financial_status_indicator_{};
    std::string reserved_62_{};
};

} // namespace siac::cts::output::cta::v2_11_b
