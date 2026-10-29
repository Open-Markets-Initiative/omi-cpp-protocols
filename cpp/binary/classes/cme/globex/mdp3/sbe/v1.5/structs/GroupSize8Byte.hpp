#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_5 {

// 8 Byte aligned repeating group dimensions
class GroupSize8Byte {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    GroupSize8Byte() = default;
    GroupSize8Byte(std::uint16_t block_length, const std::array<std::byte, 5>& padding_5, std::uint8_t num_in_group);

    // Block Length: Length
    std::uint16_t block_length() const;
    void set_block_length(std::uint16_t value);

    // Padding 5: 5 bytes padding
    const std::array<std::byte, 5>& padding_5() const;
    std::array<std::byte, 5>& padding_5();
    void set_padding_5(const std::array<std::byte, 5>& value);

    // Num In Group: NumInGroup
    std::uint8_t num_in_group() const;
    void set_num_in_group(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const GroupSize8Byte& other) const;
    bool operator!=(const GroupSize8Byte& other) const;

  private:
    std::uint16_t block_length_{};
    std::array<std::byte, 5> padding_5_{};
    std::uint8_t num_in_group_{};
};

std::ostream& operator<<(std::ostream& out, const GroupSize8Byte& value);

} // namespace cme::globex::mdp3::sbe::v1_5
