#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Defines the order-book types that are allowed for the instrument
class AllowedBookTypes {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    AllowedBookTypes() = default;
    explicit AllowedBookTypes(std::uint8_t raw);

    // Firm Quote Book: Firm Quote Book
    bool firm_quote_book() const;
    void set_firm_quote_book(bool value);

    // Offbook: Off-book
    bool offbook() const;
    void set_offbook(bool value);

    // Electronic Order Book: Electronic Order Book
    bool electronic_order_book() const;
    void set_electronic_order_book(bool value);

    // Private Rfq: Private RFQ
    bool private_rfq() const;
    void set_private_rfq(bool value);

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

    bool operator==(const AllowedBookTypes& other) const;
    bool operator!=(const AllowedBookTypes& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const AllowedBookTypes& value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
