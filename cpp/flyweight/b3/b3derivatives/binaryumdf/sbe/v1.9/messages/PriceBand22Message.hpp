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
#include "../enums/PriceBandType.hpp"
#include "../enums/PriceLimitType.hpp"
#include "../enums/PriceBandMidpointPriceType.hpp"
#include "../common/Decimal.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// PriceBand_22Message
class PriceBand22Message {
  public:
    static constexpr const char* name = "PriceBand22Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PriceBand22Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PriceBand22Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 48;
    static constexpr std::size_t fixed_size = 48;
    std::size_t encoded_size() const { return 48; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    std::optional<PriceBandType> price_band_type() const { return wire::nullable_enum<PriceBandType>(wire::read_u8(at(9)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<PriceLimitType> price_limit_type() const { return wire::nullable_enum<PriceLimitType>(wire::read_u8(at(10)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<PriceBandMidpointPriceType> price_band_midpoint_price_type() const { return wire::nullable_enum<PriceBandMidpointPriceType>(wire::read_u8(at(11)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<Decimal> low_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(12)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<Decimal> high_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(20)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<Decimal> trading_reference_price() const { return wire::nullable_decimal(wire::read_i64_le(at(28)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8); }

    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(36)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(44)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "PriceBand22Message{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", price_band_type=";
        print::optional(out, price_band_type());
        out << ", price_limit_type=";
        print::optional(out, price_limit_type());
        out << ", price_band_midpoint_price_type=";
        print::optional(out, price_band_midpoint_price_type());
        out << ", low_limit_price=";
        print::optional(out, low_limit_price());
        out << ", high_limit_price=";
        print::optional(out, high_limit_price());
        out << ", trading_reference_price=";
        print::optional(out, trading_reference_price());
        out << ", md_entry_timestamp=";
        print::optional_duration(out, md_entry_timestamp());
        out << ", rpt_seq=";
        print::optional(out, rpt_seq());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PriceBand22Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
