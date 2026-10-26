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
#include "../enums/CrossType.hpp"
#include "../enums/CrossLevel.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Auction on demand order imbalance indicator
class MoiiMessage {
  public:
    static constexpr const char* name = "MoiiMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MoiiMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MoiiMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint64_t paired_quantity() const { return wire::read_u64_be(at(10)); }

    std::uint32_t order_book() const { return wire::read_u32_be(at(18)); }

    Decimal equilibrium_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(22))), -4); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(26))); }

    CrossLevel cross_level() const { return static_cast<CrossLevel>(wire::read_char(at(27))); }

    void print(std::ostream& out) const {
        out << "MoiiMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "UTC");
        out << ", tracking_number=";
        out << tracking_number();
        out << ", paired_quantity=";
        out << paired_quantity();
        out << ", order_book=";
        out << order_book();
        out << ", equilibrium_price=";
        out << equilibrium_price();
        out << ", cross_type=";
        out << cross_type();
        out << ", cross_level=";
        out << cross_level();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MoiiMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
