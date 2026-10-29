#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

// Sale Condition Flags
class SaleConditionFlags {
  public:
    static constexpr const char* name = "SaleConditionFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SaleConditionFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool single_price_cross_trade() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    bool trade_through_exempt() const { return (raw() & static_cast<std::uint8_t>(0x10)) != 0; }

    bool odd_lot() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool extended_hours() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool intermarket_sweep() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "SaleConditionFlags{";
        out << "single_price_cross_trade=";
        out << (single_price_cross_trade() ? "true" : "false");
        out << ", trade_through_exempt=";
        out << (trade_through_exempt() ? "true" : "false");
        out << ", odd_lot=";
        out << (odd_lot() ? "true" : "false");
        out << ", extended_hours=";
        out << (extended_hours() ? "true" : "false");
        out << ", intermarket_sweep=";
        out << (intermarket_sweep() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SaleConditionFlags& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::tops::snap::v1_6
