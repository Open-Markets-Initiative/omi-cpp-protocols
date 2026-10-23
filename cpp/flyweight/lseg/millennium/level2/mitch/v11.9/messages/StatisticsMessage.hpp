#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/StatisticType.hpp"
#include "../enums/OpenClosePriceIndicator.hpp"
#include "../bitfields/StatisticsReserved.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Used to disseminate official Opening and Closing prices
class StatisticsMessage {
  public:
    static constexpr const char* name = "StatisticsMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StatisticsMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StatisticsMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 21;
    static constexpr std::size_t fixed_size = 21;
    std::size_t encoded_size() const { return 21; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(4)); }

    std::span<const std::byte, 1> reserved_a() const { return bytes_.subspan(8).template first<1>(); }

    std::span<const std::byte, 1> reserved_b() const { return bytes_.subspan(9).template first<1>(); }

    StatisticType statistic_type() const { return static_cast<StatisticType>(wire::read_char(at(10))); }

    std::int64_t price() const { return wire::read_i64_le(at(11)); }

    OpenClosePriceIndicator open_close_price_indicator() const { return static_cast<OpenClosePriceIndicator>(wire::read_char(at(19))); }

    StatisticsReserved statistics_reserved() const { return StatisticsReserved{ bytes_.subspan(20) }; }

    void print(std::ostream& out) const {
        out << "StatisticsMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", reserved_a=";
        print::hex(out, reserved_a().data(), reserved_a().size());
        out << ", reserved_b=";
        print::hex(out, reserved_b().data(), reserved_b().size());
        out << ", statistic_type=";
        out << statistic_type();
        out << ", price=";
        out << price();
        out << ", open_close_price_indicator=";
        out << open_close_price_indicator();
        out << ", statistics_reserved=";
        statistics_reserved().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StatisticsMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
