#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

class Visitor;

// Sequence_2Message
class SequenceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::Sequence2Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    SequenceMessage() = default;
    SequenceMessage(std::uint32_t next_seq_no);

    // Next Seq No: nextSeqNo
    std::uint32_t next_seq_no() const;
    void set_next_seq_no(std::uint32_t value);

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

    bool operator==(const SequenceMessage& other) const;
    bool operator!=(const SequenceMessage& other) const;

  private:
    std::uint32_t next_seq_no_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
