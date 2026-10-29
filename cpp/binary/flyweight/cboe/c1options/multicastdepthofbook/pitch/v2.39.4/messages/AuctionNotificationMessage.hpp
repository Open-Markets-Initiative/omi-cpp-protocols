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
#include "../enums/SideIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/CustomerIndicator.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Auction Notification messages are used to disseminate order details of an auction.
class AuctionNotificationMessage {
  public:
    static constexpr const char* name = "AuctionNotificationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionNotificationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionNotificationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 41;
    static constexpr std::size_t fixed_size = 41;
    std::size_t encoded_size() const { return 41; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view symbol() const { return view::text(at(4), 6, ' '); }

    std::uint64_t auction_id() const { return wire::read_u64_le(at(10)); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(18))); }

    SideIndicator side_indicator() const { return static_cast<SideIndicator>(wire::read_char(at(19))); }

    Decimal long_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(20))), -4); }

    std::uint32_t contracts() const { return wire::read_u32_le(at(28)); }

    CustomerIndicator customer_indicator() const { return static_cast<CustomerIndicator>(wire::read_char(at(32))); }

    std::string_view participant_id() const { return view::text(at(33), 4, ' '); }

    std::uint32_t auction_end_offset() const { return wire::read_u32_le(at(37)); }

    void print(std::ostream& out) const {
        out << "AuctionNotificationMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", auction_id=";
        out << auction_id();
        out << ", auction_type=";
        out << auction_type();
        out << ", side_indicator=";
        out << side_indicator();
        out << ", long_price=";
        out << long_price();
        out << ", contracts=";
        out << contracts();
        out << ", customer_indicator=";
        out << customer_indicator();
        out << ", participant_id=";
        print::text(out, participant_id());
        out << ", auction_end_offset=";
        out << auction_end_offset();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionNotificationMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
