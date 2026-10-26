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

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// C1 Only. The SOQ Strike Range Update message is only available on the C1 Exchange. This
// message disseminates the minimum and maximum strike prices of the strike price range used to
// calculate the Special Opening Quote (SOQ) on a Volatility Settlement date. In the event that
// multiple distinct SOQ calculations occur on the same day, the applicable SOQ is
// differentiated by the SOQ Identifier field, which is set to the CSMi symbol on which the
// final settlement SOQ value is disseminated.
class SoqStrikeRangeUpdateMessage {
  public:
    static constexpr const char* name = "SoqStrikeRangeUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SoqStrikeRangeUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SoqStrikeRangeUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view soq_identifier() const { return view::text(at(4), 20, ' '); }

    Decimal lower_strike_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(24))), -4); }

    Decimal upper_strike_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(32))), -4); }

    void print(std::ostream& out) const {
        out << "SoqStrikeRangeUpdateMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", soq_identifier=";
        print::text(out, soq_identifier());
        out << ", lower_strike_price=";
        out << lower_strike_price();
        out << ", upper_strike_price=";
        out << upper_strike_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SoqStrikeRangeUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
