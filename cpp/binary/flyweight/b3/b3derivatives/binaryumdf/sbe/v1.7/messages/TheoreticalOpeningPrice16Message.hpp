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
#include "../common/Decimal.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// TheoreticalOpeningPrice_16Message
class TheoreticalOpeningPrice16Message {
  public:
    static constexpr const char* name = "TheoreticalOpeningPrice16Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TheoreticalOpeningPrice16Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TheoreticalOpeningPrice16Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(9))); }

    std::uint16_t trade_date() const { return wire::read_u16_le(at(10)); }

    std::optional<Decimal> md_corporate_offset_price_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(12)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<std::int64_t> md_entry_size_quantity_optional() const { return wire::nullable(wire::read_i64_le(at(20)), static_cast<std::int64_t>(-9223372036854775807LL - 1)); }

    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(28)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(36)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "TheoreticalOpeningPrice16Message{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", md_update_action=";
        out << md_update_action();
        out << ", trade_date=";
        out << trade_date();
        out << ", md_corporate_offset_price_optional=";
        print::optional(out, md_corporate_offset_price_optional());
        out << ", md_entry_size_quantity_optional=";
        print::optional(out, md_entry_size_quantity_optional());
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

inline std::ostream& operator<<(std::ostream& out, const TheoreticalOpeningPrice16Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
