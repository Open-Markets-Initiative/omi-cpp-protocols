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
#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/MdUpdateAction.hpp"
#include "../enums/OpenCloseSettlFlag.hpp"
#include "../common/Decimal.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// OpeningPrice_15Message
class OpeningPrice15Message {
  public:
    static constexpr const char* name = "OpeningPrice15Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OpeningPrice15Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OpeningPrice15Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 44;
    static constexpr std::size_t fixed_size = 44;
    std::size_t encoded_size() const { return 44; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(9))); }

    OpenCloseSettlFlag open_close_settl_flag() const { return static_cast<OpenCloseSettlFlag>(wire::read_u8(at(10))); }

    std::span<const std::byte, 1> offset_11_padding_1() const { return bytes_.subspan(11).template first<1>(); }

    Decimal md_future_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(12))), -4); }

    std::optional<Decimal> net_chg_prev_day() const { return wire::nullable_decimal(wire::read_i64_le(at(20)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(28)); }

    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(30)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(38)), static_cast<std::uint32_t>(0ULL)); }

    std::span<const std::byte, 2> padding_2() const { return bytes_.subspan(42).template first<2>(); }

    void print(std::ostream& out) const {
        out << "OpeningPrice15Message{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", md_update_action=";
        out << md_update_action();
        out << ", open_close_settl_flag=";
        out << open_close_settl_flag();
        out << ", offset_11_padding_1=";
        print::hex(out, offset_11_padding_1().data(), offset_11_padding_1().size());
        out << ", md_future_price=";
        out << md_future_price();
        out << ", net_chg_prev_day=";
        print::optional(out, net_chg_prev_day());
        out << ", trade_date=";
        out << trade_date();
        out << ", md_entry_timestamp=";
        print::optional_duration(out, md_entry_timestamp());
        out << ", rpt_seq=";
        print::optional(out, rpt_seq());
        out << ", padding_2=";
        print::hex(out, padding_2().data(), padding_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OpeningPrice15Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
