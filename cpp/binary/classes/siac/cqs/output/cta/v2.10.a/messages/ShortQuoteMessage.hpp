#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/NationalBboIndicator.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../messages/QuoteMessagePayload.hpp"
#include "../structs/NationalBestBidAndOfferLongAppendage.hpp"
#include "../structs/NationalBestBidAndOfferShortAppendage.hpp"
#include "../structs/NationalBestBidLongAppendage.hpp"
#include "../structs/NationalBestBidShortAppendage.hpp"
#include "../structs/NationalBestOfferLongAppendage.hpp"
#include "../structs/NationalBestOfferShortAppendage.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cqs::output::cta::v2_10_a {

class QuoteMessagePayloadVisitor;

// Reports Bid and Offer quote information for CTA eligible Equity only if the quote meets all
// criteria and message format requirements
class ShortQuoteMessage : public QuoteMessagePayload {
  public:
    // The code that selects this message
    static constexpr QuoteMessagePayloadCode message_type = QuoteMessageType::ShortQuote;

    ShortQuoteMessage() = default;
    ShortQuoteMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, Decimal bid_price_short, std::uint16_t bid_size_short, Decimal offer_price_short, std::uint16_t offer_size_short, PrimaryListingMarketParticipantId primary_listing_market_participant_id, NationalBboIndicator national_bbo_indicator, const std::optional<NationalBestBidLongAppendage>& national_best_bid_long_appendage, const std::optional<NationalBestOfferLongAppendage>& national_best_offer_long_appendage, const std::optional<NationalBestBidAndOfferLongAppendage>& national_best_bid_and_offer_long_appendage, const std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage, const std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage, const std::optional<NationalBestBidAndOfferShortAppendage>& national_best_bid_and_offer_short_appendage);

    // Participant Id: Identifies the Participant or Processor that generated the message
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

    // Transaction Id: The Transaction ID will be populated by CQS and is Reserved for Internal
    // Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Participant Reference Number is a pass-thru of the inbound
    // Participant Reference number assigned to a transaction
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Security Symbol: Contains the security symbol. Left justified, space-filled
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Bid Price Short: Represents the highest price a prospective buyer is prepared to pay at
    // a particular time for a security. Has implied 2 decimal places
    Decimal bid_price_short() const;
    void set_bid_price_short(Decimal value);

    // Bid Size Short: Identifies the number of shares for a symbol rounded down to the nearest
    // multiple of its Round Lot Size
    std::uint16_t bid_size_short() const;
    void set_bid_size_short(std::uint16_t value);

    // Offer Price Short: Represents the lowest price acceptable to a prospective seller at a
    // particular time for a security. Has implied 2 decimal places
    Decimal offer_price_short() const;
    void set_offer_price_short(Decimal value);

    // Offer Size Short: Identifies the number of shares for a symbol rounded down to the
    // nearest multiple of its Round Lot Size
    std::uint16_t offer_size_short() const;
    void set_offer_size_short(std::uint16_t value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market for a
    // security
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // National Bbo Indicator: Indicates the effect the new quote has on the National BBO
    NationalBboIndicator national_bbo_indicator() const;
    void set_national_bbo_indicator(NationalBboIndicator value);

    // National Best Bid Long Appendage: National Best Bid Long Appendage
    const std::optional<NationalBestBidLongAppendage>& national_best_bid_long_appendage() const;
    std::optional<NationalBestBidLongAppendage>& national_best_bid_long_appendage();
    void set_national_best_bid_long_appendage(const std::optional<NationalBestBidLongAppendage>& value);

    // National Best Offer Long Appendage: National Best Offer Long Appendage
    const std::optional<NationalBestOfferLongAppendage>& national_best_offer_long_appendage() const;
    std::optional<NationalBestOfferLongAppendage>& national_best_offer_long_appendage();
    void set_national_best_offer_long_appendage(const std::optional<NationalBestOfferLongAppendage>& value);

    // National Best Bid And Offer Long Appendage: National Best Bid And Offer Long Appendage
    const std::optional<NationalBestBidAndOfferLongAppendage>& national_best_bid_and_offer_long_appendage() const;
    std::optional<NationalBestBidAndOfferLongAppendage>& national_best_bid_and_offer_long_appendage();
    void set_national_best_bid_and_offer_long_appendage(const std::optional<NationalBestBidAndOfferLongAppendage>& value);

    // National Best Bid Short Appendage: National Best Bid Short Appendage
    const std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage() const;
    std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage();
    void set_national_best_bid_short_appendage(const std::optional<NationalBestBidShortAppendage>& value);

    // National Best Offer Short Appendage: National Best Offer Short Appendage
    const std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage() const;
    std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage();
    void set_national_best_offer_short_appendage(const std::optional<NationalBestOfferShortAppendage>& value);

    // National Best Bid And Offer Short Appendage: National Best Bid And Offer Short Appendage
    const std::optional<NationalBestBidAndOfferShortAppendage>& national_best_bid_and_offer_short_appendage() const;
    std::optional<NationalBestBidAndOfferShortAppendage>& national_best_bid_and_offer_short_appendage();
    void set_national_best_bid_and_offer_short_appendage(const std::optional<NationalBestBidAndOfferShortAppendage>& value);

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

    bool operator==(const ShortQuoteMessage& other) const;
    bool operator!=(const ShortQuoteMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    Decimal bid_price_short_{ 0, -2 };
    std::uint16_t bid_size_short_{};
    Decimal offer_price_short_{ 0, -2 };
    std::uint16_t offer_size_short_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    NationalBboIndicator national_bbo_indicator_{};
    std::optional<NationalBestBidLongAppendage> national_best_bid_long_appendage_{};
    std::optional<NationalBestOfferLongAppendage> national_best_offer_long_appendage_{};
    std::optional<NationalBestBidAndOfferLongAppendage> national_best_bid_and_offer_long_appendage_{};
    std::optional<NationalBestBidShortAppendage> national_best_bid_short_appendage_{};
    std::optional<NationalBestOfferShortAppendage> national_best_offer_short_appendage_{};
    std::optional<NationalBestBidAndOfferShortAppendage> national_best_bid_and_offer_short_appendage_{};
};

} // namespace siac::cqs::output::cta::v2_10_a
