// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: groups/InstrumentLeg.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Complex Strategy Number of Legs
class InstrumentLeg {
  public:
    static constexpr const char* name = "InstrumentLeg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentLeg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentLeg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(0)); }

    std::int32_t leg_ratio_and_side() const { return wire::read_i32_le(at(4)); }

    std::uint32_t maturity_month_year() const { return wire::read_u32_le(at(8)); }

    std::span<const std::byte, 8> reserved_8() const { return bytes_.subspan(12).template first<8>(); }

    void print(std::ostream& out) const {
        out << "InstrumentLeg{";
        out << "instrument_id=";
        out << instrument_id();
        out << ", leg_ratio_and_side=";
        out << leg_ratio_and_side();
        out << ", maturity_month_year=";
        out << maturity_month_year();
        out << ", reserved_8=";
        print::hex(out, reserved_8().data(), reserved_8().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentLeg& value) {
    value.print(out);
    return out;
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
