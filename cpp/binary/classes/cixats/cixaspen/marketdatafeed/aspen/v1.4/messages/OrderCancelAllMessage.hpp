#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

class Visitor;

// Sent when the order is canceled in its entirety
class OrderCancelAllMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderCancelAllMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    OrderCancelAllMessage() = default;
    OrderCancelAllMessage(std::chrono::nanoseconds timestamp, std::uint64_t order_id);

    // Timestamp: Nanoseconds Since Epoch (UTC)
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Order Id: Market Issued Unique Order ID
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

    bool operator==(const OrderCancelAllMessage& other) const;
    bool operator!=(const OrderCancelAllMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t order_id_{};
};

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
