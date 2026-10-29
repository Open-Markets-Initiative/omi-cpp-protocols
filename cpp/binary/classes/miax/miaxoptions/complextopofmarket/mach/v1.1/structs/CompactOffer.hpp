#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/OfferCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Compact Offer
class CompactOffer {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 7;

    CompactOffer() = default;
    CompactOffer(Decimal compact_offer_price, std::uint16_t compact_offer_size, const std::array<std::byte, 2>& reserved_2, OfferCondition offer_condition);

    // Compact Offer Price: MIAX Best Offer net price
    Decimal compact_offer_price() const;
    void set_compact_offer_price(Decimal value);

    // Compact Offer Size: Aggregate size at MIAX Best Bid Net Price
    std::uint16_t compact_offer_size() const;
    void set_compact_offer_size(std::uint16_t value);

    // Reserved 2: Reserved for future use
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

    // Offer Condition: Top of Strategy Market Quote Conditions
    OfferCondition offer_condition() const;
    void set_offer_condition(OfferCondition value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const CompactOffer& other) const;
    bool operator!=(const CompactOffer& other) const;

  private:
    Decimal compact_offer_price_{ 0, -2 };
    std::uint16_t compact_offer_size_{};
    std::array<std::byte, 2> reserved_2_{};
    OfferCondition offer_condition_{};
};

std::ostream& operator<<(std::ostream& out, const CompactOffer& value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
