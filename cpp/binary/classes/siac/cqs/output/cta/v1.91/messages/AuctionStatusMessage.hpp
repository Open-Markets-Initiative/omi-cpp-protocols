#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../messages/QuoteMessagePayload.hpp"
#include "../structs/ParticipantTimestamp.hpp"

namespace siac::cqs::output::cta::v1_91 {

class QuoteMessagePayloadVisitor;

// The Auction Status message is used when a Participant in a Cta eligible security
class AuctionStatusMessage : public QuoteMessagePayload {
  public:
    // The code that selects this message
    static constexpr QuoteMessagePayloadCode message_type = QuoteMessageType::AuctionStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 63;

    AuctionStatusMessage() = default;
    AuctionStatusMessage(ParticipantId participant_id, const ParticipantTimestamp& participant_timestamp, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol_long, InstrumentType instrument_type, std::optional<Decimal> auction_collar_reference_price, std::optional<Decimal> auction_collar_upper_threshold_price, std::optional<Decimal> auction_collar_lower_threshold_price, std::uint8_t number_of_extensions, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, char future);

    // Participant Id: Participant or Processor that generated the message
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Participant Timestamp: Participant Timestamp
    const ParticipantTimestamp& participant_timestamp() const;
    ParticipantTimestamp& participant_timestamp();
    void set_participant_timestamp(const ParticipantTimestamp& value);

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

    // Security Symbol Long: Contains the security symbol
    const std::string& security_symbol_long() const;
    std::string& security_symbol_long();
    void set_security_symbol_long(const std::string& value);

    // Instrument Type: Identifies the instrument type relevant to the quote
    InstrumentType instrument_type() const;
    void set_instrument_type(InstrumentType value);

    // Auction Collar Reference Price: Price used by the exchange to establish the Auction
    // Collar
    std::optional<Decimal> auction_collar_reference_price() const;
    void set_auction_collar_reference_price(std::optional<Decimal> value);

    // Auction Collar Upper Threshold Price: Latest upper threshold price of the Auction Collar
    std::optional<Decimal> auction_collar_upper_threshold_price() const;
    void set_auction_collar_upper_threshold_price(std::optional<Decimal> value);

    // Auction Collar Lower Threshold Price: Latest lower threshold price of the Auction Collar
    std::optional<Decimal> auction_collar_lower_threshold_price() const;
    void set_auction_collar_lower_threshold_price(std::optional<Decimal> value);

    // Number Of Extensions: Identifies the number of manual or automatic extensions the
    // applicable auction has received
    std::uint8_t number_of_extensions() const;
    void set_number_of_extensions(std::uint8_t value);

    // Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is
    // in effect
    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const;
    void set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market for a
    // security
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Financial Status Indicator: Identifies the financial status of the security.
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Future: Field is reserved for future use.
    char future() const;
    void set_future(char value);

    // QuoteMessagePayload
    QuoteMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(QuoteMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<QuoteMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const QuoteMessagePayload& other) const override;

    bool operator==(const AuctionStatusMessage& other) const;
    bool operator!=(const AuctionStatusMessage& other) const;

  private:
    ParticipantId participant_id_{};
    ParticipantTimestamp participant_timestamp_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_long_{};
    InstrumentType instrument_type_{};
    std::optional<Decimal> auction_collar_reference_price_{};
    std::optional<Decimal> auction_collar_upper_threshold_price_{};
    std::optional<Decimal> auction_collar_lower_threshold_price_{};
    std::uint8_t number_of_extensions_{};
    ShortSaleRestrictionIndicator short_sale_restriction_indicator_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    FinancialStatusIndicator financial_status_indicator_{};
    char future_{};
};

} // namespace siac::cqs::output::cta::v1_91
