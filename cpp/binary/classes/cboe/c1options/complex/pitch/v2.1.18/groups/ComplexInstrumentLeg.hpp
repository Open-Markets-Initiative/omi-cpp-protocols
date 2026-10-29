#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

#include "../enums/LegSecurityType.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Leg for multi-leg strategies
class ComplexInstrumentLeg {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 13;

    ComplexInstrumentLeg() = default;
    ComplexInstrumentLeg(const std::string& leg_symbol, std::int32_t leg_ratio, LegSecurityType leg_security_type);

    // Leg Symbol: Option or Equity Symbol of leg, right padded with spaces.
    const std::string& leg_symbol() const;
    std::string& leg_symbol();
    void set_leg_symbol(const std::string& value);

    // Leg Ratio: Leg ratio (positive for buy-side, negative for sell-side). For options this
    // is the number of contracts, for equities this is the number of shares.
    std::int32_t leg_ratio() const;
    void set_leg_ratio(std::int32_t value);

    // Leg Security Type: Option or Equity instrument
    LegSecurityType leg_security_type() const;
    void set_leg_security_type(LegSecurityType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ComplexInstrumentLeg& other) const;
    bool operator!=(const ComplexInstrumentLeg& other) const;

  private:
    std::string leg_symbol_{};
    std::int32_t leg_ratio_{};
    LegSecurityType leg_security_type_{};
};

std::ostream& operator<<(std::ostream& out, const ComplexInstrumentLeg& value);

} // namespace cboe::c1options::complex::pitch::v2_1_18
