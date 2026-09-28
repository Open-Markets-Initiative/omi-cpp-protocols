#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string>

#include "../common/Decimal.hpp"
#include "../enums/LegSecurityType.hpp"
#include "../enums/LegSide.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// noLegs
class LegsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 38;

    LegsGroup() = default;
    LegsGroup(std::uint64_t leg_security_id, std::optional<Decimal> leg_ratio_qty, LegSecurityType leg_security_type, LegSide leg_side, const std::string& leg_symbol);

    // Leg Security Id: Leg's security ID.
    std::uint64_t leg_security_id() const;
    void set_leg_security_id(std::uint64_t value);

    // Leg Ratio Qty: Ratio of quantity for this leg relative to the entire security.
    std::optional<Decimal> leg_ratio_qty() const;
    void set_leg_ratio_qty(std::optional<Decimal> value);

    // Leg Security Type: Leg's security type.
    LegSecurityType leg_security_type() const;
    void set_leg_security_type(LegSecurityType value);

    // Leg Side: Side of this leg.
    LegSide leg_side() const;
    void set_leg_side(LegSide value);

    // Leg Symbol: Leg symbol.
    const std::string& leg_symbol() const;
    std::string& leg_symbol();
    void set_leg_symbol(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const LegsGroup& other) const;
    bool operator!=(const LegsGroup& other) const;

  private:
    std::uint64_t leg_security_id_{};
    std::optional<Decimal> leg_ratio_qty_{};
    LegSecurityType leg_security_type_{};
    LegSide leg_side_{};
    std::string leg_symbol_{};
};

std::ostream& operator<<(std::ostream& out, const LegsGroup& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
