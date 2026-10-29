#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Extended Quote Information
class ExtendedQuoteFlags {
  public:
    static constexpr const char* name = "ExtendedQuoteFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExtendedQuoteFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool quote_saturated() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool bid_auto_ex() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool offer_auto_ex() const { return (raw() & static_cast<std::uint8_t>(0x4)) != 0; }

    bool nms_conditional_quote() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    void print(std::ostream& out) const {
        out << "ExtendedQuoteFlags{";
        out << "quote_saturated=";
        out << (quote_saturated() ? "true" : "false");
        out << ", bid_auto_ex=";
        out << (bid_auto_ex() ? "true" : "false");
        out << ", offer_auto_ex=";
        out << (offer_auto_ex() ? "true" : "false");
        out << ", nms_conditional_quote=";
        out << (nms_conditional_quote() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExtendedQuoteFlags& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
