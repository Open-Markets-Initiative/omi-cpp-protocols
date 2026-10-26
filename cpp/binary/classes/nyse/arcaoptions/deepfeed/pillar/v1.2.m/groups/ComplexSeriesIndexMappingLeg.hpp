#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/LegSecurityType.hpp"
#include "../enums/LegSide.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Complex Series Index Mapping Leg
class ComplexSeriesIndexMappingLeg {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    ComplexSeriesIndexMappingLeg() = default;
    ComplexSeriesIndexMappingLeg(std::uint32_t symbol_index, std::uint16_t leg_ratio_qty, LegSide leg_side, LegSecurityType leg_security_type);

    // Symbol Index: The unique ID of this symbol for all products within this market.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Leg Ratio Qty: Leg Ratio. This field will repeat for each leg.
    std::uint16_t leg_ratio_qty() const;
    void set_leg_ratio_qty(std::uint16_t value);

    // Leg Side: Leg side. This field will repeat for each leg.
    LegSide leg_side() const;
    void set_leg_side(LegSide value);

    // Leg Security Type: Leg Security Type. This field will repeat for each leg.
    LegSecurityType leg_security_type() const;
    void set_leg_security_type(LegSecurityType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ComplexSeriesIndexMappingLeg& other) const;
    bool operator!=(const ComplexSeriesIndexMappingLeg& other) const;

  private:
    std::uint32_t symbol_index_{};
    std::uint16_t leg_ratio_qty_{};
    LegSide leg_side_{};
    LegSecurityType leg_security_type_{};
};

std::ostream& operator<<(std::ostream& out, const ComplexSeriesIndexMappingLeg& value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
