#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/LegSecurityType.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Leg for multi-leg strategies
class ComplexInstrumentLeg {
  public:
    static constexpr const char* name = "ComplexInstrumentLeg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexInstrumentLeg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexInstrumentLeg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::string_view leg_symbol() const { return view::text(at(0), 8, ' '); }

    std::int32_t leg_ratio() const { return wire::read_i32_le(at(8)); }

    LegSecurityType leg_security_type() const { return static_cast<LegSecurityType>(wire::read_char(at(12))); }

    void print(std::ostream& out) const {
        out << "ComplexInstrumentLeg{";
        out << "leg_symbol=";
        print::text(out, leg_symbol());
        out << ", leg_ratio=";
        out << leg_ratio();
        out << ", leg_security_type=";
        out << leg_security_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexInstrumentLeg& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
