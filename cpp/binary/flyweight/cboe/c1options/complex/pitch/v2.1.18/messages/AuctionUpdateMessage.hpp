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
#include "../enums/AuctionOpeningType.hpp"
#include "../common/Decimal.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Options Auction Update messages are used to disseminate price and size information during
// the Opening and Re-Opening (halt) process for complex instruments.
class AuctionUpdateMessage {
  public:
    static constexpr const char* name = "AuctionUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 62;
    static constexpr std::size_t fixed_size = 62;
    std::size_t encoded_size() const { return 62; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view complex_instrument_id_8() const { return view::text(at(4), 8, ' '); }

    AuctionOpeningType auction_opening_type() const { return static_cast<AuctionOpeningType>(wire::read_char(at(12))); }

    Decimal reference_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(13))), -4); }

    std::uint32_t buy_contracts() const { return wire::read_u32_le(at(21)); }

    std::uint32_t sell_contracts() const { return wire::read_u32_le(at(25)); }

    Decimal indicative_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(29))), -4); }

    Decimal auction_only_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(37))), -4); }

    char opening_condition() const { return wire::read_char(at(45)); }

    Decimal composite_market_bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(46))), -4); }

    Decimal composite_market_offer_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(54))), -4); }

    void print(std::ostream& out) const {
        out << "AuctionUpdateMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", complex_instrument_id_8=";
        print::text(out, complex_instrument_id_8());
        out << ", auction_opening_type=";
        out << auction_opening_type();
        out << ", reference_price=";
        out << reference_price();
        out << ", buy_contracts=";
        out << buy_contracts();
        out << ", sell_contracts=";
        out << sell_contracts();
        out << ", indicative_price=";
        out << indicative_price();
        out << ", auction_only_price=";
        out << auction_only_price();
        out << ", opening_condition=";
        print::character(out, opening_condition());
        out << ", composite_market_bid_price=";
        out << composite_market_bid_price();
        out << ", composite_market_offer_price=";
        out << composite_market_offer_price();
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

} // namespace cboe::c1options::complex::pitch::v2_1_18
