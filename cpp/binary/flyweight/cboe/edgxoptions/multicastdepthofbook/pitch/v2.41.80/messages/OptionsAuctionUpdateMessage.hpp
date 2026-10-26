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
#include "../enums/OpeningCondition.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Options Only. Options Auction Update messages are used to disseminate price and size
// information and Composite Market bid and offer prices during Opening and Re-Opening (halt)
// auctions on the Cboe Options Exchange. Options Auction Update messages are sent every five
// seconds during an opening period provided that one of the field values has changed. When no
// values have changed, a message is sent once every 60 seconds. Refer to the Cboe Options
// Opening Process specification for more information.
class OptionsAuctionUpdateMessage {
  public:
    static constexpr const char* name = "OptionsAuctionUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsAuctionUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsAuctionUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 62;
    static constexpr std::size_t fixed_size = 62;
    std::size_t encoded_size() const { return 62; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view expanded_symbol() const { return view::text(at(4), 8, ' '); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(12))); }

    Decimal reference_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(13))), -4); }

    std::uint32_t buy_contracts() const { return wire::read_u32_le(at(21)); }

    std::uint32_t sell_contracts() const { return wire::read_u32_le(at(25)); }

    Decimal indicative_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(29))), -4); }

    Decimal auction_only_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(37))), -4); }

    OpeningCondition opening_condition() const { return static_cast<OpeningCondition>(wire::read_char(at(45))); }

    Decimal composite_market_bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(46))), -4); }

    Decimal composite_market_offer_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(54))), -4); }

    void print(std::ostream& out) const {
        out << "OptionsAuctionUpdateMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", expanded_symbol=";
        print::text(out, expanded_symbol());
        out << ", auction_type=";
        out << auction_type();
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
        out << opening_condition();
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

inline std::ostream& operator<<(std::ostream& out, const OptionsAuctionUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
