#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/BboIndicator.hpp"
#include "../enums/PremiumPriceDenominatorCode.hpp"
#include "../enums/StrikePriceDenominatorCode.hpp"
#include "../messages/LongEquityAndIndexQuoteMessagePayload.hpp"
#include "../structs/BestBidAndOfferAppendage.hpp"
#include "../structs/BestBidAppendage.hpp"
#include "../structs/BestOfferAppendage.hpp"
#include "../structs/ExpirationBlock.hpp"

namespace siac::opra::output::obi::v6_2 {

class LongEquityAndIndexQuoteMessagePayloadVisitor;

// Long Equity and Index Quote Message
class LongEquityAndIndexQuoteMessage : public LongEquityAndIndexQuoteMessagePayload {
  public:
    // The code that selects this message
    static constexpr LongEquityAndIndexQuoteMessagePayloadCode message_type = LongEquityAndIndexQuoteMessageType::RegularTrading;

    LongEquityAndIndexQuoteMessage() = default;
    LongEquityAndIndexQuoteMessage(BboIndicator bbo_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, const ExpirationBlock& expiration_block, StrikePriceDenominatorCode strike_price_denominator_code, Decimal strike_price, PremiumPriceDenominatorCode premium_price_denominator_code, std::int32_t bid_price, std::uint32_t bid_size, std::int32_t offer_price, std::uint32_t offer_size, const std::optional<BestBidAppendage>& best_bid_appendage, const std::optional<BestOfferAppendage>& best_offer_appendage, const std::optional<BestBidAndOfferAppendage>& best_bid_and_offer_appendage);

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

    // Security Symbol: Identifies the unique symbol assigned to the underlying security.
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Reserved 1: One reserved byte
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Expiration Block: Expiration Block
    const ExpirationBlock& expiration_block() const;
    ExpirationBlock& expiration_block();
    void set_expiration_block(const ExpirationBlock& value);

    // Strike Price Denominator Code: The Strike Price Denominator Code field indicates the
    // position of the floating decimal point within the Strike Price field.
    StrikePriceDenominatorCode strike_price_denominator_code() const;
    void set_strike_price_denominator_code(StrikePriceDenominatorCode value);

    // Strike Price: Represents the stated price per share for which the underlying security
    // may be purchased (in the case of a call) or sold (in the case of a put) by the option
    // holder upon exercise of the option contract.
    Decimal strike_price() const;
    void set_strike_price(Decimal value);
    // the exponent strike_price_denominator_code states, or 0 for a code it does not state
    static int strike_price_exponent(char code);

    // Premium Price Denominator Code: Represents the first price paid for an option during the
    // trading day.
    PremiumPriceDenominatorCode premium_price_denominator_code() const;
    void set_premium_price_denominator_code(PremiumPriceDenominatorCode value);

    // Bid Price: Represents the price at which a buyer is willing to buy an option.
    std::int32_t bid_price() const;
    void set_bid_price(std::int32_t value);

    // Bid Size: The Bid Size identifies the number of contracts being bought for an option at
    // the Bid Price.
    std::uint32_t bid_size() const;
    void set_bid_size(std::uint32_t value);

    // Offer Price: Represents the price at which a seller is offering to sell an option.
    std::int32_t offer_price() const;
    void set_offer_price(std::int32_t value);

    // Offer Size: The Offer Size identifies the number of contracts for sale for an option at
    // the Offer Price.
    std::uint32_t offer_size() const;
    void set_offer_size(std::uint32_t value);

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

    // LongEquityAndIndexQuoteMessagePayload
    LongEquityAndIndexQuoteMessagePayloadCode type() const override;
    void set_type(LongEquityAndIndexQuoteMessagePayloadCode value);
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(LongEquityAndIndexQuoteMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<LongEquityAndIndexQuoteMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const LongEquityAndIndexQuoteMessagePayload& other) const override;

    bool operator==(const LongEquityAndIndexQuoteMessage& other) const;
    bool operator!=(const LongEquityAndIndexQuoteMessage& other) const;

  private:
    BboIndicator bbo_indicator_{};
    std::uint32_t transaction_id_{};
    std::uint32_t participant_reference_number_{};
    std::string security_symbol_{};
    std::array<std::byte, 1> reserved_1_{};
    ExpirationBlock expiration_block_{};
    StrikePriceDenominatorCode strike_price_denominator_code_{};
    Decimal strike_price_{};
    PremiumPriceDenominatorCode premium_price_denominator_code_{};
    std::int32_t bid_price_{};
    std::uint32_t bid_size_{};
    std::int32_t offer_price_{};
    std::uint32_t offer_size_{};
    std::optional<BestBidAppendage> best_bid_appendage_{};
    std::optional<BestOfferAppendage> best_offer_appendage_{};
    std::optional<BestBidAndOfferAppendage> best_bid_and_offer_appendage_{};
    // The code it was read with, of the codes selecting it
    LongEquityAndIndexQuoteMessagePayloadCode type_ = message_type;
};

} // namespace siac::opra::output::obi::v6_2
