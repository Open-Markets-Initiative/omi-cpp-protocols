#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../enums/Side.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// noSides
class SidesGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    SidesGroup() = default;
    SidesGroup(Side side, std::optional<std::uint32_t> account);

    // Side: side
    Side side() const;
    void set_side(Side value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SidesGroup& other) const;
    bool operator!=(const SidesGroup& other) const;

  private:
    Side side_{};
    std::optional<std::uint32_t> account_{};
};

std::ostream& operator<<(std::ostream& out, const SidesGroup& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
