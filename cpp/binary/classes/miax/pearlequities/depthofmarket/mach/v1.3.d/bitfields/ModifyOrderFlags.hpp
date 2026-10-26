#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Modify Order flags. Bit 0 indicates Order Position; bits 1-7 are undefined.
class ModifyOrderFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    ModifyOrderFlags() = default;
    explicit ModifyOrderFlags(std::uint8_t raw);

    // Order Position: 0 - Order kept its position in the book; 1 - Order lost its position in
    // the book.
    bool order_position() const;
    void set_order_position(bool value);

    // The whole bitfield as its wire integer
    std::uint8_t raw() const;
    void set_raw(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ModifyOrderFlags& other) const;
    bool operator!=(const ModifyOrderFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const ModifyOrderFlags& value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
