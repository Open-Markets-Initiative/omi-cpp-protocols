#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// Add Flags
class AddFlags {
  public:
    static constexpr const char* name = "AddFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool display() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    void print(std::ostream& out) const {
        out << "AddFlags{";
        out << "display=";
        out << (display() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddFlags& value) {
    value.print(out);
    return out;
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
