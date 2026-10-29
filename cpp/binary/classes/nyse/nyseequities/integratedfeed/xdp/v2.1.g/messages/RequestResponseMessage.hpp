#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Status.hpp"
#include "../messages/Message.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

class Visitor;

// This message will be sent immediately via TCP/IP in response to the client’s request for
// retransmission, refresh or Symbol Mapping messages.
class RequestResponseMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RequestResponseMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    RequestResponseMessage() = default;
    RequestResponseMessage(std::uint32_t request_seq_num, std::uint32_t begin_seq_num, std::uint32_t end_seq_num, const std::string& source_id, std::uint8_t product_id, std::uint8_t channel_id, Status status);

    // Request Seq Num: The sequence number of the request message sent by the client.
    std::uint32_t request_seq_num() const;
    void set_request_seq_num(std::uint32_t value);

    // Begin Seq Num: The beginning sequence number of the range of messages to be
    // retransmitted.
    std::uint32_t begin_seq_num() const;
    void set_begin_seq_num(std::uint32_t value);

    // End Seq Num: The end sequence number of the range of messages to be retransmitted.
    std::uint32_t end_seq_num() const;
    void set_end_seq_num(std::uint32_t value);

    // Source Id: The ID of the client requesting this retransmission . This field is up to 9
    // characters, null terminated.
    const std::string& source_id() const;
    std::string& source_id();
    void set_source_id(const std::string& value);

    // Product Id: The unique ID for this NYSE feed listed in the feed’s client specification.
    std::uint8_t product_id() const;
    void set_product_id(std::uint8_t value);

    // Channel Id: The ID of the multicast channel over which the packet was sent.
    std::uint8_t channel_id() const;
    void set_channel_id(std::uint8_t value);

    // Status: The reason why the request was rejected.
    Status status() const;
    void set_status(Status value);

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

    bool operator==(const RequestResponseMessage& other) const;
    bool operator!=(const RequestResponseMessage& other) const;

  private:
    std::uint32_t request_seq_num_{};
    std::uint32_t begin_seq_num_{};
    std::uint32_t end_seq_num_{};
    std::string source_id_{};
    std::uint8_t product_id_{};
    std::uint8_t channel_id_{};
    Status status_{};
};

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
