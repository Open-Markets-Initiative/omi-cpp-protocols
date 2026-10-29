#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// Reduce Size messages are sent when a visible order on the Cboe book is partially reduced.
class ReduceSizeLongMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ReduceSizeLongMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    ReduceSizeLongMessage() = default;
    ReduceSizeLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t canceled_quantity);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Canceled Quantity: Instrument quantity canceled
    std::uint32_t canceled_quantity() const;
    void set_canceled_quantity(std::uint32_t value);

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

    bool operator==(const ReduceSizeLongMessage& other) const;
    bool operator!=(const ReduceSizeLongMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    std::uint32_t canceled_quantity_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
