#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/LegSide.hpp"
#include "../common/Decimal.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of Leg entries
class LegsGroup {
  public:
    static constexpr const char* name = "LegsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LegsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LegsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    std::int32_t leg_security_id() const { return wire::read_i32_le(at(0)); }

    LegSide leg_side() const { return static_cast<LegSide>(wire::read_u8(at(4))); }

    std::int8_t leg_ratio_qty() const { return wire::read_i8(at(5)); }

    std::optional<Decimal> leg_price() const { return wire::nullable_decimal(wire::read_i64_le(at(6)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> leg_option_delta() const { return wire::nullable_decimal(wire::read_i32_le(at(14)), static_cast<std::int32_t>(2147483647LL), -4); }

    void print(std::ostream& out) const {
        out << "LegsGroup{";
        out << "leg_security_id=";
        out << leg_security_id();
        out << ", leg_side=";
        out << leg_side();
        out << ", leg_ratio_qty=";
        out << static_cast<int>(leg_ratio_qty());
        out << ", leg_price=";
        print::optional(out, leg_price());
        out << ", leg_option_delta=";
        print::optional(out, leg_option_delta());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LegsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
