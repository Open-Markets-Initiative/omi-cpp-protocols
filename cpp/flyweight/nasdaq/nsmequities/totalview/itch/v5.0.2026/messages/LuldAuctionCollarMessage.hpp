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

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// Indicates the auction collar thresholds within which a paused security can reopen following
// a LULD trading pause
class LuldAuctionCollarMessage {
  public:
    static constexpr const char* name = "LuldAuctionCollarMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LuldAuctionCollarMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LuldAuctionCollarMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 34;
    static constexpr std::size_t fixed_size = 34;
    std::size_t encoded_size() const { return 34; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }

    std::string_view stock() const { return view::text(at(10), 8, ' '); }

    Decimal auction_collar_reference_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(18))), -4); }

    Decimal upper_auction_collar_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(22))), -4); }

    Decimal lower_auction_collar_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(26))), -4); }

    std::uint32_t auction_collar_extension() const { return wire::read_u32_be(at(30)); }

    void print(std::ostream& out) const {
        out << "LuldAuctionCollarMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", stock=";
        print::text(out, stock());
        out << ", auction_collar_reference_price=";
        out << auction_collar_reference_price();
        out << ", upper_auction_collar_price=";
        out << upper_auction_collar_price();
        out << ", lower_auction_collar_price=";
        out << lower_auction_collar_price();
        out << ", auction_collar_extension=";
        out << auction_collar_extension();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LuldAuctionCollarMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
