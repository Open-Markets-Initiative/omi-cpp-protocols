#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

class Visitor;

// Reduce Size messages are sent when a visible order on the Cboe book is partially reduced.
class ReduceSizeShortMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ReduceSizeShortMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 14;

    ReduceSizeShortMessage() = default;
    ReduceSizeShortMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint16_t canceled_short_quantity);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Canceled Short Quantity: Number of shares/contracts canceled
    std::uint16_t canceled_short_quantity() const;
    void set_canceled_short_quantity(std::uint16_t value);

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

    bool operator==(const ReduceSizeShortMessage& other) const;
    bool operator!=(const ReduceSizeShortMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    std::uint16_t canceled_short_quantity_{};
};

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
