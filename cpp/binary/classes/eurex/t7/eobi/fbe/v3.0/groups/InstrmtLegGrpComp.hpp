#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../enums/LegSide.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

// Instrmt Leg Grp Comp
class InstrmtLegGrpComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 24;

    InstrmtLegGrpComp() = default;
    InstrmtLegGrpComp(std::optional<std::int32_t> leg_symbol, const std::array<std::byte, 4>& pad4, std::optional<std::int64_t> leg_security_id, std::optional<std::int32_t> leg_ratio_qty, std::optional<LegSide> leg_side, const std::array<std::byte, 3>& pad3);

    // Leg Symbol:
    std::optional<std::int32_t> leg_symbol() const;
    void set_leg_symbol(std::optional<std::int32_t> value);

    // Pad4:
    const std::array<std::byte, 4>& pad4() const;
    std::array<std::byte, 4>& pad4();
    void set_pad4(const std::array<std::byte, 4>& value);

    // Leg Security Id:
    std::optional<std::int64_t> leg_security_id() const;
    void set_leg_security_id(std::optional<std::int64_t> value);

    // Leg Ratio Qty:
    std::optional<std::int32_t> leg_ratio_qty() const;
    void set_leg_ratio_qty(std::optional<std::int32_t> value);

    // Leg Side:
    std::optional<LegSide> leg_side() const;
    void set_leg_side(std::optional<LegSide> value);

    // Pad3:
    const std::array<std::byte, 3>& pad3() const;
    std::array<std::byte, 3>& pad3();
    void set_pad3(const std::array<std::byte, 3>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const InstrmtLegGrpComp& other) const;
    bool operator!=(const InstrmtLegGrpComp& other) const;

  private:
    std::optional<std::int32_t> leg_symbol_{};
    std::array<std::byte, 4> pad4_{};
    std::optional<std::int64_t> leg_security_id_{};
    std::optional<std::int32_t> leg_ratio_qty_{};
    std::optional<LegSide> leg_side_{};
    std::array<std::byte, 3> pad3_{};
};

std::ostream& operator<<(std::ostream& out, const InstrmtLegGrpComp& value);

} // namespace eurex::t7::eobi::fbe::v3_0
