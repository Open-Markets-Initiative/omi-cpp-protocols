#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/BidCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Wide Bid
class WideBid {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 17;

    WideBid() = default;
    WideBid(Decimal wide_bid_price, std::uint32_t wide_bid_size, const std::array<std::byte, 4>& reserved_4, BidCondition bid_condition);

    // Wide Bid Price: MIAX Best Bid net price.
    Decimal wide_bid_price() const;
    void set_wide_bid_price(Decimal value);

    // Wide Bid Size: Aggregate size at MIAX Best Bid Net Price
    std::uint32_t wide_bid_size() const;
    void set_wide_bid_size(std::uint32_t value);

    // Reserved 4: Reserved for future use
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Bid Condition: Top of Strategy Market Quote Conditions
    BidCondition bid_condition() const;
    void set_bid_condition(BidCondition value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const WideBid& other) const;
    bool operator!=(const WideBid& other) const;

  private:
    Decimal wide_bid_price_{ 0, -4 };
    std::uint32_t wide_bid_size_{};
    std::array<std::byte, 4> reserved_4_{};
    BidCondition bid_condition_{};
};

std::ostream& operator<<(std::ostream& out, const WideBid& value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
