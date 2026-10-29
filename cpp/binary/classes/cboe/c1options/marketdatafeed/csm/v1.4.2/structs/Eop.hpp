#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Eop
class Eop {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    Eop() = default;
    Eop(std::int8_t eop_exponent, std::int32_t eop_mantissa);

    // Eop Exponent: The expected opening price
    std::int8_t eop_exponent() const;
    void set_eop_exponent(std::int8_t value);

    // Eop Mantissa: The expected opening price
    std::int32_t eop_mantissa() const;
    void set_eop_mantissa(std::int32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const Eop& other) const;
    bool operator!=(const Eop& other) const;

  private:
    std::int8_t eop_exponent_{};
    std::int32_t eop_mantissa_{};
};

std::ostream& operator<<(std::ostream& out, const Eop& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
