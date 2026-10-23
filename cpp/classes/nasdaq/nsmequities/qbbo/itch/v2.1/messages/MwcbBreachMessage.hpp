#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/BreachedLevel.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

class Visitor;

// Informs data recipients when a MWCB has breached one of the established levels
class MwcbBreachMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MwcbBreachMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    MwcbBreachMessage() = default;
    MwcbBreachMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, BreachedLevel breached_level);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Time Stamp: Timestamp
    std::chrono::nanoseconds time_stamp() const;
    void set_time_stamp(std::chrono::nanoseconds value);

    // Breached Level: Denotes the MWCB Level that was breached.
    BreachedLevel breached_level() const;
    void set_breached_level(BreachedLevel value);

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

    bool operator==(const MwcbBreachMessage& other) const;
    bool operator!=(const MwcbBreachMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds time_stamp_{};
    BreachedLevel breached_level_{};
};

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
