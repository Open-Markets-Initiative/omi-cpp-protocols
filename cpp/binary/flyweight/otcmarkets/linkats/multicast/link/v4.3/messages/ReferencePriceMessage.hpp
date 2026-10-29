#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ReferencePriceAction.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../common/Decimal.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// This message is sent on the Reference Prices Channel. Size will always be set to 1.
class ReferencePriceMessage {
  public:
    static constexpr const char* name = "ReferencePriceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ReferencePriceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ReferencePriceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 54;
    static constexpr std::size_t fixed_size = 54;
    std::size_t encoded_size() const { return 54; }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    std::uint32_t reference_price_id() const { return wire::read_u32_be(at(4)); }

    ReferencePriceAction reference_price_action() const { return static_cast<ReferencePriceAction>(wire::read_u8(at(8))); }

    QuoteFlags quote_flags() const { return QuoteFlags{ bytes_.subspan(9) }; }

    std::uint32_t security_id() const { return wire::read_u32_be(at(10)); }

    Decimal ask_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(14))), -6); }

    std::uint32_t ask_size() const { return wire::read_u32_be(at(22)); }

    std::uint64_t ask_time_milli() const { return wire::read_u64_be(at(26)); }

    Decimal bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(34))), -6); }

    std::uint32_t bid_size() const { return wire::read_u32_be(at(42)); }

    std::uint64_t bid_time_milli() const { return wire::read_u64_be(at(46)); }

    void print(std::ostream& out) const {
        out << "ReferencePriceMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", reference_price_id=";
        out << reference_price_id();
        out << ", reference_price_action=";
        out << reference_price_action();
        out << ", quote_flags=";
        quote_flags().print(out);
        out << ", security_id=";
        out << security_id();
        out << ", ask_price=";
        out << ask_price();
        out << ", ask_size=";
        out << ask_size();
        out << ", ask_time_milli=";
        out << ask_time_milli();
        out << ", bid_price=";
        out << bid_price();
        out << ", bid_size=";
        out << bid_size();
        out << ", bid_time_milli=";
        out << bid_time_milli();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ReferencePriceMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
