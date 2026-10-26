#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Modify Flags bit field used in Modify Order messages. Bit 0 indicates whether the order is
// aggregated in the Cboe SIP quote; Bit 1 indicates whether priority is maintained or reset.
class ModifyFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    ModifyFlags() = default;
    explicit ModifyFlags(std::uint8_t raw);

    // Display: 0 = Order is not aggregated in the Cboe SIP quote, 1 = Order is aggregated in
    // the Cboe SIP quote.
    bool display() const;
    void set_display(bool value);

    // Maintain Priority: 0 = Reset Priority, 1 = Maintain Priority.
    bool maintain_priority() const;
    void set_maintain_priority(bool value);

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

    bool operator==(const ModifyFlags& other) const;
    bool operator!=(const ModifyFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const ModifyFlags& value);

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
