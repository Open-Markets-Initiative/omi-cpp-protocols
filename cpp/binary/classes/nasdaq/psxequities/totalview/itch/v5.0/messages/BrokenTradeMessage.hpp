#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::psxequities::totalview::itch::v5_0 {

class Visitor;

// The Broken Trade Message is sent whenever an execution on Nasdaq PSX is broken. An execution
// may be broken if it is found to be “clearly erroneous” pursuant to Nasdaq’s Clearly
// Erroneous Policy. A trade break is final; once a trade is broken, it cannot be reinstated.
class BrokenTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::BrokenTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 18;

    BrokenTradeMessage() = default;
    BrokenTradeMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t match_number);

    // Stock Locate: Always 0
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: NASDAQ PSX internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Match Number: The Nasdaq PSX generated day unique Match Number of this execution
    std::uint64_t match_number() const;
    void set_match_number(std::uint64_t value);

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

    bool operator==(const BrokenTradeMessage& other) const;
    bool operator!=(const BrokenTradeMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t match_number_{};
};

} // namespace nasdaq::psxequities::totalview::itch::v5_0
