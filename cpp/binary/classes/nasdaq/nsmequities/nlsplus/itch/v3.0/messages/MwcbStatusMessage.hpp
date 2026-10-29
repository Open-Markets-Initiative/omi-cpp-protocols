#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/BreachedLevel.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// Informs the market that a market wide circuit breaker decline level has been breached.
class MwcbStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MwcbStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    MwcbStatusMessage() = default;
    MwcbStatusMessage(BreachedLevel breached_level);

    // Breached Level: Denotes the Mwcb level that was breached
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

    bool operator==(const MwcbStatusMessage& other) const;
    bool operator!=(const MwcbStatusMessage& other) const;

  private:
    BreachedLevel breached_level_{};
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
