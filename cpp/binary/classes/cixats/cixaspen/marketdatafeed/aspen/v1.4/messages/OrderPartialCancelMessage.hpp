#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

class Visitor;

// Part of a resting order is canceled
class OrderPartialCancelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderPartialCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    OrderPartialCancelMessage() = default;
    OrderPartialCancelMessage(std::chrono::nanoseconds timestamp, std::uint64_t order_id, Decimal quantity_canceled);

    // Timestamp: Nanoseconds Since Epoch (UTC)
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Order Id: Market Issued Unique Order ID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Quantity Canceled: Quantity canceled - Quantity 6 implied decimals
    Decimal quantity_canceled() const;
    void set_quantity_canceled(Decimal value);

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

    bool operator==(const OrderPartialCancelMessage& other) const;
    bool operator!=(const OrderPartialCancelMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t order_id_{};
    Decimal quantity_canceled_{ 0, -6 };
};

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
