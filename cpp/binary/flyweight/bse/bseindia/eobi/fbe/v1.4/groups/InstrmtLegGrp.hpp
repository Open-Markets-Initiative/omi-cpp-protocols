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

namespace bse::bseindia::eobi::fbe::v1_4 {

// Leg definitions repeated NoLegs times in the Add Complex Instrument Message.
class InstrmtLegGrp {
  public:
    static constexpr const char* name = "InstrmtLegGrp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrmtLegGrp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrmtLegGrp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::int64_t leg_security_id() const { return wire::read_i64_le(at(0)); }

    std::optional<std::int32_t> leg_ratio_qty() const { return wire::nullable(wire::read_i32_le(at(8)), static_cast<std::int32_t>(-2147483648LL)); }

    LegSide leg_side() const { return static_cast<LegSide>(wire::read_u8(at(12))); }

    std::span<const std::byte, 3> pad_3() const { return bytes_.subspan(13).template first<3>(); }

    void print(std::ostream& out) const {
        out << "InstrmtLegGrp{";
        out << "leg_security_id=";
        out << leg_security_id();
        out << ", leg_ratio_qty=";
        print::optional(out, leg_ratio_qty());
        out << ", leg_side=";
        out << leg_side();
        out << ", pad_3=";
        print::hex(out, pad_3().data(), pad_3().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrmtLegGrp& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
