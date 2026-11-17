// Databento.MarketData.Normalized.Dbn.v2: messages/RecordBodyStatMsg.hpp
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
#include "../enums/StatType.hpp"
#include "../enums/UpdateAction.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// A statistics message; the record of the statistics schema
class RecordBodyStatMsg {
  public:
    static constexpr const char* name = "RecordBodyStatMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecordBodyStatMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecordBodyStatMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 48;
    static constexpr std::size_t fixed_size = 48;
    std::size_t encoded_size() const { return 48; }

    std::optional<std::chrono::nanoseconds> ts_recv() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<std::chrono::nanoseconds> ts_ref() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<std::int32_t> quantity() const { return wire::nullable(wire::read_i32_le(at(24)), static_cast<std::int32_t>(2147483647LL)); }

    std::uint32_t sequence() const { return wire::read_u32_le(at(28)); }

    std::int32_t ts_in_delta() const { return wire::read_i32_le(at(32)); }

    StatType stat_type() const { return static_cast<StatType>(wire::read_u16_le(at(36))); }

    std::uint16_t channel() const { return wire::read_u16_le(at(38)); }

    UpdateAction update_action() const { return static_cast<UpdateAction>(wire::read_u8(at(40))); }

    std::uint8_t stat_flags() const { return wire::read_u8(at(41)); }

    std::span<const std::byte, 6> reserved_6() const { return bytes_.subspan(42).template first<6>(); }

    void print(std::ostream& out) const {
        out << "RecordBodyStatMsg{";
        out << "ts_recv=";
        print::optional_duration(out, ts_recv());
        out << ", ts_ref=";
        print::optional_duration(out, ts_ref());
        out << ", price=";
        print::optional(out, price());
        out << ", quantity=";
        print::optional(out, quantity());
        out << ", sequence=";
        out << sequence();
        out << ", ts_in_delta=";
        out << ts_in_delta();
        out << ", stat_type=";
        out << stat_type();
        out << ", channel=";
        out << channel();
        out << ", update_action=";
        out << update_action();
        out << ", stat_flags=";
        out << static_cast<int>(stat_flags());
        out << ", reserved_6=";
        print::hex(out, reserved_6().data(), reserved_6().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecordBodyStatMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
