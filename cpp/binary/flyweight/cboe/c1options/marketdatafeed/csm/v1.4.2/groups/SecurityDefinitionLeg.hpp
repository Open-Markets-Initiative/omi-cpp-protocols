#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/LegSide.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Security Definition Leg
class SecurityDefinitionLeg {
  public:
    static constexpr const char* name = "SecurityDefinitionLeg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityDefinitionLeg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityDefinitionLeg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    std::uint32_t leg_ratio_qty() const { return wire::read_u32_be(at(0)); }

    std::uint32_t leg_security_id() const { return wire::read_u32_be(at(4)); }

    LegSide leg_side() const { return static_cast<LegSide>(wire::read_char(at(8))); }

    void print(std::ostream& out) const {
        out << "SecurityDefinitionLeg{";
        out << "leg_ratio_qty=";
        out << leg_ratio_qty();
        out << ", leg_security_id=";
        out << leg_security_id();
        out << ", leg_side=";
        out << leg_side();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityDefinitionLeg& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
