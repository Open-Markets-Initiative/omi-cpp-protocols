#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/LegSide.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Complex Strategy Number of Legs
class LegDefinition {
  public:
    static constexpr const char* name = "LegDefinition";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LegDefinition(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LegDefinition has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 15;
    static constexpr std::size_t fixed_size = 15;
    std::size_t encoded_size() const { return 15; }

    std::uint32_t product_id() const { return wire::read_u32_le(at(0)); }

    std::uint16_t leg_ratio_qty() const { return wire::read_u16_le(at(4)); }

    LegSide leg_side() const { return static_cast<LegSide>(wire::read_char(at(6))); }

    std::span<const std::byte, 8> reserved_8() const { return bytes_.subspan(7).template first<8>(); }

    void print(std::ostream& out) const {
        out << "LegDefinition{";
        out << "product_id=";
        out << product_id();
        out << ", leg_ratio_qty=";
        out << leg_ratio_qty();
        out << ", leg_side=";
        out << leg_side();
        out << ", reserved_8=";
        print::hex(out, reserved_8().data(), reserved_8().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LegDefinition& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
