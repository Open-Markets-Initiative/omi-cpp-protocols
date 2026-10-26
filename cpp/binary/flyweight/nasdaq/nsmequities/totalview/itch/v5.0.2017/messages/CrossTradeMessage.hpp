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
#include "../common/Decimal.hpp"
#include "../enums/CrossType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// Cross Trade message indicates that NASDAQ has completed its cross process for a specific
// security. NASDAQ sends out a Cross Trade message for all active issues in the system
// following the Opening, Closing and EMC cross events. Firms may use the Cross Trade message
// to determine when the cross for each security has been completed. (Note: For the halted /
// paused securities, firms should use the Trading Action message to determine when an issue
// has been released for trading.)
class CrossTradeMessage {
  public:
    static constexpr const char* name = "CrossTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CrossTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CrossTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 39;
    static constexpr std::size_t fixed_size = 39;
    std::size_t encoded_size() const { return 39; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint64_t cross_shares() const { return wire::read_u64_be(at(10)); }

    std::string_view stock() const { return view::text(at(18), 8, ' '); }

    Decimal cross_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(26))), -4); }

    std::uint64_t match_number() const { return wire::read_u64_be(at(30)); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(38))); }

    void print(std::ostream& out) const {
        out << "CrossTradeMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", cross_shares=";
        out << cross_shares();
        out << ", stock=";
        print::text(out, stock());
        out << ", cross_price=";
        out << cross_price();
        out << ", match_number=";
        out << match_number();
        out << ", cross_type=";
        out << cross_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CrossTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
