#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace lseg::millennium::level2::mitch::v11_9 {

// Order Book Clear Flags
class OrderBookClearFlags {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    OrderBookClearFlags() = default;
    explicit OrderBookClearFlags(std::uint8_t raw);

    // Unused 5: Unused
    std::uint8_t unused_5() const;
    void set_unused_5(std::uint8_t value);

    // Firm Quote: Firm Quote
    bool firm_quote() const;
    void set_firm_quote(bool value);

    // Private Rfq: Private RFQ
    bool private_rfq() const;
    void set_private_rfq(bool value);

    // Unused 1: Unused
    bool unused_1() const;
    void set_unused_1(bool value);

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

    bool operator==(const OrderBookClearFlags& other) const;
    bool operator!=(const OrderBookClearFlags& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const OrderBookClearFlags& value);

} // namespace lseg::millennium::level2::mitch::v11_9
