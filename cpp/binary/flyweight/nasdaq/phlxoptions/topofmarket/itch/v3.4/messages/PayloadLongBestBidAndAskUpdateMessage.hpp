#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/QuoteCondition.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// This message is the same as the Best Bid AND Ask Update Message – Short Form described above
// except that Prices and Sizes are 4 byte Integers, the prices having 4 implied decimal
// places.
class PayloadLongBestBidAndAskUpdateMessage {
  public:
    static constexpr const char* name = "PayloadLongBestBidAndAskUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadLongBestBidAndAskUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadLongBestBidAndAskUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(4)); }

    QuoteCondition quote_condition() const { return static_cast<QuoteCondition>(wire::read_char(at(8))); }

    Decimal bid_price_4() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(9))), -4); }

    std::uint32_t bid_size_4() const { return wire::read_u32_be(at(13)); }

    Decimal ask_price_4() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(17))), -4); }

    std::uint32_t ask_size_4() const { return wire::read_u32_be(at(21)); }

    void print(std::ostream& out) const {
        out << "PayloadLongBestBidAndAskUpdateMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", option_id=";
        out << option_id();
        out << ", quote_condition=";
        out << quote_condition();
        out << ", bid_price_4=";
        out << bid_price_4();
        out << ", bid_size_4=";
        out << bid_size_4();
        out << ", ask_price_4=";
        out << ask_price_4();
        out << ", ask_size_4=";
        out << ask_size_4();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadLongBestBidAndAskUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
