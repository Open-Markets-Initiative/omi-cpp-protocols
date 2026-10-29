#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Md Entry Px
class MdEntryPx {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    MdEntryPx() = default;
    MdEntryPx(std::int8_t md_entry_px_exponent, std::int32_t md_entry_px_mantissa);

    // Md Entry Px Exponent: Price at this level and side of book.
    std::int8_t md_entry_px_exponent() const;
    void set_md_entry_px_exponent(std::int8_t value);

    // Md Entry Px Mantissa: Price at this level and side of book.
    std::int32_t md_entry_px_mantissa() const;
    void set_md_entry_px_mantissa(std::int32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MdEntryPx& other) const;
    bool operator!=(const MdEntryPx& other) const;

  private:
    std::int8_t md_entry_px_exponent_{};
    std::int32_t md_entry_px_mantissa_{};
};

std::ostream& operator<<(std::ostream& out, const MdEntryPx& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
