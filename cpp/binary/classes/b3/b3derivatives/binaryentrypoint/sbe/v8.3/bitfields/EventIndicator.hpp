// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: bitfields/EventIndicator.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// EventIndicator bit set
class EventIndicator {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    EventIndicator() = default;
    explicit EventIndicator(std::uint8_t raw);

    // Poss Resend: PossResend
    bool poss_resend() const;
    void set_poss_resend(bool value);

    // Low Priority: LowPriority
    bool low_priority() const;
    void set_low_priority(bool value);

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

    bool operator==(const EventIndicator& other) const;
    bool operator!=(const EventIndicator& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const EventIndicator& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
