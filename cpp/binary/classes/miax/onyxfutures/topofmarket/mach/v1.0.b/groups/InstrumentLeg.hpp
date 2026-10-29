#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Complex Strategy Number of Legs
class InstrumentLeg {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 20;

    InstrumentLeg() = default;
    InstrumentLeg(std::uint32_t instrument_id, std::int32_t leg_ratio_and_side, std::uint32_t maturity_month_year, const std::array<std::byte, 8>& reserved_8);

    // Instrument Id: Unique ID assigned by MIAX Futures Onyx
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Leg Ratio And Side: Leg ratio for the specified instrument
    std::int32_t leg_ratio_and_side() const;
    void set_leg_ratio_and_side(std::int32_t value);

    // Maturity Month Year: Maturity Month-Year is the expiration date of a Simple Instrument
    std::uint32_t maturity_month_year() const;
    void set_maturity_month_year(std::uint32_t value);

    // Reserved 8: Reserved for future use
    const std::array<std::byte, 8>& reserved_8() const;
    std::array<std::byte, 8>& reserved_8();
    void set_reserved_8(const std::array<std::byte, 8>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const InstrumentLeg& other) const;
    bool operator!=(const InstrumentLeg& other) const;

  private:
    std::uint32_t instrument_id_{};
    std::int32_t leg_ratio_and_side_{};
    std::uint32_t maturity_month_year_{};
    std::array<std::byte, 8> reserved_8_{};
};

std::ostream& operator<<(std::ostream& out, const InstrumentLeg& value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
