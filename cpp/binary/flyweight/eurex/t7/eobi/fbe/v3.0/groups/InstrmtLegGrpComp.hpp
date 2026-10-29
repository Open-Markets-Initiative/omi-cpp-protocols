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

namespace eurex::t7::eobi::fbe::v3_0 {

class InstrmtLegGrpComp {
  public:
    static constexpr const char* name = "InstrmtLegGrpComp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrmtLegGrpComp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrmtLegGrpComp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::optional<std::int32_t> leg_symbol() const { return wire::nullable(wire::read_i32_le(at(0)), static_cast<std::int32_t>(0x80000000LL)); }

    std::span<const std::byte, 4> pad4() const { return bytes_.subspan(4).template first<4>(); }

    std::optional<std::int64_t> leg_security_id() const { return wire::nullable(wire::read_i64_le(at(8)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::int32_t> leg_ratio_qty() const { return wire::nullable(wire::read_i32_le(at(16)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<LegSide> leg_side() const { return wire::nullable_enum<LegSide>(wire::read_u8(at(20)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 3> pad3() const { return bytes_.subspan(21).template first<3>(); }

    void print(std::ostream& out) const {
        out << "InstrmtLegGrpComp{";
        out << "leg_symbol=";
        print::optional(out, leg_symbol());
        out << ", pad4=";
        print::hex(out, pad4().data(), pad4().size());
        out << ", leg_security_id=";
        print::optional(out, leg_security_id());
        out << ", leg_ratio_qty=";
        print::optional(out, leg_ratio_qty());
        out << ", leg_side=";
        print::optional(out, leg_side());
        out << ", pad3=";
        print::hex(out, pad3().data(), pad3().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrmtLegGrpComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v3_0
