#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/ExpirationMonth.hpp"

namespace siac::opra::output::obi::v6_2 {

// Expiration Block
class ExpirationBlock {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 3;

    ExpirationBlock() = default;
    ExpirationBlock(ExpirationMonth expiration_month, std::uint8_t expiration_day, std::uint8_t expiration_year);

    // Expiration Month: Indicates the expiration month and identifies the option as a Call or
    // a Put.
    ExpirationMonth expiration_month() const;
    void set_expiration_month(ExpirationMonth value);

    // Expiration Day: Contains Hex 0x01 to 0x1F (decimal 1 to 31), indicating the day of the
    // month the series expires.
    std::uint8_t expiration_day() const;
    void set_expiration_day(std::uint8_t value);

    // Expiration Year: Contains Hex 0x00 to 0x63 (decimal 0 to 99). Represents the year,
    // starting with year 2000.
    std::uint8_t expiration_year() const;
    void set_expiration_year(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ExpirationBlock& other) const;
    bool operator!=(const ExpirationBlock& other) const;

  private:
    ExpirationMonth expiration_month_{};
    std::uint8_t expiration_day_{};
    std::uint8_t expiration_year_{};
};

std::ostream& operator<<(std::ostream& out, const ExpirationBlock& value);

} // namespace siac::opra::output::obi::v6_2
