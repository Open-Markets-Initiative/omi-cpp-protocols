#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/LegSide.hpp"
#include "../enums/LegSecurityType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class ComplexSeriesIndexMappingLeg {
  public:
    static constexpr const char* name = "ComplexSeriesIndexMappingLeg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexSeriesIndexMappingLeg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexSeriesIndexMappingLeg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(0)); }

    std::uint16_t leg_ratio_qty() const { return wire::read_u16_le(at(4)); }

    LegSide leg_side() const { return static_cast<LegSide>(wire::read_char(at(6))); }

    LegSecurityType leg_security_type() const { return static_cast<LegSecurityType>(wire::read_char(at(7))); }

    void print(std::ostream& out) const {
        out << "ComplexSeriesIndexMappingLeg{";
        out << "symbol_index=";
        out << symbol_index();
        out << ", leg_ratio_qty=";
        out << leg_ratio_qty();
        out << ", leg_side=";
        out << leg_side();
        out << ", leg_security_type=";
        out << leg_security_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexSeriesIndexMappingLeg& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
