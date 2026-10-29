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
#include "../enums/AuctionType.hpp"
#include "../common/Decimal.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Auction Update messages are used to disseminate Cboe price and size information during
// auctions for Cboe listed securities and for Cboe Market Close (CMC) crosses.
class AuctionUpdateMessage {
  public:
    static constexpr const char* name = "AuctionUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 45;
    static constexpr std::size_t fixed_size = 45;
    std::size_t encoded_size() const { return 45; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view stock_symbol() const { return view::text(at(4), 8, ' '); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(12))); }

    Decimal reference_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(13))), -4); }

    std::uint32_t buy_shares() const { return wire::read_u32_le(at(21)); }

    std::uint32_t sell_shares() const { return wire::read_u32_le(at(25)); }

    Decimal indicative_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(29))), -4); }

    Decimal auction_only_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(37))), -4); }

    void print(std::ostream& out) const {
        out << "AuctionUpdateMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", stock_symbol=";
        print::text(out, stock_symbol());
        out << ", auction_type=";
        out << auction_type();
        out << ", reference_price=";
        out << reference_price();
        out << ", buy_shares=";
        out << buy_shares();
        out << ", sell_shares=";
        out << sell_shares();
        out << ", indicative_price=";
        out << indicative_price();
        out << ", auction_only_price=";
        out << auction_only_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
