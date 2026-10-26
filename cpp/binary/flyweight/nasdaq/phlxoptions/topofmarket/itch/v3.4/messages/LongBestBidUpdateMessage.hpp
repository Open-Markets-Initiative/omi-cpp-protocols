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

// This message is the same as the Best Bid OR Ask Update Message – Short Form described above
// except that Prices and Sizes are 4 byte Integers, the price having 4 implied decimal places.
class LongBestBidUpdateMessage {
  public:
    static constexpr const char* name = "LongBestBidUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LongBestBidUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LongBestBidUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(4)); }

    QuoteCondition quote_condition() const { return static_cast<QuoteCondition>(wire::read_char(at(8))); }

    Decimal price_4() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(9))), -4); }

    std::uint32_t size_4() const { return wire::read_u32_be(at(13)); }

    void print(std::ostream& out) const {
        out << "LongBestBidUpdateMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", option_id=";
        out << option_id();
        out << ", quote_condition=";
        out << quote_condition();
        out << ", price_4=";
        out << price_4();
        out << ", size_4=";
        out << size_4();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LongBestBidUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
