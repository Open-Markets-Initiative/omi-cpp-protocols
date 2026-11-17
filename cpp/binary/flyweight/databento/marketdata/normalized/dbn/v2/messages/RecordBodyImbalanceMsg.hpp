// Databento.MarketData.Normalized.Dbn.v2: messages/RecordBodyImbalanceMsg.hpp
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
#include "../enums/UnpairedSide.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// An auction imbalance message; the record of the imbalance schema
class RecordBodyImbalanceMsg {
  public:
    static constexpr const char* name = "RecordBodyImbalanceMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecordBodyImbalanceMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecordBodyImbalanceMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 96;
    static constexpr std::size_t fixed_size = 96;
    std::size_t encoded_size() const { return 96; }

    std::optional<std::chrono::nanoseconds> ts_recv() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<Decimal> ref_price() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<std::chrono::nanoseconds> auction_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<Decimal> cont_book_clr_price() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> auct_interest_clr_price() const { return wire::nullable_decimal(wire::read_i64_le(at(32)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> ssr_filling_price() const { return wire::nullable_decimal(wire::read_i64_le(at(40)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> ind_match_price() const { return wire::nullable_decimal(wire::read_i64_le(at(48)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> upper_collar() const { return wire::nullable_decimal(wire::read_i64_le(at(56)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> lower_collar() const { return wire::nullable_decimal(wire::read_i64_le(at(64)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::uint32_t paired_qty() const { return wire::read_u32_le(at(72)); }

    std::uint32_t total_imbalance_qty() const { return wire::read_u32_le(at(76)); }

    std::uint32_t market_imbalance_qty() const { return wire::read_u32_le(at(80)); }

    std::uint32_t unpaired_qty() const { return wire::read_u32_le(at(84)); }

    char auction_type() const { return wire::read_char(at(88)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(89))); }

    std::uint8_t auction_status() const { return wire::read_u8(at(90)); }

    std::uint8_t freeze_status() const { return wire::read_u8(at(91)); }

    std::uint8_t num_extensions() const { return wire::read_u8(at(92)); }

    UnpairedSide unpaired_side() const { return static_cast<UnpairedSide>(wire::read_char(at(93))); }

    char significant_imbalance() const { return wire::read_char(at(94)); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(95).template first<1>(); }

    void print(std::ostream& out) const {
        out << "RecordBodyImbalanceMsg{";
        out << "ts_recv=";
        print::optional_duration(out, ts_recv());
        out << ", ref_price=";
        print::optional(out, ref_price());
        out << ", auction_time=";
        print::optional_duration(out, auction_time());
        out << ", cont_book_clr_price=";
        print::optional(out, cont_book_clr_price());
        out << ", auct_interest_clr_price=";
        print::optional(out, auct_interest_clr_price());
        out << ", ssr_filling_price=";
        print::optional(out, ssr_filling_price());
        out << ", ind_match_price=";
        print::optional(out, ind_match_price());
        out << ", upper_collar=";
        print::optional(out, upper_collar());
        out << ", lower_collar=";
        print::optional(out, lower_collar());
        out << ", paired_qty=";
        out << paired_qty();
        out << ", total_imbalance_qty=";
        out << total_imbalance_qty();
        out << ", market_imbalance_qty=";
        out << market_imbalance_qty();
        out << ", unpaired_qty=";
        out << unpaired_qty();
        out << ", auction_type=";
        print::character(out, auction_type());
        out << ", side=";
        out << side();
        out << ", auction_status=";
        out << static_cast<int>(auction_status());
        out << ", freeze_status=";
        out << static_cast<int>(freeze_status());
        out << ", num_extensions=";
        out << static_cast<int>(num_extensions());
        out << ", unpaired_side=";
        out << unpaired_side();
        out << ", significant_imbalance=";
        print::character(out, significant_imbalance());
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecordBodyImbalanceMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
