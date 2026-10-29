#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ImbalanceDirection.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CrossType.hpp"
#include "../enums/PriceVariationIndicator.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// NASDAQ disseminates NOII data at 5-second intervals in the minutes leading up to the NASDAQ
// Opening Cross and NASDAQ Closing Cross.
class PayloadNetOrderImbalanceIndicatorMessage {
  public:
    static constexpr const char* name = "PayloadNetOrderImbalanceIndicatorMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadNetOrderImbalanceIndicatorMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadNetOrderImbalanceIndicatorMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 41;
    static constexpr std::size_t fixed_size = 41;
    std::size_t encoded_size() const { return 41; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t paired_shares() const { return wire::read_u64_be(at(4)); }

    std::uint64_t imbalance_shares() const { return wire::read_u64_be(at(12)); }

    ImbalanceDirection imbalance_direction() const { return static_cast<ImbalanceDirection>(wire::read_char(at(20))); }

    std::string_view stock() const { return view::text(at(21), 6, ' '); }

    Decimal far_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(27))), -4); }

    Decimal near_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(31))), -4); }

    Decimal current_reference_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(35))), -4); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(39))); }

    PriceVariationIndicator price_variation_indicator() const { return static_cast<PriceVariationIndicator>(wire::read_char(at(40))); }

    void print(std::ostream& out) const {
        out << "PayloadNetOrderImbalanceIndicatorMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", paired_shares=";
        out << paired_shares();
        out << ", imbalance_shares=";
        out << imbalance_shares();
        out << ", imbalance_direction=";
        out << imbalance_direction();
        out << ", stock=";
        print::text(out, stock());
        out << ", far_price=";
        out << far_price();
        out << ", near_price=";
        out << near_price();
        out << ", current_reference_price=";
        out << current_reference_price();
        out << ", cross_type=";
        out << cross_type();
        out << ", price_variation_indicator=";
        out << price_variation_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadNetOrderImbalanceIndicatorMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
