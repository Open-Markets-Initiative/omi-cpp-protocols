#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// The ticker message is used to send real time trade information
class ComplexStrategyTickerMessage {
  public:
    static constexpr const char* name = "ComplexStrategyTickerMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexStrategyTickerMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexStrategyTickerMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 51;
    static constexpr std::size_t fixed_size = 51;
    std::size_t encoded_size() const { return 51; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t strategy_id() const { return wire::read_u32_be(at(6)); }

    Decimal last_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(10))), -8); }

    std::uint32_t size() const { return wire::read_u32_be(at(18)); }

    std::uint32_t volume() const { return wire::read_u32_be(at(22)); }

    std::uint64_t high() const { return wire::read_u64_be(at(26)); }

    std::uint64_t low() const { return wire::read_u64_be(at(34)); }

    std::uint64_t first() const { return wire::read_u64_be(at(42)); }

    char trade_condition() const { return wire::read_char(at(50)); }

    void print(std::ostream& out) const {
        out << "ComplexStrategyTickerMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", strategy_id=";
        out << strategy_id();
        out << ", last_price=";
        out << last_price();
        out << ", size=";
        out << size();
        out << ", volume=";
        out << volume();
        out << ", high=";
        out << high();
        out << ", low=";
        out << low();
        out << ", first=";
        out << first();
        out << ", trade_condition=";
        print::character(out, trade_condition());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexStrategyTickerMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
