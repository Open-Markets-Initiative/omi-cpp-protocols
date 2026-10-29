#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/TemplateId.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Message Header
class MessageHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    MessageHeader() = default;
    MessageHeader(std::uint16_t message_length, TemplateId template_id, char message_type, std::uint32_t msg_seq_num);

    // Message Length: Length of the message in bytes
    std::uint16_t message_length() const;
    void set_message_length(std::uint16_t value);

    // Template Id: The Template ID is for decoding the message.
    TemplateId template_id() const;
    void set_template_id(TemplateId value);

    // Message Type: Code identifying this message type
    char message_type() const;
    void set_message_type(char value);

    // Msg Seq Num: Message Sequence Number
    std::uint32_t msg_seq_num() const;
    void set_msg_seq_num(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MessageHeader& other) const;
    bool operator!=(const MessageHeader& other) const;

  private:
    std::uint16_t message_length_{};
    TemplateId template_id_{};
    char message_type_{};
    std::uint32_t msg_seq_num_{};
};

std::ostream& operator<<(std::ostream& out, const MessageHeader& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
