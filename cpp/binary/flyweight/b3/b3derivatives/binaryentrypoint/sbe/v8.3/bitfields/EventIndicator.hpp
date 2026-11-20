// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: bitfields/EventIndicator.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// EventIndicator bit set
class EventIndicator {
  public:
    static constexpr const char* name = "EventIndicator";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EventIndicator(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool poss_resend() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool low_priority() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    void print(std::ostream& out) const {
        out << "EventIndicator{";
        out << "poss_resend=";
        out << (poss_resend() ? "true" : "false");
        out << ", low_priority=";
        out << (low_priority() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EventIndicator& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
