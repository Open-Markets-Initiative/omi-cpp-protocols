#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Defines the order-book types that are allowed for the instrument
class AllowedBookTypes {
  public:
    static constexpr const char* name = "AllowedBookTypes";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AllowedBookTypes(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool firm_quote_book() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool off_book() const { return (raw() & static_cast<std::uint8_t>(0x4)) != 0; }

    bool electronic_order_book() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    bool private_rfq() const { return (raw() & static_cast<std::uint8_t>(0x10)) != 0; }

    void print(std::ostream& out) const {
        out << "AllowedBookTypes{";
        out << "firm_quote_book=";
        out << (firm_quote_book() ? "true" : "false");
        out << ", off_book=";
        out << (off_book() ? "true" : "false");
        out << ", electronic_order_book=";
        out << (electronic_order_book() ? "true" : "false");
        out << ", private_rfq=";
        out << (private_rfq() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AllowedBookTypes& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
