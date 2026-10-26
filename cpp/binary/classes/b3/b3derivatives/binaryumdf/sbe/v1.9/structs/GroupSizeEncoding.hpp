#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// GroupSizeEncoding
class GroupSizeEncoding {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 3;

    GroupSizeEncoding() = default;
    GroupSizeEncoding(std::uint16_t block_length, std::uint8_t num_in_group);

    // Block Length: blockLength
    std::uint16_t block_length() const;
    void set_block_length(std::uint16_t value);

    // Num In Group: numInGroup
    std::uint8_t num_in_group() const;
    void set_num_in_group(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const GroupSizeEncoding& other) const;
    bool operator!=(const GroupSizeEncoding& other) const;

  private:
    std::uint16_t block_length_{};
    std::uint8_t num_in_group_{};
};

std::ostream& operator<<(std::ostream& out, const GroupSizeEncoding& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
