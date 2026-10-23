#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/PremiumPriceDenominatorCode.hpp"
#include "../enums/StrikePriceDenominatorCode.hpp"
#include "../enums/UnderlyingPriceDenominatorCode.hpp"
#include "../messages/EquityAndIndexEndOfDaySummaryMessagePayload.hpp"
#include "../structs/ExpirationBlock.hpp"

namespace siac::opra::output::obi::v6_2 {

class EquityAndIndexEndOfDaySummaryMessagePayloadVisitor;

// Equity and Index End of Day Summary Message
class EquityAndIndexEndOfDaySummaryMessage : public EquityAndIndexEndOfDaySummaryMessagePayload {
  public:
    // The code that selects this message
    static constexpr EquityAndIndexEndOfDaySummaryMessagePayloadCode message_type = EquityAndIndexEndOfDaySummaryMessageType::EquityAndIndexEndOfDaySummary;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 69;

    EquityAndIndexEndOfDaySummaryMessage() = default;
    EquityAndIndexEndOfDaySummaryMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, const ExpirationBlock& expiration_block, StrikePriceDenominatorCode strike_price_denominator_code, Decimal strike_price, std::uint32_t volume, std::uint32_t open_interest_volume, PremiumPriceDenominatorCode premium_price_denominator_code, std::int32_t open_price, std::int32_t high_price, std::int32_t low_price, std::int32_t last_price, std::int32_t net_change, UnderlyingPriceDenominatorCode underlying_price_denominator_code, Decimal underlying_price, std::int32_t bid_price, std::int32_t offer_price);

    // Message Indicator: Message identifier
    char message_indicator() const;
    void set_message_indicator(char value);

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

    // Volume: Represents the total number of contracts traded for an option in one trade, or
    // the total number of contracts traded for an option for the entire trading day.
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Open Interest Volume: Represents the total number of outstanding option contracts that
    // have not been exercised and have not yet reached expiration.
    std::uint32_t open_interest_volume() const;
    void set_open_interest_volume(std::uint32_t value);

    // Premium Price Denominator Code: Represents the first price paid for an option during the
    // trading day.
    PremiumPriceDenominatorCode premium_price_denominator_code() const;
    void set_premium_price_denominator_code(PremiumPriceDenominatorCode value);

    // Open Price: Represents the first price paid for an option during the trading day.
    std::int32_t open_price() const;
    void set_open_price(std::int32_t value);

    // High Price: Represents the highest price paid for an option during the trading day.
    std::int32_t high_price() const;
    void set_high_price(std::int32_t value);

    // Low Price: Represents the lowest price paid for an option during the trading day.
    std::int32_t low_price() const;
    void set_low_price(std::int32_t value);

    // Last Price: Represents the last price paid for an option during the trading day.
    std::int32_t last_price() const;
    void set_last_price(std::int32_t value);

    // Net Change: Represents the change in the price of an option from the closing price of
    // one day to the closing price on the next day on which the option is traded.
    std::int32_t net_change() const;
    void set_net_change(std::int32_t value);

    // Underlying Price Denominator Code: The Underlying Price Denominator Code field indicates
    // the position of the floating decimal point within the Underlying Price field.
    UnderlyingPriceDenominatorCode underlying_price_denominator_code() const;
    void set_underlying_price_denominator_code(UnderlyingPriceDenominatorCode value);

    // Underlying Price: Represents the price of the underlying security.
    Decimal underlying_price() const;
    void set_underlying_price(Decimal value);
    // the exponent underlying_price_denominator_code states, or 0 for a code it does not state
    static int underlying_price_exponent(char code);

    // Bid Price: Represents the price at which a buyer is willing to buy an option.
    std::int32_t bid_price() const;
    void set_bid_price(std::int32_t value);

    // Offer Price: Represents the price at which a seller is offering to sell an option.
    std::int32_t offer_price() const;
    void set_offer_price(std::int32_t value);

    // EquityAndIndexEndOfDaySummaryMessagePayload
    EquityAndIndexEndOfDaySummaryMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(EquityAndIndexEndOfDaySummaryMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<EquityAndIndexEndOfDaySummaryMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const EquityAndIndexEndOfDaySummaryMessagePayload& other) const override;

    bool operator==(const EquityAndIndexEndOfDaySummaryMessage& other) const;
    bool operator!=(const EquityAndIndexEndOfDaySummaryMessage& other) const;

  private:
    char message_indicator_{};
    std::uint32_t transaction_id_{};
    std::uint32_t participant_reference_number_{};
    std::string security_symbol_{};
    std::array<std::byte, 1> reserved_1_{};
    ExpirationBlock expiration_block_{};
    StrikePriceDenominatorCode strike_price_denominator_code_{};
    Decimal strike_price_{};
    std::uint32_t volume_{};
    std::uint32_t open_interest_volume_{};
    PremiumPriceDenominatorCode premium_price_denominator_code_{};
    std::int32_t open_price_{};
    std::int32_t high_price_{};
    std::int32_t low_price_{};
    std::int32_t last_price_{};
    std::int32_t net_change_{};
    UnderlyingPriceDenominatorCode underlying_price_denominator_code_{};
    Decimal underlying_price_{};
    std::int32_t bid_price_{};
    std::int32_t offer_price_{};
};

} // namespace siac::opra::output::obi::v6_2
