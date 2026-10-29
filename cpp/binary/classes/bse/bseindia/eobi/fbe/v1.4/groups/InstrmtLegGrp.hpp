#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../enums/LegSide.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Leg definitions repeated NoLegs times in the Add Complex Instrument Message.
class InstrmtLegGrp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 16;

    InstrmtLegGrp() = default;
    InstrmtLegGrp(std::int64_t leg_security_id, std::optional<std::int32_t> leg_ratio_qty, LegSide leg_side, const std::array<std::byte, 3>& pad_3);

    // Leg Security Id: Instrument identifier of the leg security.
    std::int64_t leg_security_id() const;
    void set_leg_security_id(std::int64_t value);

    // Leg Ratio Qty: The ratio of quantity for this individual leg relative to the entire
    // multi-leg security.
    std::optional<std::int32_t> leg_ratio_qty() const;
    void set_leg_ratio_qty(std::optional<std::int32_t> value);

    // Leg Side: The side of the individual leg of a strategy as defined in signature.
    LegSide leg_side() const;
    void set_leg_side(LegSide value);

    // Pad 3: not used
    const std::array<std::byte, 3>& pad_3() const;
    std::array<std::byte, 3>& pad_3();
    void set_pad_3(const std::array<std::byte, 3>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const InstrmtLegGrp& other) const;
    bool operator!=(const InstrmtLegGrp& other) const;

  private:
    std::int64_t leg_security_id_{};
    std::optional<std::int32_t> leg_ratio_qty_{};
    LegSide leg_side_{};
    std::array<std::byte, 3> pad_3_{};
};

std::ostream& operator<<(std::ostream& out, const InstrmtLegGrp& value);

} // namespace bse::bseindia::eobi::fbe::v1_4
