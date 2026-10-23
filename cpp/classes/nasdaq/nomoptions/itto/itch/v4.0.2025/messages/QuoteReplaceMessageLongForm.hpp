#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class SequencedMessageVisitor;

// This message is sent whenever a quote on the book is replaced. The replaced quote has new
// sequence numbers on both sides. These new sequence numbers replace the prior sequence
// numbers on the quote.
class QuoteReplaceMessageLongForm : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::QuoteReplaceMessageLongForm;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 56;

    QuoteReplaceMessageLongForm() = default;
    QuoteReplaceMessageLongForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t original_bid_reference_number, std::uint64_t bid_reference_number, std::uint64_t original_ask_reference_number, std::uint64_t ask_reference_number, Decimal bid_price_long, std::uint32_t bid_size_long, Decimal ask_price_long, std::uint32_t ask_size_long);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Original Bid Reference Number: The original bid reference number that is replaced
    std::uint64_t original_bid_reference_number() const;
    void set_original_bid_reference_number(std::uint64_t value);

    // Bid Reference Number: The bid reference number associated with the new quote.
    std::uint64_t bid_reference_number() const;
    void set_bid_reference_number(std::uint64_t value);

    // Original Ask Reference Number: The original ask reference number that is replaced
    std::uint64_t original_ask_reference_number() const;
    void set_original_ask_reference_number(std::uint64_t value);

    // Ask Reference Number: The ask reference number associated with the new quote
    std::uint64_t ask_reference_number() const;
    void set_ask_reference_number(std::uint64_t value);

    // Bid Price Long: The display bid price of the replaced quote.
    Decimal bid_price_long() const;
    void set_bid_price_long(Decimal value);

    // Bid Size Long: The bid contracts of the new quote.
    std::uint32_t bid_size_long() const;
    void set_bid_size_long(std::uint32_t value);

    // Ask Price Long: The display ask price of the replaced quote.
    Decimal ask_price_long() const;
    void set_ask_price_long(Decimal value);

    // Ask Size Long: The ask contracts of the new quote.
    std::uint32_t ask_size_long() const;
    void set_ask_size_long(std::uint32_t value);

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

    bool operator==(const QuoteReplaceMessageLongForm& other) const;
    bool operator!=(const QuoteReplaceMessageLongForm& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t original_bid_reference_number_{};
    std::uint64_t bid_reference_number_{};
    std::uint64_t original_ask_reference_number_{};
    std::uint64_t ask_reference_number_{};
    Decimal bid_price_long_{ 0, -4 };
    std::uint32_t bid_size_long_{};
    Decimal ask_price_long_{ 0, -4 };
    std::uint32_t ask_size_long_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
