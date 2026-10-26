#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Additional order attributes
class OrderAttributes {
  public:
    static constexpr const char* name = "OrderAttributes";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderAttributes(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 2;
    static constexpr std::size_t fixed_size = 2;
    std::size_t encoded_size() const { return 2; }

    std::uint16_t raw() const { return wire::read_u16_be(bytes_.data()); }

    bool force() const { return (raw() & static_cast<std::uint16_t>(0x1)) != 0; }

    bool short_sell() const { return (raw() & static_cast<std::uint16_t>(0x2)) != 0; }

    bool market_bid() const { return (raw() & static_cast<std::uint16_t>(0x4)) != 0; }

    bool price_stabilization() const { return (raw() & static_cast<std::uint16_t>(0x8)) != 0; }

    bool override_crossing() const { return (raw() & static_cast<std::uint16_t>(0x10)) != 0; }

    bool undisclosed() const { return (raw() & static_cast<std::uint16_t>(0x20)) != 0; }

    void print(std::ostream& out) const {
        out << "OrderAttributes{";
        out << "force=";
        out << (force() ? "true" : "false");
        out << ", short_sell=";
        out << (short_sell() ? "true" : "false");
        out << ", market_bid=";
        out << (market_bid() ? "true" : "false");
        out << ", price_stabilization=";
        out << (price_stabilization() ? "true" : "false");
        out << ", override_crossing=";
        out << (override_crossing() ? "true" : "false");
        out << ", undisclosed=";
        out << (undisclosed() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderAttributes& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
