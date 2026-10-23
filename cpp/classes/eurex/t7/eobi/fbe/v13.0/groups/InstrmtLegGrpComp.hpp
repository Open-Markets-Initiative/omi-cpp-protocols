#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/LegSecurityType.hpp"
#include "../enums/LegSide.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// Instrmt Leg Grp Comp
class InstrmtLegGrpComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    InstrmtLegGrpComp() = default;
    InstrmtLegGrpComp(std::optional<std::int32_t> leg_symbol, const std::array<std::byte, 4>& pad4, std::optional<std::int64_t> leg_security_id, std::optional<Decimal> leg_price, std::optional<std::int32_t> leg_ratio_qty, std::optional<LegSecurityType> leg_security_type, std::optional<LegSide> leg_side, const std::array<std::byte, 2>& pad2);

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

    // Leg Price:
    std::optional<Decimal> leg_price() const;
    void set_leg_price(std::optional<Decimal> value);

    // Leg Ratio Qty:
    std::optional<std::int32_t> leg_ratio_qty() const;
    void set_leg_ratio_qty(std::optional<std::int32_t> value);

    // Leg Security Type:
    std::optional<LegSecurityType> leg_security_type() const;
    void set_leg_security_type(std::optional<LegSecurityType> value);

    // Leg Side:
    std::optional<LegSide> leg_side() const;
    void set_leg_side(std::optional<LegSide> value);

    // Pad2:
    const std::array<std::byte, 2>& pad2() const;
    std::array<std::byte, 2>& pad2();
    void set_pad2(const std::array<std::byte, 2>& value);

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
    std::optional<Decimal> leg_price_{};
    std::optional<std::int32_t> leg_ratio_qty_{};
    std::optional<LegSecurityType> leg_security_type_{};
    std::optional<LegSide> leg_side_{};
    std::array<std::byte, 2> pad2_{};
};

std::ostream& operator<<(std::ostream& out, const InstrmtLegGrpComp& value);

} // namespace eurex::t7::eobi::fbe::v13_0
