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
#include "../common/Day.hpp"
#include "../enums/ImbalanceDirection.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CrossType.hpp"
#include "../enums/PriceVariationIndicator.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// NASDAQ disseminates NOII data
class FilePayloadNetOrderImbalanceIndicatorMessage {
  public:
    static constexpr const char* name = "FilePayloadNetOrderImbalanceIndicatorMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FilePayloadNetOrderImbalanceIndicatorMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FilePayloadNetOrderImbalanceIndicatorMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 49;
    static constexpr std::size_t fixed_size = 49;
    std::size_t encoded_size() const { return 49; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint64_t paired_shares() const { return wire::read_u64_be(at(10)); }

    std::uint64_t imbalance_shares() const { return wire::read_u64_be(at(18)); }

    ImbalanceDirection imbalance_direction() const { return static_cast<ImbalanceDirection>(wire::read_char(at(26))); }

    std::string_view stock() const { return view::text(at(27), 8, ' '); }

    Decimal far_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(35))), -4); }

    Decimal near_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(39))), -4); }

    Decimal current_reference_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(43))), -4); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(47))); }

    PriceVariationIndicator price_variation_indicator() const { return static_cast<PriceVariationIndicator>(wire::read_char(at(48))); }

    void print(std::ostream& out) const {
        out << "FilePayloadNetOrderImbalanceIndicatorMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
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

inline std::ostream& operator<<(std::ostream& out, const FilePayloadNetOrderImbalanceIndicatorMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
