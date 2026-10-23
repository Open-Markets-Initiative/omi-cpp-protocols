#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/SchemaId.hpp"
#include "../enums/TemplateId.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// Template ID and length of message root
class MessageHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    MessageHeader() = default;
    MessageHeader(std::uint16_t block_length, TemplateId template_id, SchemaId schema_id, std::uint16_t version);

    // Block Length:
    std::uint16_t block_length() const;
    void set_block_length(std::uint16_t value);

    // Template Id:
    TemplateId template_id() const;
    void set_template_id(TemplateId value);

    // Schema Id:
    SchemaId schema_id() const;
    void set_schema_id(SchemaId value);

    // Version:
    std::uint16_t version() const;
    void set_version(std::uint16_t value);

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
    std::uint16_t block_length_{};
    TemplateId template_id_{};
    SchemaId schema_id_{};
    std::uint16_t version_{};
};

std::ostream& operator<<(std::ostream& out, const MessageHeader& value);

} // namespace cme::globex::mdp3::sbe::v1_9
