#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class SequencedMessageVisitor;

// This message is sent whenever an order on the book has been cancel-replaced. All remaining
// shares from the original order are no longer accessible, and must be removed. The new order
// details are provided for the replacement, along with a new order reference number which will
// be used henceforth.
class OrderReplaceMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = 'U';
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    OrderReplaceMessage() = default;
    OrderReplaceMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t original_order_reference_number, std::uint64_t new_order_reference_number, std::uint32_t shares, Decimal price);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Original Order Reference Number: The original reference number of the order being
    // replaced.
    std::uint64_t original_order_reference_number() const;
    void set_original_order_reference_number(std::uint64_t value);

    // New Order Reference Number: The new reference number for this order at time of
    // replacement. Please note that the NASDAQ system will use this new order reference number
    // for all subsequent updates.
    std::uint64_t new_order_reference_number() const;
    void set_new_order_reference_number(std::uint64_t value);

    // Shares: The total number of shares associated with the order being added to the book.
    std::uint32_t shares() const;
    void set_shares(std::uint32_t value);

    // Price: The display price of the new order. Refer to Data Types for field processing
    // notes.
    Decimal price() const;
    void set_price(Decimal value);

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

    bool operator==(const OrderReplaceMessage& other) const;
    bool operator!=(const OrderReplaceMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t original_order_reference_number_{};
    std::uint64_t new_order_reference_number_{};
    std::uint32_t shares_{};
    Decimal price_{ 0, -4 };
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
