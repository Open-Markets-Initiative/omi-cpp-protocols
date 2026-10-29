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
#include "../messages/Message.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

class Visitor;

// Sent when an order is executed
class OrderExecutedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 47;

    OrderExecutedMessage() = default;
    OrderExecutedMessage(std::chrono::nanoseconds timestamp, std::uint64_t order_id, Decimal quantity, std::uint64_t execution_id, Side side, Decimal price, const std::string& broker, const std::string& contra_broker);

    // Timestamp: Nanoseconds Since Epoch (UTC)
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Order Id: Market Issued Unique Order ID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Quantity: Quantity - 6 implied decimals
    Decimal quantity() const;
    void set_quantity(Decimal value);

    // Execution Id: Market Issued Unique Execution ID
    std::uint64_t execution_id() const;
    void set_execution_id(std::uint64_t value);

    // Side: Side of the order
    Side side() const;
    void set_side(Side value);

    // Price: Price - 6 implied decimals
    Decimal price() const;
    void set_price(Decimal value);

    // Broker: Three digit number Broker Number or 001 for anonymous
    const std::string& broker() const;
    std::string& broker();
    void set_broker(const std::string& value);

    // Contra Broker: Three digit number Broker Number of the contra order or 001 for anonymous
    const std::string& contra_broker() const;
    std::string& contra_broker();
    void set_contra_broker(const std::string& value);

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

    bool operator==(const OrderExecutedMessage& other) const;
    bool operator!=(const OrderExecutedMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t order_id_{};
    Decimal quantity_{ 0, -6 };
    std::uint64_t execution_id_{};
    Side side_{};
    Decimal price_{ 0, -6 };
    std::string broker_{};
    std::string contra_broker_{};
};

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
