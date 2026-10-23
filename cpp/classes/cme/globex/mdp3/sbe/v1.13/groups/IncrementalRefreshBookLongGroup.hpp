#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/MdEntryTypeBook.hpp"
#include "../enums/MdUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of entries in Market Data message.
class IncrementalRefreshBookLongGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    IncrementalRefreshBookLongGroup() = default;
    IncrementalRefreshBookLongGroup(std::optional<Decimal> md_entry_px_optional_ex, std::optional<std::uint64_t> md_entry_size_optional, std::int32_t security_id, std::uint32_t rpt_seq, std::optional<std::int32_t> number_of_orders_optional, std::uint8_t md_price_level, MdUpdateAction md_update_action, MdEntryTypeBook md_entry_type_book, const std::array<std::byte, 1>& padding_1);

    // Md Entry Px Optional Ex: Workup price
    std::optional<Decimal> md_entry_px_optional_ex() const;
    void set_md_entry_px_optional_ex(std::optional<Decimal> value);

    // Md Entry Size Optional: Aggregate booked qty at price level, notional
    std::optional<std::uint64_t> md_entry_size_optional() const;
    void set_md_entry_size_optional(std::optional<std::uint64_t> value);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Rpt Seq: Sequence number of the last Market Data entry processed for the instrument
    std::uint32_t rpt_seq() const;
    void set_rpt_seq(std::uint32_t value);

    // Number Of Orders Optional: In Book entry - aggregate number of orders at given price
    // level
    std::optional<std::int32_t> number_of_orders_optional() const;
    void set_number_of_orders_optional(std::optional<std::int32_t> value);

    // Md Price Level: Aggregate book level
    std::uint8_t md_price_level() const;
    void set_md_price_level(std::uint8_t value);

    // Md Update Action: Market Data update action
    MdUpdateAction md_update_action() const;
    void set_md_update_action(MdUpdateAction value);

    // Md Entry Type Book: Market Data entry type
    MdEntryTypeBook md_entry_type_book() const;
    void set_md_entry_type_book(MdEntryTypeBook value);

    // Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& padding_1() const;
    std::array<std::byte, 1>& padding_1();
    void set_padding_1(const std::array<std::byte, 1>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshBookLongGroup& other) const;
    bool operator!=(const IncrementalRefreshBookLongGroup& other) const;

  private:
    std::optional<Decimal> md_entry_px_optional_ex_{};
    std::optional<std::uint64_t> md_entry_size_optional_{};
    std::int32_t security_id_{};
    std::uint32_t rpt_seq_{};
    std::optional<std::int32_t> number_of_orders_optional_{};
    std::uint8_t md_price_level_{};
    MdUpdateAction md_update_action_{};
    MdEntryTypeBook md_entry_type_book_{};
    std::array<std::byte, 1> padding_1_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookLongGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
