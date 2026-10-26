#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class Visitor;

// Provides information about registered orders in case of Zaraba execution. Delivered when an
// execution occurs in Zaraba.
class OrderExecutedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 19;

    OrderExecutedMessage() = default;
    OrderExecutedMessage(std::chrono::microseconds time_microseconds, std::uint32_t order_id, Side side, std::uint64_t volume, std::uint32_t match_id);

    // Time Microseconds: Time to the nearest microsecond
    std::chrono::microseconds time_microseconds() const;
    void set_time_microseconds(std::chrono::microseconds value);

    // Order Id: Identifier assigned per issue on an order basis, unique and sequential each
    // business day
    std::uint32_t order_id() const;
    void set_order_id(std::uint32_t value);

    // Side: Indicates buy or sell
    Side side() const;
    void set_side(Side value);

    // Volume: Executed volume in number of shares
    std::uint64_t volume() const;
    void set_volume(std::uint64_t value);

    // Match Id: Identifier assigned per issue on an execution basis, unique and sequential
    // each business day
    std::uint32_t match_id() const;
    void set_match_id(std::uint32_t value);

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
    std::chrono::microseconds time_microseconds_{};
    std::uint32_t order_id_{};
    Side side_{};
    std::uint64_t volume_{};
    std::uint32_t match_id_{};
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
