#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class Visitor;

// Debug packets are intended to provide human readable text that may aid in debugging problems
class DebugPacket : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = ClientPacketType::DebugPacket;

    DebugPacket() = default;
    DebugPacket(const std::string& debug_text);

    // Debug Text: Free form human readable text
    const std::string& debug_text() const;
    std::string& debug_text();
    void set_debug_text(const std::string& value);

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

    bool operator==(const DebugPacket& other) const;
    bool operator!=(const DebugPacket& other) const;

  private:
    std::string debug_text_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
