#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/MdEntryTypeBook.hpp"
#include "../enums/MdUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of entries in Market Data message
class IncrementalRefreshOrderBookGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 40;

    IncrementalRefreshOrderBookGroup() = default;
    IncrementalRefreshOrderBookGroup(std::optional<std::uint64_t> order_id_optional, std::optional<std::uint64_t> md_order_priority, std::optional<Decimal> md_entry_px_optional, std::optional<std::int32_t> md_display_qty_optional, std::int32_t security_id, MdUpdateAction md_update_action, MdEntryTypeBook md_entry_type_book, const std::array<std::byte, 6>& padding_6);

    // Order Id Optional: Order ID
    std::optional<std::uint64_t> order_id_optional() const;
    void set_order_id_optional(std::optional<std::uint64_t> value);

    // Md Order Priority: Order priority for execution on the order book
    std::optional<std::uint64_t> md_order_priority() const;
    void set_md_order_priority(std::optional<std::uint64_t> value);

    // Md Entry Px Optional: Market Data entry price
    std::optional<Decimal> md_entry_px_optional() const;
    void set_md_entry_px_optional(std::optional<Decimal> value);

    // Md Display Qty Optional: Visible qty of order
    std::optional<std::int32_t> md_display_qty_optional() const;
    void set_md_display_qty_optional(std::optional<std::int32_t> value);

    // Security Id: Unique instrument ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Md Update Action: Market Data update action
    MdUpdateAction md_update_action() const;
    void set_md_update_action(MdUpdateAction value);

    // Md Entry Type Book: Market Data entry type
    MdEntryTypeBook md_entry_type_book() const;
    void set_md_entry_type_book(MdEntryTypeBook value);

    // Padding 6: 6 bytes padding
    const std::array<std::byte, 6>& padding_6() const;
    std::array<std::byte, 6>& padding_6();
    void set_padding_6(const std::array<std::byte, 6>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshOrderBookGroup& other) const;
    bool operator!=(const IncrementalRefreshOrderBookGroup& other) const;

  private:
    std::optional<std::uint64_t> order_id_optional_{};
    std::optional<std::uint64_t> md_order_priority_{};
    std::optional<Decimal> md_entry_px_optional_{};
    std::optional<std::int32_t> md_display_qty_optional_{};
    std::int32_t security_id_{};
    MdUpdateAction md_update_action_{};
    MdEntryTypeBook md_entry_type_book_{};
    std::array<std::byte, 6> padding_6_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshOrderBookGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_8
