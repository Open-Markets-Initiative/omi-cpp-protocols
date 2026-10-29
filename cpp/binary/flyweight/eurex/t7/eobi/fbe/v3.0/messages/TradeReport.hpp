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
#include "../enums/MatchType.hpp"
#include "../enums/MatchSubType.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

class TradeReport {
  public:
    static constexpr const char* name = "TradeReport";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeReport(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeReport has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::uint32_t> trd_match_id() const { return wire::nullable(wire::read_u32_le(at(16)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    std::optional<std::int32_t> last_qty() const { return wire::nullable(wire::read_i32_le(at(20)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<Decimal> last_px() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<MatchType> match_type() const { return wire::nullable_enum<MatchType>(wire::read_u8(at(32)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<MatchSubType> match_sub_type() const { return wire::nullable_enum<MatchSubType>(wire::read_u8(at(33)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 6> pad6() const { return bytes_.subspan(34).template first<6>(); }

    void print(std::ostream& out) const {
        out << "TradeReport{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << ", trd_match_id=";
        print::optional(out, trd_match_id());
        out << ", last_qty=";
        print::optional(out, last_qty());
        out << ", last_px=";
        print::optional(out, last_px());
        out << ", match_type=";
        print::optional(out, match_type());
        out << ", match_sub_type=";
        print::optional(out, match_sub_type());
        out << ", pad6=";
        print::hex(out, pad6().data(), pad6().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeReport& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v3_0
