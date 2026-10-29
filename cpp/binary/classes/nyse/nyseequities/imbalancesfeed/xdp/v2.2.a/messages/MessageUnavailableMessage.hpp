#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

class Visitor;

// This message will be sent over the Retransmission multicast channels to inform clients of
// unavailability of a range of messages (or part of a range) for which they may have requested
// a retransmission.
class MessageUnavailableMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MessageUnavailableMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 10;

    MessageUnavailableMessage() = default;
    MessageUnavailableMessage(std::uint32_t begin_seq_num, std::uint32_t end_seq_num, std::uint8_t product_id, std::uint8_t channel_id);

    // Begin Seq Num: The beginning sequence number of the range of messages to be
    // retransmitted.
    std::uint32_t begin_seq_num() const;
    void set_begin_seq_num(std::uint32_t value);

    // End Seq Num: The end sequence number of the range of messages to be retransmitted.
    std::uint32_t end_seq_num() const;
    void set_end_seq_num(std::uint32_t value);

    // Product Id: The unique ID for this NYSE feed listed in the feed’s client specification.
    std::uint8_t product_id() const;
    void set_product_id(std::uint8_t value);

    // Channel Id: The ID of the multicast channel over which the packet was sent.
    std::uint8_t channel_id() const;
    void set_channel_id(std::uint8_t value);

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

    bool operator==(const MessageUnavailableMessage& other) const;
    bool operator!=(const MessageUnavailableMessage& other) const;

  private:
    std::uint32_t begin_seq_num_{};
    std::uint32_t end_seq_num_{};
    std::uint8_t product_id_{};
    std::uint8_t channel_id_{};
};

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
