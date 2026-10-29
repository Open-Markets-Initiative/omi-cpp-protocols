#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class SequencedMessageVisitor;

// This message will be generated for unattributed orders accepted by the NASDAQ system.
class AddOrderMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = 'A';
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 27;

    AddOrderMessage() = default;
    AddOrderMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number, Side side, std::uint32_t shares, const std::string& stock, Decimal price);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Reference Number: The unique reference number assigned to the new order at the
    // time of receipt.
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Side: The type of order being added.
    Side side() const;
    void set_side(Side value);

    // Shares: The total number of shares associated with the order being added to the book.
    std::uint32_t shares() const;
    void set_shares(std::uint32_t value);

    // Stock: Denotes the security symbol for the issue in NASDAQ Single Book. Refer to
    // Appendix NASDAQ Single Book stock symbol convention information.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

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

    bool operator==(const AddOrderMessage& other) const;
    bool operator!=(const AddOrderMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t order_reference_number_{};
    Side side_{};
    std::uint32_t shares_{};
    std::string stock_{};
    Decimal price_{ 0, -4 };
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
