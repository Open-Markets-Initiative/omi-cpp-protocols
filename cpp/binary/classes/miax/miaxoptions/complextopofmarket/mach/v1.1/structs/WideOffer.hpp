#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/OfferCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Wide Offer
class WideOffer {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 17;

    WideOffer() = default;
    WideOffer(Decimal wide_offer_price, std::uint32_t wide_offer_size, const std::array<std::byte, 4>& reserved_4, OfferCondition offer_condition);

    // Wide Offer Price: MIAX Best Offer net price
    Decimal wide_offer_price() const;
    void set_wide_offer_price(Decimal value);

    // Wide Offer Size: Aggregate size at MIAX Best Bid Net Price
    std::uint32_t wide_offer_size() const;
    void set_wide_offer_size(std::uint32_t value);

    // Reserved 4: Reserved for future use
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

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

    bool operator==(const WideOffer& other) const;
    bool operator!=(const WideOffer& other) const;

  private:
    Decimal wide_offer_price_{ 0, -4 };
    std::uint32_t wide_offer_size_{};
    std::array<std::byte, 4> reserved_4_{};
    OfferCondition offer_condition_{};
};

std::ostream& operator<<(std::ostream& out, const WideOffer& value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
