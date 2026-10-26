#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/MdEntryType.hpp"
#include "../enums/OpenCloseSettlFlag.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of entries in Market Data message
class SnapshotfullRefreshTcpLongGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 23;

    SnapshotfullRefreshTcpLongGroup() = default;
    SnapshotfullRefreshTcpLongGroup(std::optional<Decimal> md_entry_px_optional_ex, std::optional<std::uint64_t> md_entry_size_optional, std::optional<std::int32_t> number_of_orders_optional, std::optional<std::uint8_t> md_price_level_unsigned_optional, std::optional<OpenCloseSettlFlag> open_close_settl_flag, MdEntryType md_entry_type);

    // Md Entry Px Optional Ex: Workup price
    std::optional<Decimal> md_entry_px_optional_ex() const;
    void set_md_entry_px_optional_ex(std::optional<Decimal> value);

    // Md Entry Size Optional: Aggregate booked qty at price level, notional
    std::optional<std::uint64_t> md_entry_size_optional() const;
    void set_md_entry_size_optional(std::optional<std::uint64_t> value);

    // Number Of Orders Optional: In Book entry - aggregate number of orders at given price
    // level
    std::optional<std::int32_t> number_of_orders_optional() const;
    void set_number_of_orders_optional(std::optional<std::int32_t> value);

    // Md Price Level Unsigned Optional: Aggregate book level
    std::optional<std::uint8_t> md_price_level_unsigned_optional() const;
    void set_md_price_level_unsigned_optional(std::optional<std::uint8_t> value);

    // Open Close Settl Flag: Flag describing IOP and Open Price entries
    std::optional<OpenCloseSettlFlag> open_close_settl_flag() const;
    void set_open_close_settl_flag(std::optional<OpenCloseSettlFlag> value);

    // Md Entry Type: Market Data entry type
    MdEntryType md_entry_type() const;
    void set_md_entry_type(MdEntryType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SnapshotfullRefreshTcpLongGroup& other) const;
    bool operator!=(const SnapshotfullRefreshTcpLongGroup& other) const;

  private:
    std::optional<Decimal> md_entry_px_optional_ex_{};
    std::optional<std::uint64_t> md_entry_size_optional_{};
    std::optional<std::int32_t> number_of_orders_optional_{};
    std::optional<std::uint8_t> md_price_level_unsigned_optional_{};
    std::optional<OpenCloseSettlFlag> open_close_settl_flag_{};
    MdEntryType md_entry_type_{};
};

std::ostream& operator<<(std::ostream& out, const SnapshotfullRefreshTcpLongGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
