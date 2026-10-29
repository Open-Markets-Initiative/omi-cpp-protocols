#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../enums/PosType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// noPositions
class PositionsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 17;

    PositionsGroup() = default;
    PositionsGroup(PosType pos_type, std::optional<std::uint64_t> long_qty_optional, std::optional<std::uint64_t> short_qty);

    // Pos Type: Used to identify the type of quantity.
    PosType pos_type() const;
    void set_pos_type(PosType value);

    // Long Qty Optional: Long Quantity.
    std::optional<std::uint64_t> long_qty_optional() const;
    void set_long_qty_optional(std::optional<std::uint64_t> value);

    // Short Qty: Short Quantity.
    std::optional<std::uint64_t> short_qty() const;
    void set_short_qty(std::optional<std::uint64_t> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const PositionsGroup& other) const;
    bool operator!=(const PositionsGroup& other) const;

  private:
    PosType pos_type_{};
    std::optional<std::uint64_t> long_qty_optional_{};
    std::optional<std::uint64_t> short_qty_{};
};

std::ostream& operator<<(std::ostream& out, const PositionsGroup& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
