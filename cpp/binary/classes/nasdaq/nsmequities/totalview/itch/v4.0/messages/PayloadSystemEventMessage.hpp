#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/EventCode.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class PacketMessageVisitor;

// The system event message type is used to signal a market or data feed handler event.
class PayloadSystemEventMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::SystemEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 5;

    PayloadSystemEventMessage() = default;
    PayloadSystemEventMessage(std::chrono::nanoseconds nanoseconds, EventCode event_code);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Event Code: See System Event Codes.
    EventCode event_code() const;
    void set_event_code(EventCode value);

    // PacketMessage
    PacketMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PacketMessageVisitor& visitor) const override;
    std::unique_ptr<PacketMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const PacketMessage& other) const override;

    bool operator==(const PayloadSystemEventMessage& other) const;
    bool operator!=(const PayloadSystemEventMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    EventCode event_code_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
