#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
class NoteCodesBitField8 {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    NoteCodesBitField8() = default;
    explicit NoteCodesBitField8(std::uint8_t raw);

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

    bool operator==(const NoteCodesBitField8& other) const;
    bool operator!=(const NoteCodesBitField8& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const NoteCodesBitField8& value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
