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
#include "../enums/MdEntryType.hpp"
#include "../bitfields/MatchEventIndicatorOptional.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// noMDEntries
class SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup {
  public:
    static constexpr const char* name = "SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 42;
    static constexpr std::size_t fixed_size = 42;
    std::size_t encoded_size() const { return 42; }

    std::optional<Decimal> md_corporate_offset_price_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::int64_t md_entry_size_quantity() const { return wire::read_i64_le(at(8)); }

    std::uint32_t md_entry_position_no() const { return wire::read_u32_le(at(16)); }

    std::optional<std::uint32_t> entering_firm() const { return wire::nullable(wire::read_u32_le(at(20)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::chrono::nanoseconds> md_insert_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(24)), static_cast<std::uint64_t>(0ULL)); }

    std::uint64_t secondary_order_id() const { return wire::read_u64_le(at(32)); }

    MdEntryType md_entry_type() const { return static_cast<MdEntryType>(wire::read_char(at(40))); }

    MatchEventIndicatorOptional match_event_indicator_optional() const { return MatchEventIndicatorOptional{ bytes_.subspan(41) }; }

    void print(std::ostream& out) const {
        out << "SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup{";
        out << "md_corporate_offset_price_optional=";
        print::optional(out, md_corporate_offset_price_optional());
        out << ", md_entry_size_quantity=";
        out << md_entry_size_quantity();
        out << ", md_entry_position_no=";
        out << md_entry_position_no();
        out << ", entering_firm=";
        print::optional(out, entering_firm());
        out << ", md_insert_timestamp=";
        print::optional_duration(out, md_insert_timestamp());
        out << ", secondary_order_id=";
        out << secondary_order_id();
        out << ", md_entry_type=";
        out << md_entry_type();
        out << ", match_event_indicator_optional=";
        match_event_indicator_optional().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
