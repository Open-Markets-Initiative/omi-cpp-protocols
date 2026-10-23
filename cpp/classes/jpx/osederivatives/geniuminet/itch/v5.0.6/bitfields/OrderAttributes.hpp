#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Additional order attributes
class OrderAttributes {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 2;

    OrderAttributes() = default;
    explicit OrderAttributes(std::uint16_t raw);

    // Force: Force
    bool force() const;
    void set_force(bool value);

    // Short Sell: Short Sell
    bool short_sell() const;
    void set_short_sell(bool value);

    // Market Bid: Market Bid
    bool market_bid() const;
    void set_market_bid(bool value);

    // Price Stabilization: Price Stabilization
    bool price_stabilization() const;
    void set_price_stabilization(bool value);

    // Override Crossing: Override Crossing
    bool override_crossing() const;
    void set_override_crossing(bool value);

    // Undisclosed: Undisclosed
    bool undisclosed() const;
    void set_undisclosed(bool value);

    // The whole bitfield as its wire integer
    std::uint16_t raw() const;
    void set_raw(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const OrderAttributes& other) const;
    bool operator!=(const OrderAttributes& other) const;

  private:
    std::uint16_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const OrderAttributes& value);

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
