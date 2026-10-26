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
#include "../common/Decimal.hpp"
#include "../bitfields/SummaryFlags.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// The End of Day Summary message is sent immediately after trading ends for a symbol. No more
// Market Update messages will follow an End of Day Summary message for a particular symbol.
class EndOfDaySummaryMessage {
  public:
    static constexpr const char* name = "EndOfDaySummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EndOfDaySummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EndOfDaySummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 63;
    static constexpr std::size_t fixed_size = 63;
    std::size_t encoded_size() const { return 63; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view symbol() const { return view::text(at(4), 6, ' '); }

    std::uint32_t trade_date() const { return wire::read_u32_le(at(10)); }

    std::uint32_t open_interest() const { return wire::read_u32_le(at(14)); }

    Decimal high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(18))), -4); }

    Decimal low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(26))), -4); }

    Decimal open_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(34))), -4); }

    Decimal close_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(42))), -4); }

    std::uint32_t total_volume() const { return wire::read_u32_le(at(50)); }

    std::uint32_t block_volume() const { return wire::read_u32_le(at(54)); }

    std::uint32_t ecrp_volume() const { return wire::read_u32_le(at(58)); }

    SummaryFlags summary_flags() const { return SummaryFlags{ bytes_.subspan(62) }; }

    void print(std::ostream& out) const {
        out << "EndOfDaySummaryMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", trade_date=";
        out << trade_date();
        out << ", open_interest=";
        out << open_interest();
        out << ", high_price=";
        out << high_price();
        out << ", low_price=";
        out << low_price();
        out << ", open_price=";
        out << open_price();
        out << ", close_price=";
        out << close_price();
        out << ", total_volume=";
        out << total_volume();
        out << ", block_volume=";
        out << block_volume();
        out << ", ecrp_volume=";
        out << ecrp_volume();
        out << ", summary_flags=";
        summary_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EndOfDaySummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
