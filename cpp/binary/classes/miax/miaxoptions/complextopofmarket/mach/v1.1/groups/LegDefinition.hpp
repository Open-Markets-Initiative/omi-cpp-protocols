#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/LegSide.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Complex Strategy Number of Legs
class LegDefinition {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 15;

    LegDefinition() = default;
    LegDefinition(std::uint32_t product_id, std::uint16_t leg_ratio_qty, LegSide leg_side, const std::array<std::byte, 8>& reserved_8);

    // Product Id: MIAX Product ID mapped to a given option. It is assigned per trading session
    // and is valid for that session.
    std::uint32_t product_id() const;
    void set_product_id(std::uint32_t value);

    // Leg Ratio Qty: The ratio of this individual leg
    std::uint16_t leg_ratio_qty() const;
    void set_leg_ratio_qty(std::uint16_t value);

    // Leg Side: The side of this individual leg
    LegSide leg_side() const;
    void set_leg_side(LegSide value);

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

    bool operator==(const LegDefinition& other) const;
    bool operator!=(const LegDefinition& other) const;

  private:
    std::uint32_t product_id_{};
    std::uint16_t leg_ratio_qty_{};
    LegSide leg_side_{};
    std::array<std::byte, 8> reserved_8_{};
};

std::ostream& operator<<(std::ostream& out, const LegDefinition& value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
