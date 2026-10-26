#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// An execution has been broken and cannot be reinstated
class BrokenTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::BrokenTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 14;

    BrokenTradeMessage() = default;
    BrokenTradeMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint32_t match_number);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Tracking Number: Nasdaq Nordic internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Match Number: Day unique match number of this execution
    std::uint32_t match_number() const;
    void set_match_number(std::uint32_t value);

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
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint32_t match_number_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
