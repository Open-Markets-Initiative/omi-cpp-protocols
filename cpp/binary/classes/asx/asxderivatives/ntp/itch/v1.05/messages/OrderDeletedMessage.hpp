#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// This message is sent whenever an order in the book is cancelled by the owner, expired,
// cancelled by the exchange, purged or volume cancelled
class OrderDeletedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderDeletedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 19;

    OrderDeletedMessage() = default;
    OrderDeletedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Side side, std::uint64_t order_id);

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

    bool operator==(const OrderDeletedMessage& other) const;
    bool operator!=(const OrderDeletedMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    Side side_{};
    std::uint64_t order_id_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
