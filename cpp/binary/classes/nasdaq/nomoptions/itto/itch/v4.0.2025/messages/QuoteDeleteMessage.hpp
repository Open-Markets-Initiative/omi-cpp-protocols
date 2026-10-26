#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class SequencedMessageVisitor;

// The message is sent when a single quote is being cancelled. All remaining contracts are no
// longer accessible so the quote should be removed from the book.
class QuoteDeleteMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::QuoteDeleteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    QuoteDeleteMessage() = default;
    QuoteDeleteMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t bid_reference_number, std::uint64_t ask_reference_number);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Bid Reference Number: The bid reference number associated with the new quote.
    std::uint64_t bid_reference_number() const;
    void set_bid_reference_number(std::uint64_t value);

    // Ask Reference Number: The ask reference number associated with the new quote
    std::uint64_t ask_reference_number() const;
    void set_ask_reference_number(std::uint64_t value);

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

    bool operator==(const QuoteDeleteMessage& other) const;
    bool operator!=(const QuoteDeleteMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t bid_reference_number_{};
    std::uint64_t ask_reference_number_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
