#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace lseg::millennium::level2::mitch::v11_9 {

// Order Modified Flags
class OrderModifiedFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    OrderModifiedFlags() = default;
    explicit OrderModifiedFlags(std::uint8_t raw);

    // Priority Flag: Priority Flag
    bool priority_flag() const;
    void set_priority_flag(bool value);

    // Unused 4: Unused
    std::uint8_t unused_4() const;
    void set_unused_4(std::uint8_t value);

    // Firm Quote: Firm Quote
    bool firm_quote() const;
    void set_firm_quote(bool value);

    // Unused 2: Unused
    std::uint8_t unused_2() const;
    void set_unused_2(std::uint8_t value);

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

    bool operator==(const OrderModifiedFlags& other) const;
    bool operator!=(const OrderModifiedFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const OrderModifiedFlags& value);

} // namespace lseg::millennium::level2::mitch::v11_9
