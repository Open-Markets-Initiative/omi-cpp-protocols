#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/QuoteCondition.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

class SequencedMessageVisitor;

// Whenever the best bid and ask position changes on both sides, the options system will send
// its best bid and ask update via the data feed for the affected security.
class ShortBestBidAndAskUpdateMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::ShortBestBidAndAskUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    ShortBestBidAndAskUpdateMessage() = default;
    ShortBestBidAndAskUpdateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, QuoteCondition quote_condition, Decimal bid_price_2, std::uint16_t bid_size_2, Decimal ask_price_2, std::uint16_t ask_size_2);

    // Nanoseconds: The sub-second portion of the time, in nanoseconds (0-999999999). The
    // second portion of the time is obtained from the most recent timestamp message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Option Id: Option ID for this option, assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Quote Condition: Quote Condition value
    QuoteCondition quote_condition() const;
    void set_quote_condition(QuoteCondition value);

    // Bid Price 2: Best bid price. NOTE: When converted to a decimal format, the price is in
    // fixed point format with 3 whole number places followed by 2 decimal digits.
    Decimal bid_price_2() const;
    void set_bid_price_2(Decimal value);

    // Bid Size 2: Aggregated number of contracts on the bid side being displayed in the
    // options market at the current time.
    std::uint16_t bid_size_2() const;
    void set_bid_size_2(std::uint16_t value);

    // Ask Price 2: Best ask price. NOTE: When converted to a decimal format, the price is in
    // fixed point format with 3 whole number places followed by 2 decimal digits.
    Decimal ask_price_2() const;
    void set_ask_price_2(Decimal value);

    // Ask Size 2: Aggregated number of contracts on the ask side being displayed in the
    // options market at the current time.
    std::uint16_t ask_size_2() const;
    void set_ask_size_2(std::uint16_t value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const ShortBestBidAndAskUpdateMessage& other) const;
    bool operator!=(const ShortBestBidAndAskUpdateMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t option_id_{};
    QuoteCondition quote_condition_{};
    Decimal bid_price_2_{ 0, -2 };
    std::uint16_t bid_size_2_{};
    Decimal ask_price_2_{ 0, -2 };
    std::uint16_t ask_size_2_{};
};

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
