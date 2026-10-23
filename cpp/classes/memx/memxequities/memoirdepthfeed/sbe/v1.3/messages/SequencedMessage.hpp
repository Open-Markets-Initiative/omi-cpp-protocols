#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../groups/SequencedMessageMessage.hpp"
#include "../messages/Message.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class Visitor;

// Sequenced Message
class SequencedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SequencedMessage;

    SequencedMessage() = default;
    SequencedMessage(std::uint16_t message_count, const std::vector<SequencedMessageMessage>& message);

    // Message Count: Number of messages in this packet
    std::uint16_t message_count() const;
    void set_message_count(std::uint16_t value);

    // Message: Message List Element
    const std::vector<SequencedMessageMessage>& message() const;
    std::vector<SequencedMessageMessage>& message();
    void set_message(const std::vector<SequencedMessageMessage>& value);

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

    bool operator==(const SequencedMessage& other) const;
    bool operator!=(const SequencedMessage& other) const;

  private:
    std::uint16_t message_count_{};
    std::vector<SequencedMessageMessage> message_{};
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
