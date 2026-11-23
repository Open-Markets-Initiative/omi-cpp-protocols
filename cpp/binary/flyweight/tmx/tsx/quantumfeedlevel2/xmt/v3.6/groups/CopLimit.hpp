// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: groups/CopLimit.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class CopLimit {
  public:
    static constexpr const char* name = "CopLimit";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CopLimit(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CopLimit has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    std::optional<std::uint16_t> broker_number() const { return wire::nullable(wire::read_u16_le(at(0)), static_cast<std::uint16_t>(0ULL)); }

    std::optional<std::uint64_t> order_id() const { return wire::nullable(wire::read_u64_le(at(2)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_u64_le(at(10)), static_cast<std::uint64_t>(0ULL), -6); }

    void print(std::ostream& out) const {
        out << "CopLimit{";
        out << "broker_number=";
        print::optional(out, broker_number());
        out << ", order_id=";
        print::optional(out, order_id());
        out << ", price=";
        print::optional(out, price());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CopLimit& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
