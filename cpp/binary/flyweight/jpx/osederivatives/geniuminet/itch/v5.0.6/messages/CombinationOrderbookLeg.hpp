#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/LegSide.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Mapping between a combination orderbook and its leg orderbooks.
class CombinationOrderbookLeg {
  public:
    static constexpr const char* name = "CombinationOrderbookLeg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CombinationOrderbookLeg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CombinationOrderbookLeg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t combination_orderbook_id() const { return wire::read_u32_be(at(4)); }

    std::uint32_t leg_orderbook_id() const { return wire::read_u32_be(at(8)); }

    LegSide leg_side() const { return static_cast<LegSide>(wire::read_char(at(12))); }

    std::uint32_t leg_ratio() const { return wire::read_u32_be(at(13)); }

    void print(std::ostream& out) const {
        out << "CombinationOrderbookLeg{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", combination_orderbook_id=";
        out << combination_orderbook_id();
        out << ", leg_orderbook_id=";
        out << leg_orderbook_id();
        out << ", leg_side=";
        out << leg_side();
        out << ", leg_ratio=";
        out << leg_ratio();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CombinationOrderbookLeg& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
