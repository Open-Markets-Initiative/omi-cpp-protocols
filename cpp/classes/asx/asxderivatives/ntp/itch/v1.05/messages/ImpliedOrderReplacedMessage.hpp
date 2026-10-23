#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// This message notifies the subscriber that an existing implied order is to be replaced when
// the implied price, volume or priority has changed due to a price or volume movement of
// “real” orders for a side of a single Tradeable Instrument Id
class ImpliedOrderReplacedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ImpliedOrderReplacedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    ImpliedOrderReplacedMessage() = default;
    ImpliedOrderReplacedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Side side, std::uint64_t order_id, std::uint64_t order_book_priority, std::uint32_t quantity, Decimal price);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tradeable Instrument Id: Identifier of the Order Book.
    std::uint32_t tradeable_instrument_id() const;
    void set_tradeable_instrument_id(std::uint32_t value);

    // Side: Type of order
    Side side() const;
    void set_side(Side value);

    // Order Id: Public order id of the order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Order Book Priority: Time priority of this order within the order book.
    std::uint64_t order_book_priority() const;
    void set_order_book_priority(std::uint64_t value);

    // Quantity: Number of lots added to the book (all volume is visible).
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Price: Price of the order.
    Decimal price() const;
    void set_price(Decimal value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const ImpliedOrderReplacedMessage& other) const;
    bool operator!=(const ImpliedOrderReplacedMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    Side side_{};
    std::uint64_t order_id_{};
    std::uint64_t order_book_priority_{};
    std::uint32_t quantity_{};
    Decimal price_{ 0, -2 };
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
