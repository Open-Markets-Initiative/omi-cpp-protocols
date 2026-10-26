#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SideLeg.hpp"
#include "../common/Decimal.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Bundle Leg
class BundleLeg {
  public:
    static constexpr const char* name = "BundleLeg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BundleLeg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BundleLeg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::uint32_t tradeable_instrument_id_leg() const { return wire::read_u32_be(at(0)); }

    SideLeg side_leg() const { return static_cast<SideLeg>(wire::read_char(at(4))); }

    std::uint32_t ratio_leg() const { return wire::read_u32_be(at(5)); }

    Decimal price_leg() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(9))), -2); }

    void print(std::ostream& out) const {
        out << "BundleLeg{";
        out << "tradeable_instrument_id_leg=";
        out << tradeable_instrument_id_leg();
        out << ", side_leg=";
        out << side_leg();
        out << ", ratio_leg=";
        out << ratio_leg();
        out << ", price_leg=";
        out << price_leg();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BundleLeg& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
