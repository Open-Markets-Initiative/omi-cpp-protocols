#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/PosType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// noPositions
class PositionsGroup {
  public:
    static constexpr const char* name = "PositionsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PositionsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PositionsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    PosType pos_type() const { return static_cast<PosType>(wire::read_char(at(0))); }

    std::optional<std::uint64_t> long_qty_optional() const { return wire::nullable(wire::read_u64_le(at(1)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> short_qty() const { return wire::nullable(wire::read_u64_le(at(9)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "PositionsGroup{";
        out << "pos_type=";
        out << pos_type();
        out << ", long_qty_optional=";
        print::optional(out, long_qty_optional());
        out << ", short_qty=";
        print::optional(out, short_qty());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PositionsGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
