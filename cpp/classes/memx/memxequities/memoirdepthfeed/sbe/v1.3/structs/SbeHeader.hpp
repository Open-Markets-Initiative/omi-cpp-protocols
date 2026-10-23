#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/TemplateId.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Sbe Header
class SbeHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 6;

    SbeHeader() = default;
    SbeHeader(std::uint16_t block_length, TemplateId template_id, std::uint8_t schema_id, std::uint16_t version);

    // Block Length: Memx Udp Message Type
    std::uint16_t block_length() const;
    void set_block_length(std::uint16_t value);

    // Template Id: T8 Identifier of the message template
    TemplateId template_id() const;
    void set_template_id(TemplateId value);

    // Schema Id: The identifier of a message schema
    std::uint8_t schema_id() const;
    void set_schema_id(std::uint8_t value);

    // Version: The version number of the message schema that was used to encode a message
    std::uint16_t version() const;
    void set_version(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SbeHeader& other) const;
    bool operator!=(const SbeHeader& other) const;

  private:
    std::uint16_t block_length_{};
    TemplateId template_id_{};
    std::uint8_t schema_id_{};
    std::uint16_t version_{};
};

std::ostream& operator<<(std::ostream& out, const SbeHeader& value);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
