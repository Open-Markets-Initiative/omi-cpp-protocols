#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/LegSecurityType.hpp"
#include "../enums/Side.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Leg definition
class LegDefinition {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    LegDefinition() = default;
    LegDefinition(std::uint32_t symbol_index, std::uint16_t leg_ratio_qty, Side side, LegSecurityType leg_security_type);

    // Symbol Index: Series index if Security type is Option. Underlying index if Security type
    // is Equity
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Leg Ratio Qty: Leg ratio
    std::uint16_t leg_ratio_qty() const;
    void set_leg_ratio_qty(std::uint16_t value);

    // Side: Side of the RFQ
    Side side() const;
    void set_side(Side value);

    // Leg Security Type: Leg Security Type
    LegSecurityType leg_security_type() const;
    void set_leg_security_type(LegSecurityType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const LegDefinition& other) const;
    bool operator!=(const LegDefinition& other) const;

  private:
    std::uint32_t symbol_index_{};
    std::uint16_t leg_ratio_qty_{};
    Side side_{};
    LegSecurityType leg_security_type_{};
};

std::ostream& operator<<(std::ostream& out, const LegDefinition& value);

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
