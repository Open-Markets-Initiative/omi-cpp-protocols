#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../bitfields/SettlPriceType.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdEntryType.hpp"
#include "../enums/OpenCloseSettlFlag.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of entries in Market Data message
class SnapshotFullRefreshGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 22;

    SnapshotFullRefreshGroup() = default;
    SnapshotFullRefreshGroup(std::optional<Decimal> md_entry_px_optional_ex, std::optional<std::int32_t> md_entry_size_short_optional, std::optional<std::int32_t> number_of_orders_optional, std::optional<std::int8_t> md_price_level_optional, std::optional<std::uint16_t> trading_reference_date, std::optional<OpenCloseSettlFlag> open_close_settl_flag, const SettlPriceType& settl_price_type, MdEntryType md_entry_type);

    // Md Entry Px Optional Ex: Workup price
    std::optional<Decimal> md_entry_px_optional_ex() const;
    void set_md_entry_px_optional_ex(std::optional<Decimal> value);

    // Md Entry Size Short Optional: Market Data entry size
    std::optional<std::int32_t> md_entry_size_short_optional() const;
    void set_md_entry_size_short_optional(std::optional<std::int32_t> value);

    // Number Of Orders Optional: In Book entry - aggregate number of orders at given price
    // level
    std::optional<std::int32_t> number_of_orders_optional() const;
    void set_number_of_orders_optional(std::optional<std::int32_t> value);

    // Md Price Level Optional: Aggregate book position
    std::optional<std::int8_t> md_price_level_optional() const;
    void set_md_price_level_optional(std::optional<std::int8_t> value);

    // Trading Reference Date: Indicates session date corresponding to the settlement price in
    // tag 1150-TradingReferencePrice
    std::optional<std::uint16_t> trading_reference_date() const;
    void set_trading_reference_date(std::optional<std::uint16_t> value);

    // Open Close Settl Flag: Flag describing IOP and Open Price entries
    std::optional<OpenCloseSettlFlag> open_close_settl_flag() const;
    void set_open_close_settl_flag(std::optional<OpenCloseSettlFlag> value);

    // Settl Price Type: SettlPriceType bit set
    const SettlPriceType& settl_price_type() const;
    SettlPriceType& settl_price_type();
    void set_settl_price_type(const SettlPriceType& value);

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

    bool operator==(const SnapshotFullRefreshGroup& other) const;
    bool operator!=(const SnapshotFullRefreshGroup& other) const;

  private:
    std::optional<Decimal> md_entry_px_optional_ex_{};
    std::optional<std::int32_t> md_entry_size_short_optional_{};
    std::optional<std::int32_t> number_of_orders_optional_{};
    std::optional<std::int8_t> md_price_level_optional_{};
    std::optional<std::uint16_t> trading_reference_date_{};
    std::optional<OpenCloseSettlFlag> open_close_settl_flag_{};
    SettlPriceType settl_price_type_{};
    MdEntryType md_entry_type_{};
};

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
