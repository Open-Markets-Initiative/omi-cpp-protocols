#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/BboIndicator.hpp"
#include "../messages/ShortEquityAndIndexQuoteMessagePayload.hpp"
#include "../structs/BestBidAndOfferAppendage.hpp"
#include "../structs/BestBidAppendage.hpp"
#include "../structs/BestOfferAppendage.hpp"
#include "../structs/ExpirationBlock.hpp"

namespace siac::opra::output::obi::v6_2 {

class ShortEquityAndIndexQuoteMessagePayloadVisitor;

// Short Equity and Index Quote Message
class ShortEquityAndIndexQuoteMessage : public ShortEquityAndIndexQuoteMessagePayload {
  public:
    // The code that selects this message
    static constexpr ShortEquityAndIndexQuoteMessagePayloadCode message_type = ShortEquityAndIndexQuoteMessageType::RegularTrading;

    ShortEquityAndIndexQuoteMessage() = default;
    ShortEquityAndIndexQuoteMessage(BboIndicator bbo_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol_short, const ExpirationBlock& expiration_block, Decimal strike_price_short, Decimal bid_price_short, std::uint16_t bid_size_short, Decimal offer_price_short, std::uint16_t offer_size_short, const std::optional<BestBidAppendage>& best_bid_appendage, const std::optional<BestOfferAppendage>& best_offer_appendage, const std::optional<BestBidAndOfferAppendage>& best_bid_and_offer_appendage);

    // Bbo Indicator: Indicates the effect the new quote has on the Best Bid and/or the Best
    // Offer.
    BboIndicator bbo_indicator() const;
    void set_bbo_indicator(BboIndicator value);

    // Transaction Id: Reserved for Internal Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: The PRN is for optional use by the Participant
    std::uint32_t participant_reference_number() const;
    void set_participant_reference_number(std::uint32_t value);

    // Security Symbol Short: Identifies the unique symbol assigned to the underlying security.
    const std::string& security_symbol_short() const;
    std::string& security_symbol_short();
    void set_security_symbol_short(const std::string& value);

    // Expiration Block: Expiration Block
    const ExpirationBlock& expiration_block() const;
    ExpirationBlock& expiration_block();
    void set_expiration_block(const ExpirationBlock& value);

    // Strike Price Short: Represents the stated price per share for which the underlying
    // security may be purchased (in the case of a call) or sold (in the case of a put) by the
    // option holder upon exercise of the option contract.
    Decimal strike_price_short() const;
    void set_strike_price_short(Decimal value);

    // Bid Price Short: Represents the price at which a buyer is willing to buy an option.
    Decimal bid_price_short() const;
    void set_bid_price_short(Decimal value);

    // Bid Size Short: The Bid Size identifies the number of contracts being bought for an
    // option at the Bid Price.
    std::uint16_t bid_size_short() const;
    void set_bid_size_short(std::uint16_t value);

    // Offer Price Short: Represents the price at which a seller is offering to sell an option.
    Decimal offer_price_short() const;
    void set_offer_price_short(Decimal value);

    // Offer Size Short: The Offer Size identifies the number of contracts for sale for an
    // option at the Offer Price.
    std::uint16_t offer_size_short() const;
    void set_offer_size_short(std::uint16_t value);

    // Best Bid Appendage: Best Bid Appendage
    const std::optional<BestBidAppendage>& best_bid_appendage() const;
    std::optional<BestBidAppendage>& best_bid_appendage();
    void set_best_bid_appendage(const std::optional<BestBidAppendage>& value);

    // Best Offer Appendage: Best Offer Appendage
    const std::optional<BestOfferAppendage>& best_offer_appendage() const;
    std::optional<BestOfferAppendage>& best_offer_appendage();
    void set_best_offer_appendage(const std::optional<BestOfferAppendage>& value);

    // Best Bid And Offer Appendage: Best Bid and Offer Appendage
    const std::optional<BestBidAndOfferAppendage>& best_bid_and_offer_appendage() const;
    std::optional<BestBidAndOfferAppendage>& best_bid_and_offer_appendage();
    void set_best_bid_and_offer_appendage(const std::optional<BestBidAndOfferAppendage>& value);

    // ShortEquityAndIndexQuoteMessagePayload
    ShortEquityAndIndexQuoteMessagePayloadCode type() const override;
    void set_type(ShortEquityAndIndexQuoteMessagePayloadCode value);
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ShortEquityAndIndexQuoteMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<ShortEquityAndIndexQuoteMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ShortEquityAndIndexQuoteMessagePayload& other) const override;

    bool operator==(const ShortEquityAndIndexQuoteMessage& other) const;
    bool operator!=(const ShortEquityAndIndexQuoteMessage& other) const;

  private:
    BboIndicator bbo_indicator_{};
    std::uint32_t transaction_id_{};
    std::uint32_t participant_reference_number_{};
    std::string security_symbol_short_{};
    ExpirationBlock expiration_block_{};
    Decimal strike_price_short_{ 0, -1 };
    Decimal bid_price_short_{ 0, -2 };
    std::uint16_t bid_size_short_{};
    Decimal offer_price_short_{ 0, -2 };
    std::uint16_t offer_size_short_{};
    std::optional<BestBidAppendage> best_bid_appendage_{};
    std::optional<BestOfferAppendage> best_offer_appendage_{};
    std::optional<BestBidAndOfferAppendage> best_bid_and_offer_appendage_{};
    // The code it was read with, of the codes selecting it
    ShortEquityAndIndexQuoteMessagePayloadCode type_ = message_type;
};

} // namespace siac::opra::output::obi::v6_2
