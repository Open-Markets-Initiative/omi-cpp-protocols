#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace lseg::millennium::level2::mitch::v11_9 {

// Indicates a trade cancellation or amendment
class PtModFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    PtModFlags() = default;
    explicit PtModFlags(std::uint8_t raw);

    // Canc: Cancel
    bool canc() const;
    void set_canc(bool value);

    // Amnd: Amended
    bool amnd() const;
    void set_amnd(bool value);

    // Unused 6: Unused
    std::uint8_t unused_6() const;
    void set_unused_6(std::uint8_t value);

    // The whole bitfield as its wire integer
    std::uint8_t raw() const;
    void set_raw(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const PtModFlags& other) const;
    bool operator!=(const PtModFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const PtModFlags& value);

} // namespace lseg::millennium::level2::mitch::v11_9
