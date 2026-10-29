#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

class Visitor;

// The End of Session message is sent for each unit when the unit shuts down
class EndOfSession : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::EndOfSession;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    EndOfSession() = default;
    EndOfSession(std::uint32_t last_timestamp);

    // Last Timestamp: Nanosecond offset from last unit timestamp
    std::uint32_t last_timestamp() const;
    void set_last_timestamp(std::uint32_t value);

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

    bool operator==(const EndOfSession& other) const;
    bool operator!=(const EndOfSession& other) const;

  private:
    std::uint32_t last_timestamp_{};
};

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
