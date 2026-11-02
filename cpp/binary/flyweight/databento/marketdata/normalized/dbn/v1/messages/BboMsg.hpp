#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"
#include "../bitfields/Flags.hpp"
#include "../structs/BidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// Subsampled market by price with a known book depth of 1; the record of the bbo-1s and bbo-1m
// schemas
class BboMsg {
  public:
    static constexpr const char* name = "BboMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BboMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BboMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 64;
    static constexpr std::size_t fixed_size = 64;
    std::size_t encoded_size() const { return 64; }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::uint32_t size() const { return wire::read_u32_le(at(8)); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(12).template first<1>(); }

    Side side() const { return static_cast<Side>(wire::read_char(at(13))); }

    Flags flags() const { return Flags{ bytes_.subspan(14) }; }

    std::span<const std::byte, 1> second_reserved_1() const { return bytes_.subspan(15).template first<1>(); }

    std::optional<std::chrono::nanoseconds> ts_recv() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(24).template first<4>(); }

    std::uint32_t sequence() const { return wire::read_u32_le(at(28)); }

    BidAskPair bid_ask_pair() const { return BidAskPair{ bytes_.subspan(32) }; }

    void print(std::ostream& out) const {
        out << "BboMsg{";
        out << "price=";
        print::optional(out, price());
        out << ", size=";
        out << size();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", side=";
        out << side();
        out << ", flags=";
        flags().print(out);
        out << ", second_reserved_1=";
        print::hex(out, second_reserved_1().data(), second_reserved_1().size());
        out << ", ts_recv=";
        print::optional_duration(out, ts_recv());
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", sequence=";
        out << sequence();
        out << ", bid_ask_pair=";
        bid_ask_pair().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BboMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
