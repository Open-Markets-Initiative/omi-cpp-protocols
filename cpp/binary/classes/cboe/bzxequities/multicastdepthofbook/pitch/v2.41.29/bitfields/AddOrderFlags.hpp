#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

// Add Order Flags
class AddOrderFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    AddOrderFlags() = default;
    explicit AddOrderFlags(std::uint8_t raw);

    // Display: Order is displayed in the Cboe SIP quote
    bool display() const;
    void set_display(bool value);

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

    bool operator==(const AddOrderFlags& other) const;
    bool operator!=(const AddOrderFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const AddOrderFlags& value);

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29
