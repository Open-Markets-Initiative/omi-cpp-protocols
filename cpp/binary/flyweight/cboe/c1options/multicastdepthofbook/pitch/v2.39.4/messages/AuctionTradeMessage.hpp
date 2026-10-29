#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Auction Trade messages are used to disseminate executions resulting from an options auction.
class AuctionTradeMessage {
  public:
    static constexpr const char* name = "AuctionTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t auction_id() const { return wire::read_u64_le(at(4)); }

    std::uint64_t execution_id() const { return wire::read_u64_le(at(12)); }

    Decimal long_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(20))), -4); }

    std::uint32_t contracts() const { return wire::read_u32_le(at(28)); }

    void print(std::ostream& out) const {
        out << "AuctionTradeMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", auction_id=";
        out << auction_id();
        out << ", execution_id=";
        out << execution_id();
        out << ", long_price=";
        out << long_price();
        out << ", contracts=";
        out << contracts();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
