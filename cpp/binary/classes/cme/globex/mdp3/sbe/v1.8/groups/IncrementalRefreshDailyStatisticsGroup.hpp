#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../bitfields/SettlPriceType.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdEntryTypeDailyStatistics.hpp"
#include "../enums/MdUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of entries in Market Data message
class IncrementalRefreshDailyStatisticsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    IncrementalRefreshDailyStatisticsGroup() = default;
    IncrementalRefreshDailyStatisticsGroup(std::optional<Decimal> md_entry_px_optional, std::optional<std::int32_t> md_entry_size_optional, std::int32_t security_id, std::uint32_t rpt_seq, std::optional<std::uint16_t> trading_reference_date, const SettlPriceType& settl_price_type, MdUpdateAction md_update_action, MdEntryTypeDailyStatistics md_entry_type_daily_statistics, const std::array<std::byte, 7>& padding_7);

    // Md Entry Px Optional: Market Data entry price
    std::optional<Decimal> md_entry_px_optional() const;
    void set_md_entry_px_optional(std::optional<Decimal> value);

    // Md Entry Size Optional: Market Data entry size
    std::optional<std::int32_t> md_entry_size_optional() const;
    void set_md_entry_size_optional(std::optional<std::int32_t> value);

    // Security Id: Unique instrument ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Rpt Seq: Sequence number of the last Market Data entry processed for the instrument
    std::uint32_t rpt_seq() const;
    void set_rpt_seq(std::uint32_t value);

    // Trading Reference Date: Indicates session date corresponding to the settlement price in
    // tag 1150-TradingReferencePrice
    std::optional<std::uint16_t> trading_reference_date() const;
    void set_trading_reference_date(std::optional<std::uint16_t> value);

    // Settl Price Type: SettlPriceType bit set
    const SettlPriceType& settl_price_type() const;
    SettlPriceType& settl_price_type();
    void set_settl_price_type(const SettlPriceType& value);

    // Md Update Action: Market Data update action
    MdUpdateAction md_update_action() const;
    void set_md_update_action(MdUpdateAction value);

    // Md Entry Type Daily Statistics: Market Data entry type
    MdEntryTypeDailyStatistics md_entry_type_daily_statistics() const;
    void set_md_entry_type_daily_statistics(MdEntryTypeDailyStatistics value);

    // Padding 7: 7 bytes padding
    const std::array<std::byte, 7>& padding_7() const;
    std::array<std::byte, 7>& padding_7();
    void set_padding_7(const std::array<std::byte, 7>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshDailyStatisticsGroup& other) const;
    bool operator!=(const IncrementalRefreshDailyStatisticsGroup& other) const;

  private:
    std::optional<Decimal> md_entry_px_optional_{};
    std::optional<std::int32_t> md_entry_size_optional_{};
    std::int32_t security_id_{};
    std::uint32_t rpt_seq_{};
    std::optional<std::uint16_t> trading_reference_date_{};
    SettlPriceType settl_price_type_{};
    MdUpdateAction md_update_action_{};
    MdEntryTypeDailyStatistics md_entry_type_daily_statistics_{};
    std::array<std::byte, 7> padding_7_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshDailyStatisticsGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_8
