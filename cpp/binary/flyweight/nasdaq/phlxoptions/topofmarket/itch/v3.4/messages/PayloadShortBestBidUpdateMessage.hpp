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

// The options system will continuously calculate its best bid and offer position for active
// options contracts on the options market during the trading day. Whenever the best bid or ask
// position changes on one side but not the other side, the options system will send its best
// bid or ask update via this feed for the affected security.
class PayloadShortBestBidUpdateMessage {
  public:
    static constexpr const char* name = "PayloadShortBestBidUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadShortBestBidUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadShortBestBidUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(4)); }

    QuoteCondition quote_condition() const { return static_cast<QuoteCondition>(wire::read_char(at(8))); }

    Decimal price_2() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_be(at(9))), -2); }

    std::uint16_t size_2() const { return wire::read_u16_be(at(11)); }

    void print(std::ostream& out) const {
        out << "PayloadShortBestBidUpdateMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", option_id=";
        out << option_id();
        out << ", quote_condition=";
        out << quote_condition();
        out << ", price_2=";
        out << price_2();
        out << ", size_2=";
        out << size_2();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadShortBestBidUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
