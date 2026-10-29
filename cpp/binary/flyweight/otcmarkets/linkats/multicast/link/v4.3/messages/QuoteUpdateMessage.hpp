#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../common/Decimal.hpp"
#include "../bitfields/ExtendedQuoteFlags.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Quote update information for the Quote Book channel and the Quote Book with Global OTC data
// channel.
class QuoteUpdateMessage {
  public:
    static constexpr const char* name = "QuoteUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 33;
    static constexpr std::size_t fixed_size = 33;
    std::size_t encoded_size() const { return 33; }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    std::uint32_t quote_id() const { return wire::read_u32_be(at(4)); }

    QuoteFlags quote_flags() const { return QuoteFlags{ bytes_.subspan(8) }; }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(9))), -6); }

    std::uint32_t size() const { return wire::read_u32_be(at(17)); }

    std::int8_t qap() const { return wire::read_i8(at(21)); }

    std::uint64_t quote_time_milli() const { return wire::read_u64_be(at(22)); }

    std::uint16_t quote_reference_id() const { return wire::read_u16_be(at(30)); }

    ExtendedQuoteFlags extended_quote_flags() const { return ExtendedQuoteFlags{ bytes_.subspan(32) }; }

    void print(std::ostream& out) const {
        out << "QuoteUpdateMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", quote_id=";
        out << quote_id();
        out << ", quote_flags=";
        quote_flags().print(out);
        out << ", price=";
        out << price();
        out << ", size=";
        out << size();
        out << ", qap=";
        out << static_cast<int>(qap());
        out << ", quote_time_milli=";
        out << quote_time_milli();
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

inline std::ostream& operator<<(std::ostream& out, const QuoteUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
