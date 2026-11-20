// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: groups/CopOrder.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class CopOrder {
  public:
    static constexpr const char* name = "CopOrder";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CopOrder(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CopOrder has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    std::optional<std::uint16_t> broker_number() const { return wire::nullable(wire::read_u16_le(at(0)), static_cast<std::uint16_t>(0ULL)); }

    std::optional<std::uint64_t> order_id() const { return wire::nullable(wire::read_u64_le(at(2)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "CopOrder{";
        out << "broker_number=";
        print::optional(out, broker_number());
        out << ", order_id=";
        print::optional(out, order_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CopOrder& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
