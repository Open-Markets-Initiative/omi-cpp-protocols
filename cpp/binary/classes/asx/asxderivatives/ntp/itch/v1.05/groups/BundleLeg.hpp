#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/SideLeg.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Bundle Leg
class BundleLeg {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 17;

    BundleLeg() = default;
    BundleLeg(std::uint32_t tradeable_instrument_id_leg, SideLeg side_leg, std::uint32_t ratio_leg, Decimal price_leg);

    // Tradeable Instrument Id Leg: Instrument Id of the leg
    std::uint32_t tradeable_instrument_id_leg() const;
    void set_tradeable_instrument_id_leg(std::uint32_t value);

    // Side Leg: Side of the leg
    SideLeg side_leg() const;
    void set_side_leg(SideLeg value);

    // Ratio Leg: Ratio of the leg
    std::uint32_t ratio_leg() const;
    void set_ratio_leg(std::uint32_t value);

    // Price Leg: Price of the leg
    Decimal price_leg() const;
    void set_price_leg(Decimal value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const BundleLeg& other) const;
    bool operator!=(const BundleLeg& other) const;

  private:
    std::uint32_t tradeable_instrument_id_leg_{};
    SideLeg side_leg_{};
    std::uint32_t ratio_leg_{};
    Decimal price_leg_{ 0, -2 };
};

std::ostream& operator<<(std::ostream& out, const BundleLeg& value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
