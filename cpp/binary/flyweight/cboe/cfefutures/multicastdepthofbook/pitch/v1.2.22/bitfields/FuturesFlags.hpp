#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Futures Flags bitfields
class FuturesFlags {
  public:
    static constexpr const char* name = "FuturesFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FuturesFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool variance() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    void print(std::ostream& out) const {
        out << "FuturesFlags{";
        out << "variance=";
        out << (variance() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FuturesFlags& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
