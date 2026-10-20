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
#include "../enums/ImbalanceSide.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

// Broadcasts an Auction Information Message every one second between the Lock-in Time and the
// auction match for Opening and Closing Auctions, and during the Display Only Period for IPO,
// Halt, and Volatility Auctions.
class AuctionInformationMessage {
  public:
    static constexpr const char* name = "AuctionInformationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionInformationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionInformationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 79;
    static constexpr std::size_t fixed_size = 79;
    std::size_t encoded_size() const { return 79; }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(0))); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    std::uint32_t paired_shares() const { return wire::read_u32_le(at(17)); }

    Decimal reference_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(21))), -4); }

    Decimal indicative_clearing_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(29))), -4); }

    std::uint32_t imbalance_shares() const { return wire::read_u32_le(at(37)); }

    ImbalanceSide imbalance_side() const { return static_cast<ImbalanceSide>(wire::read_char(at(41))); }

    std::uint8_t extension_number() const { return wire::read_u8(at(42)); }

    std::chrono::seconds scheduled_auction_time() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(at(43)))); }

    Decimal auction_book_clearing_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(47))), -4); }

    Decimal collar_reference_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(55))), -4); }

    Decimal lower_auction_collar() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(63))), -4); }

    Decimal upper_auction_collar() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(71))), -4); }

    void print(std::ostream& out) const {
        out << "AuctionInformationMessage{";
        out << "auction_type=";
        out << auction_type();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", paired_shares=";
        out << paired_shares();
        out << ", reference_price=";
        out << reference_price();
        out << ", indicative_clearing_price=";
        out << indicative_clearing_price();
        out << ", imbalance_shares=";
        out << imbalance_shares();
        out << ", imbalance_side=";
        out << imbalance_side();
        out << ", extension_number=";
        out << static_cast<int>(extension_number());
        out << ", scheduled_auction_time=";
        out << scheduled_auction_time().count();
        out << ", auction_book_clearing_price=";
        out << auction_book_clearing_price();
        out << ", collar_reference_price=";
        out << collar_reference_price();
        out << ", lower_auction_collar=";
        out << lower_auction_collar();
        out << ", upper_auction_collar=";
        out << upper_auction_collar();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionInformationMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::tops::iextp::v1_66
