#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/LegSide.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Security Definition Leg
class SecurityDefinitionLeg {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 9;

    SecurityDefinitionLeg() = default;
    SecurityDefinitionLeg(std::uint32_t leg_ratio_qty, std::uint32_t leg_security_id, LegSide leg_side);

    // Leg Ratio Qty: Leg ratio
    std::uint32_t leg_ratio_qty() const;
    void set_leg_ratio_qty(std::uint32_t value);

    // Leg Security Id: SecurityID of the leg
    std::uint32_t leg_security_id() const;
    void set_leg_security_id(std::uint32_t value);

    // Leg Side:
    LegSide leg_side() const;
    void set_leg_side(LegSide value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SecurityDefinitionLeg& other) const;
    bool operator!=(const SecurityDefinitionLeg& other) const;

  private:
    std::uint32_t leg_ratio_qty_{};
    std::uint32_t leg_security_id_{};
    LegSide leg_side_{};
};

std::ostream& operator<<(std::ostream& out, const SecurityDefinitionLeg& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
