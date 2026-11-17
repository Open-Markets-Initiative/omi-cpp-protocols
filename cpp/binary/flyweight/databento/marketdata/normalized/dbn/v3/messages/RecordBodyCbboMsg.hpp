// Databento.MarketData.Normalized.Dbn.v3: messages/RecordBodyCbboMsg.hpp
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
#include "../structs/ConsolidatedBidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// Subsampled consolidated market by price with a known book depth of 1; the record of the
// cbbo-1s and cbbo-1m schemas
class RecordBodyCbboMsg {
  public:
    static constexpr const char* name = "RecordBodyCbboMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecordBodyCbboMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecordBodyCbboMsg has, which a reader checks before it views them
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

    std::span<const std::byte, 8> reserved_8() const { return bytes_.subspan(24).template first<8>(); }

    ConsolidatedBidAskPair consolidated_bid_ask_pair() const { return ConsolidatedBidAskPair{ bytes_.subspan(32) }; }

    void print(std::ostream& out) const {
        out << "RecordBodyCbboMsg{";
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
        out << ", reserved_8=";
        print::hex(out, reserved_8().data(), reserved_8().size());
        out << ", consolidated_bid_ask_pair=";
        consolidated_bid_ask_pair().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecordBodyCbboMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
