#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

class Visitor;

// Reduce Size message (long)
class ReduceSizeLongMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ReduceSizeLongMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    ReduceSizeLongMessage() = default;
    ReduceSizeLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t canceled_quantity_binary_4);

    // Time Offset: Nanosecond offset from last
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Canceled Quantity Binary 4: Number of shares/contracts
    std::uint32_t canceled_quantity_binary_4() const;
    void set_canceled_quantity_binary_4(std::uint32_t value);

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
    std::uint32_t canceled_quantity_binary_4_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
