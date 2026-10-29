#pragma once

#include <array>
#include <cstddef>
#include <ostream>
#include <string>

#include "../common/Decimal.hpp"
#include "../enums/LegSide.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// noLegs
class LegsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 30;

    LegsGroup() = default;
    LegsGroup(const std::string& leg_symbol, Decimal leg_ratio_qty, LegSide leg_side, const std::array<std::byte, 1>& padding_1);

    // Leg Symbol: Multileg instrument's individual security’s Symbol. See Symbol (55) field
    // for description.
    const std::string& leg_symbol() const;
    std::string& leg_symbol();
    void set_leg_symbol(const std::string& value);

    // Leg Ratio Qty: The ratio of quantity for this individual leg relative to the entire
    // multileg security.
    Decimal leg_ratio_qty() const;
    void set_leg_ratio_qty(Decimal value);

    // Leg Side: The side of this individual leg (multileg security). See Side (54) field for
    // description and values.
    LegSide leg_side() const;
    void set_leg_side(LegSide value);

    // Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& padding_1() const;
    std::array<std::byte, 1>& padding_1();
    void set_padding_1(const std::array<std::byte, 1>& value);

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
    std::string leg_symbol_{};
    Decimal leg_ratio_qty_{ 0, -7 };
    LegSide leg_side_{};
    std::array<std::byte, 1> padding_1_{};
};

std::ostream& operator<<(std::ostream& out, const LegsGroup& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
