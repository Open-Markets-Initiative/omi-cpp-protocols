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

// Wide Offer
class WideOffer {
  public:
    static constexpr const char* name = "WideOffer";

    // the bytes it reads, which it does not own: they must outlive it
    explicit WideOffer(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every WideOffer has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    Decimal wide_offer_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(0))), -4); }

    std::uint32_t wide_offer_size() const { return wire::read_u32_le(at(8)); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(12).template first<4>(); }

    OfferCondition offer_condition() const { return static_cast<OfferCondition>(wire::read_char(at(16))); }

    void print(std::ostream& out) const {
        out << "WideOffer{";
        out << "wide_offer_price=";
        out << wide_offer_price();
        out << ", wide_offer_size=";
        out << wide_offer_size();
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", offer_condition=";
        out << offer_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const WideOffer& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
