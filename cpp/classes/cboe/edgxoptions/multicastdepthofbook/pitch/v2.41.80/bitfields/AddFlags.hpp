#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Add Flags bit field used in Add Order messages. Bit 3 indicates AON (All or None) status
// (Options only).
class AddFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    AddFlags() = default;
    explicit AddFlags(std::uint8_t raw);

    // Aon: Options only. 0 = Order is a firm quote, 1 = Order is AON (All or None).
    bool aon() const;
    void set_aon(bool value);

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

    bool operator==(const AddFlags& other) const;
    bool operator!=(const AddFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const AddFlags& value);

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
