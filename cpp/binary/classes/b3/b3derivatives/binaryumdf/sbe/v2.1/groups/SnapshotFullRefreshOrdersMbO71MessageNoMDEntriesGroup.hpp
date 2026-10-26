#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdEntryType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// noMDEntries
class SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 42;

    SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup() = default;
    SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup(std::optional<Decimal> md_corporate_offset_price_optional, std::int64_t md_entry_size_quantity, std::optional<std::uint32_t> md_entry_position_no, std::optional<std::uint32_t> entering_firm, std::optional<std::chrono::nanoseconds> md_insert_timestamp, std::uint64_t secondary_order_id, MdEntryType md_entry_type, const MatchEventIndicator& match_event_indicator);

    // Md Corporate Offset Price Optional: mDEntryPx
    std::optional<Decimal> md_corporate_offset_price_optional() const;
    void set_md_corporate_offset_price_optional(std::optional<Decimal> value);

    // Md Entry Size Quantity: mDEntrySize
    std::int64_t md_entry_size_quantity() const;
    void set_md_entry_size_quantity(std::int64_t value);

    // Md Entry Position No: mDEntryPositionNo
    std::optional<std::uint32_t> md_entry_position_no() const;
    void set_md_entry_position_no(std::optional<std::uint32_t> value);

    // Entering Firm: enteringFirm
    std::optional<std::uint32_t> entering_firm() const;
    void set_entering_firm(std::optional<std::uint32_t> value);

    // Md Insert Timestamp: mDInsertTimestamp
    std::optional<std::chrono::nanoseconds> md_insert_timestamp() const;
    void set_md_insert_timestamp(std::optional<std::chrono::nanoseconds> value);

    // Secondary Order Id: secondaryOrderID
    std::uint64_t secondary_order_id() const;
    void set_secondary_order_id(std::uint64_t value);

    // Md Entry Type: mDEntryType
    MdEntryType md_entry_type() const;
    void set_md_entry_type(MdEntryType value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup& other) const;
    bool operator!=(const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup& other) const;

  private:
    std::optional<Decimal> md_corporate_offset_price_optional_{};
    std::int64_t md_entry_size_quantity_{};
    std::optional<std::uint32_t> md_entry_position_no_{};
    std::optional<std::uint32_t> entering_firm_{};
    std::optional<std::chrono::nanoseconds> md_insert_timestamp_{};
    std::uint64_t secondary_order_id_{};
    MdEntryType md_entry_type_{};
    MatchEventIndicator match_event_indicator_{};
};

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
