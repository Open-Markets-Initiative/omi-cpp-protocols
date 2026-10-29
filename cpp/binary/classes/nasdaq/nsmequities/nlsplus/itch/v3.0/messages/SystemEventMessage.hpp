#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/EventCode.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// System Event Messages is used to signal key market or data feed control events.
class SystemEventMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SystemEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    SystemEventMessage() = default;
    SystemEventMessage(EventCode event_code);

    // Event Code: Denotes the Nls Plus type of system event for which the message is being
    // generated
    EventCode event_code() const;
    void set_event_code(EventCode value);

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

    bool operator==(const SystemEventMessage& other) const;
    bool operator!=(const SystemEventMessage& other) const;

  private:
    EventCode event_code_{};
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
