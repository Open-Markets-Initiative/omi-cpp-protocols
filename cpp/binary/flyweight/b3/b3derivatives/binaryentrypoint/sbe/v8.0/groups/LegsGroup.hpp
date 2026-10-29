#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/LegSide.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// noLegs
class LegsGroup {
  public:
    static constexpr const char* name = "LegsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LegsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LegsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 30;
    static constexpr std::size_t fixed_size = 30;
    std::size_t encoded_size() const { return 30; }

    std::string_view leg_symbol() const { return view::text(at(0), 20, '\0'); }

    Decimal leg_ratio_qty() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(20))), -7); }

    LegSide leg_side() const { return static_cast<LegSide>(wire::read_char(at(28))); }

    std::span<const std::byte, 1> padding_1() const { return bytes_.subspan(29).template first<1>(); }

    void print(std::ostream& out) const {
        out << "LegsGroup{";
        out << "leg_symbol=";
        print::text(out, leg_symbol());
        out << ", leg_ratio_qty=";
        out << leg_ratio_qty();
        out << ", leg_side=";
        out << leg_side();
        out << ", padding_1=";
        print::hex(out, padding_1().data(), padding_1().size());
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

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
