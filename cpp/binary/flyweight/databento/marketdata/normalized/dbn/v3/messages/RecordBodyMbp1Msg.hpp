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
#include "../enums/Action.hpp"
#include "../enums/Side.hpp"
#include "../bitfields/Flags.hpp"
#include "../structs/BidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// Market by price implementation with a known book depth of 1; the record of the mbp-1 and
// tbbo schemas
class RecordBodyMbp1Msg {
  public:
    static constexpr const char* name = "RecordBodyMbp1Msg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecordBodyMbp1Msg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecordBodyMbp1Msg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 64;
    static constexpr std::size_t fixed_size = 64;
    std::size_t encoded_size() const { return 64; }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::uint32_t size() const { return wire::read_u32_le(at(8)); }

    Action action() const { return static_cast<Action>(wire::read_char(at(12))); }

    Side side() const { return static_cast<Side>(wire::read_char(at(13))); }

    Flags flags() const { return Flags{ bytes_.subspan(14) }; }

    std::uint8_t depth() const { return wire::read_u8(at(15)); }

    std::optional<std::chrono::nanoseconds> ts_recv() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::int32_t ts_in_delta() const { return wire::read_i32_le(at(24)); }

    std::uint32_t sequence() const { return wire::read_u32_le(at(28)); }

    BidAskPair bid_ask_pair() const { return BidAskPair{ bytes_.subspan(32) }; }

    void print(std::ostream& out) const {
        out << "RecordBodyMbp1Msg{";
        out << "price=";
        print::optional(out, price());
        out << ", size=";
        out << size();
        out << ", action=";
        out << action();
        out << ", side=";
        out << side();
        out << ", flags=";
        flags().print(out);
        out << ", depth=";
        out << static_cast<int>(depth());
        out << ", ts_recv=";
        print::optional_duration(out, ts_recv());
        out << ", ts_in_delta=";
        out << ts_in_delta();
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

inline std::ostream& operator<<(std::ostream& out, const RecordBodyMbp1Msg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
