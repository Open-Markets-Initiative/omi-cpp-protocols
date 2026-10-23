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

// This message is sent whenever an order or one side of a quote on the book is replaced. The
// replacement has a new sequence number and replaces the prior sequence number.
class SingleSideReplaceMessageLongForm : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::SingleSideReplaceMessageLongForm;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    SingleSideReplaceMessageLongForm() = default;
    SingleSideReplaceMessageLongForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t original_reference_number, std::uint64_t new_reference_number, Decimal price_long, std::uint32_t volume_long);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Original Reference Number: The original reference number associated with the order being
    // replaced.
    std::uint64_t original_reference_number() const;
    void set_original_reference_number(std::uint64_t value);

    // New Reference Number: The new reference number associated with the new order.
    std::uint64_t new_reference_number() const;
    void set_new_reference_number(std::uint64_t value);

    // Price Long: The display price of the new order being added to the book.
    Decimal price_long() const;
    void set_price_long(Decimal value);

    // Volume Long: The total number of contracts of the new order being added to the book.
    std::uint32_t volume_long() const;
    void set_volume_long(std::uint32_t value);

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

    bool operator==(const SingleSideReplaceMessageLongForm& other) const;
    bool operator!=(const SingleSideReplaceMessageLongForm& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t original_reference_number_{};
    std::uint64_t new_reference_number_{};
    Decimal price_long_{ 0, -4 };
    std::uint32_t volume_long_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
