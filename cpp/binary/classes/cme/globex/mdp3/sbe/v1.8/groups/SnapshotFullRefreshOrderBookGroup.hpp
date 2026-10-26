#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/MdEntryTypeBook.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of entries in Market Data message
class SnapshotFullRefreshOrderBookGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 29;

    SnapshotFullRefreshOrderBookGroup() = default;
    SnapshotFullRefreshOrderBookGroup(std::uint64_t order_id, std::optional<std::uint64_t> md_order_priority, Decimal md_entry_px, std::int32_t md_display_qty, MdEntryTypeBook md_entry_type_book);

    // Order Id: Unique Order ID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Md Order Priority: Order priority for execution on the order book
    std::optional<std::uint64_t> md_order_priority() const;
    void set_md_order_priority(std::optional<std::uint64_t> value);

    // Md Entry Px: Market Data entry price
    Decimal md_entry_px() const;
    void set_md_entry_px(Decimal value);

    // Md Display Qty: Visible order qty
    std::int32_t md_display_qty() const;
    void set_md_display_qty(std::int32_t value);

    // Md Entry Type Book: Market Data entry type
    MdEntryTypeBook md_entry_type_book() const;
    void set_md_entry_type_book(MdEntryTypeBook value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SnapshotFullRefreshOrderBookGroup& other) const;
    bool operator!=(const SnapshotFullRefreshOrderBookGroup& other) const;

  private:
    std::uint64_t order_id_{};
    std::optional<std::uint64_t> md_order_priority_{};
    Decimal md_entry_px_{ 0, -7 };
    std::int32_t md_display_qty_{};
    MdEntryTypeBook md_entry_type_book_{};
};

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrderBookGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_8
