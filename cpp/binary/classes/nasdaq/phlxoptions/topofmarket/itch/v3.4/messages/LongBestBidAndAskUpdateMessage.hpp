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

// This message is the same as the Best Bid AND Ask Update Message – Short Form described above
// except that Prices and Sizes are 4 byte Integers, the prices having 4 implied decimal
// places.
class LongBestBidAndAskUpdateMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::LongBestBidAndAskUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    LongBestBidAndAskUpdateMessage() = default;
    LongBestBidAndAskUpdateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, QuoteCondition quote_condition, Decimal bid_price_4, std::uint32_t bid_size_4, Decimal ask_price_4, std::uint32_t ask_size_4);

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

    // Bid Price 4: Best bid price.
    Decimal bid_price_4() const;
    void set_bid_price_4(Decimal value);

    // Bid Size 4: Aggregated number of contracts on the bid side being displayed in the
    // options market at the current time.
    std::uint32_t bid_size_4() const;
    void set_bid_size_4(std::uint32_t value);

    // Ask Price 4: Best ask price.
    Decimal ask_price_4() const;
    void set_ask_price_4(Decimal value);

    // Ask Size 4: Aggregated number of contracts on the ask side being displayed in the
    // options market at the current time.
    std::uint32_t ask_size_4() const;
    void set_ask_size_4(std::uint32_t value);

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

    bool operator==(const LongBestBidAndAskUpdateMessage& other) const;
    bool operator!=(const LongBestBidAndAskUpdateMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t option_id_{};
    QuoteCondition quote_condition_{};
    Decimal bid_price_4_{ 0, -4 };
    std::uint32_t bid_size_4_{};
    Decimal ask_price_4_{ 0, -4 };
    std::uint32_t ask_size_4_{};
};

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
