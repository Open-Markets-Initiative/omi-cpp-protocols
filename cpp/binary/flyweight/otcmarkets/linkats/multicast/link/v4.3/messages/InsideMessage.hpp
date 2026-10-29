#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/InsideAction.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../common/Decimal.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// This message is sent on the Quote Inside Channel and the Quote Inside with Global OTC data
// channel.
class InsideMessage {
  public:
    static constexpr const char* name = "InsideMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InsideMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InsideMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 56;
    static constexpr std::size_t fixed_size = 56;
    std::size_t encoded_size() const { return 56; }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    std::uint32_t inside_id() const { return wire::read_u32_be(at(4)); }

    InsideAction inside_action() const { return static_cast<InsideAction>(wire::read_u8(at(8))); }

    QuoteFlags quote_flags() const { return QuoteFlags{ bytes_.subspan(9) }; }

    std::uint32_t security_id() const { return wire::read_u32_be(at(10)); }

    Decimal ask_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(14))), -6); }

    std::uint32_t ask_size() const { return wire::read_u32_be(at(22)); }

    std::uint64_t ask_time_milli() const { return wire::read_u64_be(at(26)); }

    Decimal bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(34))), -6); }

    std::uint32_t bid_size() const { return wire::read_u32_be(at(42)); }

    std::uint64_t bid_time_milli() const { return wire::read_u64_be(at(46)); }

    std::uint8_t ask_num_priced_mp() const { return wire::read_u8(at(54)); }

    std::uint8_t bid_num_priced_mp() const { return wire::read_u8(at(55)); }

    void print(std::ostream& out) const {
        out << "InsideMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", inside_id=";
        out << inside_id();
        out << ", inside_action=";
        out << inside_action();
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
        out << ", ask_num_priced_mp=";
        out << static_cast<int>(ask_num_priced_mp());
        out << ", bid_num_priced_mp=";
        out << static_cast<int>(bid_num_priced_mp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InsideMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
