#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

class Visitor;

// End of Session message
class EndOfSessionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::EndOfSessionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    EndOfSessionMessage() = default;
    EndOfSessionMessage(std::uint32_t timestamp);

    // Timestamp: Nanosecond offset from last
    std::uint32_t timestamp() const;
    void set_timestamp(std::uint32_t value);

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

    bool operator==(const EndOfSessionMessage& other) const;
    bool operator!=(const EndOfSessionMessage& other) const;

  private:
    std::uint32_t timestamp_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
