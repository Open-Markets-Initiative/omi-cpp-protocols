#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../common/Decimal.hpp"
#include "../bitfields/ExtendedQuoteFlags.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// This message is sent on the Quote Book channel and the Quote Book with Global OTC data
// channel.
class QuoteMessage {
  public:
    static constexpr const char* name = "QuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 63;
    static constexpr std::size_t fixed_size = 63;
    std::size_t encoded_size() const { return 63; }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    std::uint32_t quote_id() const { return wire::read_u32_be(at(4)); }

    std::uint8_t quote_action() const { return wire::read_u8(at(8)); }

    QuoteFlags quote_flags() const { return QuoteFlags{ bytes_.subspan(9) }; }

    std::uint32_t security_id() const { return wire::read_u32_be(at(10)); }

    std::string_view mpid() const { return view::text(at(14), 4, ' '); }

    Decimal ask_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(18))), -6); }

    std::uint32_t ask_size() const { return wire::read_u32_be(at(26)); }

    std::int8_t ask_qap() const { return wire::read_i8(at(30)); }

    std::uint64_t ask_time_milli() const { return wire::read_u64_be(at(31)); }

    Decimal bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(39))), -6); }

    std::uint32_t bid_size() const { return wire::read_u32_be(at(47)); }

    std::int8_t bid_qap() const { return wire::read_i8(at(51)); }

    std::uint64_t bid_time_milli() const { return wire::read_u64_be(at(52)); }

    std::uint16_t quote_reference_id() const { return wire::read_u16_be(at(60)); }

    ExtendedQuoteFlags extended_quote_flags() const { return ExtendedQuoteFlags{ bytes_.subspan(62) }; }

    void print(std::ostream& out) const {
        out << "QuoteMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", quote_id=";
        out << quote_id();
        out << ", quote_action=";
        out << static_cast<int>(quote_action());
        out << ", quote_flags=";
        quote_flags().print(out);
        out << ", security_id=";
        out << security_id();
        out << ", mpid=";
        print::text(out, mpid());
        out << ", ask_price=";
        out << ask_price();
        out << ", ask_size=";
        out << ask_size();
        out << ", ask_qap=";
        out << static_cast<int>(ask_qap());
        out << ", ask_time_milli=";
        out << ask_time_milli();
        out << ", bid_price=";
        out << bid_price();
        out << ", bid_size=";
        out << bid_size();
        out << ", bid_qap=";
        out << static_cast<int>(bid_qap());
        out << ", bid_time_milli=";
        out << bid_time_milli();
        out << ", quote_reference_id=";
        out << quote_reference_id();
        out << ", extended_quote_flags=";
        extended_quote_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
