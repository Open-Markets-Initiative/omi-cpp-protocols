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

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

// Auction Summary messages are used to disseminate the results of an auction of a complex
// instrument. An Opening or Re-Opening Auction Summary message for each complex instrument is
// sent at the conclusion of its Opening or Re-Opening auction and represents Cboe opening
// price.
class AuctionSummaryMessage {
  public:
    static constexpr const char* name = "AuctionSummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionSummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionSummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view symbol_long() const { return view::text(at(4), 8, ' '); }

    char auction_opening_type() const { return wire::read_char(at(12)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(13))), -4); }

    std::uint32_t shares_contracts() const { return wire::read_u32_le(at(21)); }

    void print(std::ostream& out) const {
        out << "AuctionSummaryMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", symbol_long=";
        print::text(out, symbol_long());
        out << ", auction_opening_type=";
        print::character(out, auction_opening_type());
        out << ", price=";
        out << price();
        out << ", shares_contracts=";
        out << shares_contracts();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionSummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
