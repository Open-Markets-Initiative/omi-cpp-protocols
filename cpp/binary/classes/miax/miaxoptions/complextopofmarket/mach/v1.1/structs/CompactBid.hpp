#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/BidCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Compact Bid
class CompactBid {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 7;

    CompactBid() = default;
    CompactBid(Decimal compact_bid_price, std::uint16_t compact_bid_size, const std::array<std::byte, 2>& reserved_2, BidCondition bid_condition);

    // Compact Bid Price: MIAX Best Bid net price.
    Decimal compact_bid_price() const;
    void set_compact_bid_price(Decimal value);

    // Compact Bid Size: Aggregate size at MIAX Best Bid Net Price
    std::uint16_t compact_bid_size() const;
    void set_compact_bid_size(std::uint16_t value);

    // Reserved 2: Reserved for future use
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

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

    bool operator==(const CompactBid& other) const;
    bool operator!=(const CompactBid& other) const;

  private:
    Decimal compact_bid_price_{ 0, -2 };
    std::uint16_t compact_bid_size_{};
    std::array<std::byte, 2> reserved_2_{};
    BidCondition bid_condition_{};
};

std::ostream& operator<<(std::ostream& out, const CompactBid& value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
