#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/OfferCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Compact Offer
class CompactOffer {
  public:
    static constexpr const char* name = "CompactOffer";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CompactOffer(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CompactOffer has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 7;
    static constexpr std::size_t fixed_size = 7;
    std::size_t encoded_size() const { return 7; }

    Decimal compact_offer_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i16_le(at(0))), -2); }

    std::uint16_t compact_offer_size() const { return wire::read_u16_le(at(2)); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(4).template first<2>(); }

    OfferCondition offer_condition() const { return static_cast<OfferCondition>(wire::read_char(at(6))); }

    void print(std::ostream& out) const {
        out << "CompactOffer{";
        out << "compact_offer_price=";
        out << compact_offer_price();
        out << ", compact_offer_size=";
        out << compact_offer_size();
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << ", offer_condition=";
        out << offer_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CompactOffer& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
