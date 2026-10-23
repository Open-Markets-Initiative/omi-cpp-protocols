#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// C1 and EDGX Options Only. Auction Cancel messages are used to disseminate the cancelation of
// an earlier Auction Notification message as a result of a user cancelation of the original
// order, a user modification request to change the price or increase the original order
// quantity, a fading of the NBBO or to cancel any remaining order quantity from the original
// Auction Notification messages following the auction termination. A user request to modify
// the order price or to increase the original order quantity will result in a cancelation of
// the auction followed by a new Auction Notification message. Auction Cancel messages will not
// be issued for order quantity decrements.
class AuctionCancelMessage {
  public:
    static constexpr const char* name = "AuctionCancelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionCancelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionCancelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t auction_id() const { return wire::read_u64_le(at(4)); }

    void print(std::ostream& out) const {
        out << "AuctionCancelMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", auction_id=";
        out << auction_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionCancelMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
