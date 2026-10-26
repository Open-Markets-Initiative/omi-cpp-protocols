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
#include "../enums/CrossType.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// This message will also be used to report all executions within a price improvement (PRISM)
// auction.
class OptionsCrossTradeMessage {
  public:
    static constexpr const char* name = "OptionsCrossTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsCrossTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsCrossTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 29;
    static constexpr std::size_t fixed_size = 29;
    std::size_t encoded_size() const { return 29; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(8)); }

    std::uint32_t cross_number() const { return wire::read_u32_be(at(12)); }

    std::uint32_t match_number() const { return wire::read_u32_be(at(16)); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(20))); }

    Decimal price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(21))), -4); }

    std::uint32_t volume_long() const { return wire::read_u32_be(at(25)); }

    void print(std::ostream& out) const {
        out << "OptionsCrossTradeMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", option_id=";
        out << option_id();
        out << ", cross_number=";
        out << cross_number();
        out << ", match_number=";
        out << match_number();
        out << ", cross_type=";
        out << cross_type();
        out << ", price_long=";
        out << price_long();
        out << ", volume_long=";
        out << volume_long();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsCrossTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
