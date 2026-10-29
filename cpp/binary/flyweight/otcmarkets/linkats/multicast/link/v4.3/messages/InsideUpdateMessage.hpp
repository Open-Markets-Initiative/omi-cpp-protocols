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

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Quote update information for the Quote Inside channel and the Quote Inside with Global OTC
// data channel.
class InsideUpdateMessage {
  public:
    static constexpr const char* name = "InsideUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InsideUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InsideUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 30;
    static constexpr std::size_t fixed_size = 30;
    std::size_t encoded_size() const { return 30; }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    std::uint32_t inside_id() const { return wire::read_u32_be(at(4)); }

    QuoteFlags quote_flags() const { return QuoteFlags{ bytes_.subspan(8) }; }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(9))), -6); }

    std::uint32_t size() const { return wire::read_u32_be(at(17)); }

    std::uint64_t inside_time_milli() const { return wire::read_u64_be(at(21)); }

    std::uint8_t num_priced_mp() const { return wire::read_u8(at(29)); }

    void print(std::ostream& out) const {
        out << "InsideUpdateMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", inside_id=";
        out << inside_id();
        out << ", quote_flags=";
        quote_flags().print(out);
        out << ", price=";
        out << price();
        out << ", size=";
        out << size();
        out << ", inside_time_milli=";
        out << inside_time_milli();
        out << ", num_priced_mp=";
        out << static_cast<int>(num_priced_mp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InsideUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
