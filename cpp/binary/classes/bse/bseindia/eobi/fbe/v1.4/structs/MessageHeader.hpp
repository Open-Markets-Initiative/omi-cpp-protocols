#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/TemplateId.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Body Len, Template Id, and Msg Seq Num opening every message behind the Packet Header
class MessageHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    MessageHeader() = default;
    MessageHeader(std::uint16_t body_len, TemplateId template_id, std::uint32_t msg_seq_num);

    // Body Len: Number of bytes for the message, including this field
    std::uint16_t body_len() const;
    void set_body_len(std::uint16_t value);

    // Template Id: Unique identifier for a Bse Eobi message layout
    TemplateId template_id() const;
    void set_template_id(TemplateId value);

    // Msg Seq Num: Message sequence number, incremented per product across all message types
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
    std::uint16_t body_len_{};
    TemplateId template_id_{};
    std::uint32_t msg_seq_num_{};
};

std::ostream& operator<<(std::ostream& out, const MessageHeader& value);

} // namespace bse::bseindia::eobi::fbe::v1_4
