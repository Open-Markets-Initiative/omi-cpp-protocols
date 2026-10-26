#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/LegSecurityType.hpp"
#include "../enums/LegSide.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// noLegs
class DeprecatedLegsGroup {
  public:
    static constexpr const char* name = "DeprecatedLegsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DeprecatedLegsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DeprecatedLegsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 38;
    static constexpr std::size_t fixed_size = 38;
    std::size_t encoded_size() const { return 38; }

    std::uint64_t leg_security_id() const { return wire::read_u64_le(at(0)); }

    std::optional<Decimal> leg_ratio_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -7); }

    LegSecurityType leg_security_type() const { return static_cast<LegSecurityType>(wire::read_u8(at(16))); }

    LegSide leg_side() const { return static_cast<LegSide>(wire::read_u8(at(17))); }

    std::string_view leg_symbol() const { return view::text(at(18), 20, '\0'); }

    void print(std::ostream& out) const {
        out << "DeprecatedLegsGroup{";
        out << "leg_security_id=";
        out << leg_security_id();
        out << ", leg_ratio_qty=";
        print::optional(out, leg_ratio_qty());
        out << ", leg_security_type=";
        out << leg_security_type();
        out << ", leg_side=";
        out << leg_side();
        out << ", leg_symbol=";
        print::text(out, leg_symbol());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DeprecatedLegsGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
