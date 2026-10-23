#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SourceVenue.hpp"
#include "../enums/StatisticType.hpp"
#include "../common/Decimal.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/AuctionInfo.hpp"
#include "../enums/OpeningClosingPriceIndicator.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Contains a set of statistics that are not updated frequently.
class StatisticsUpdateMessage {
  public:
    static constexpr const char* name = "StatisticsUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StatisticsUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StatisticsUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 47;
    static constexpr std::size_t fixed_size = 47;
    std::size_t encoded_size() const { return 47; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint64_t instrument() const { return wire::read_u64_le(at(8)); }

    SourceVenue source_venue() const { return static_cast<SourceVenue>(wire::read_u16_le(at(16))); }

    StatisticType statistic_type() const { return static_cast<StatisticType>(wire::read_u16_le(at(18))); }

    Decimal statistic_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(20))), -8); }

    Decimal statistic_size() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(28))), -8); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(36))); }

    Decimal imbalance_quantity() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(37))), -8); }

    AuctionInfo auction_info() const { return static_cast<AuctionInfo>(wire::read_char(at(45))); }

    OpeningClosingPriceIndicator opening_closing_price_indicator() const { return static_cast<OpeningClosingPriceIndicator>(wire::read_char(at(46))); }

    void print(std::ostream& out) const {
        out << "StatisticsUpdateMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", instrument=";
        out << instrument();
        out << ", source_venue=";
        out << source_venue();
        out << ", statistic_type=";
        out << statistic_type();
        out << ", statistic_price=";
        out << statistic_price();
        out << ", statistic_size=";
        out << statistic_size();
        out << ", auction_type=";
        out << auction_type();
        out << ", imbalance_quantity=";
        out << imbalance_quantity();
        out << ", auction_info=";
        out << auction_info();
        out << ", opening_closing_price_indicator=";
        out << opening_closing_price_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StatisticsUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
