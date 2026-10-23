#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/MdEntryTypeStatistics.hpp"
#include "../enums/MdUpdateAction.hpp"
#include "../enums/OpenCloseSettlFlag.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// Number of entries in Market Data message
class IncrementalRefreshSessionStatisticsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 24;

    IncrementalRefreshSessionStatisticsGroup() = default;
    IncrementalRefreshSessionStatisticsGroup(Decimal md_entry_px_ex, std::int32_t security_id, std::uint32_t rpt_seq, std::optional<OpenCloseSettlFlag> open_close_settl_flag, MdUpdateAction md_update_action, MdEntryTypeStatistics md_entry_type_statistics, std::optional<std::int32_t> md_entry_size_short_optional, const std::array<std::byte, 1>& padding_1);

    // Md Entry Px Ex: Trade price
    Decimal md_entry_px_ex() const;
    void set_md_entry_px_ex(Decimal value);

    // Security Id: Unique instrument ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Rpt Seq: Sequence number of the last Market Data entry processed for the instrument
    std::uint32_t rpt_seq() const;
    void set_rpt_seq(std::uint32_t value);

    // Open Close Settl Flag: Flag describing IOP and Open Price entries
    std::optional<OpenCloseSettlFlag> open_close_settl_flag() const;
    void set_open_close_settl_flag(std::optional<OpenCloseSettlFlag> value);

    // Md Update Action: Market Data update action
    MdUpdateAction md_update_action() const;
    void set_md_update_action(MdUpdateAction value);

    // Md Entry Type Statistics: Market Data entry type
    MdEntryTypeStatistics md_entry_type_statistics() const;
    void set_md_entry_type_statistics(MdEntryTypeStatistics value);

    // Md Entry Size Short Optional: Market Data entry size
    std::optional<std::int32_t> md_entry_size_short_optional() const;
    void set_md_entry_size_short_optional(std::optional<std::int32_t> value);

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

    bool operator==(const IncrementalRefreshSessionStatisticsGroup& other) const;
    bool operator!=(const IncrementalRefreshSessionStatisticsGroup& other) const;

  private:
    Decimal md_entry_px_ex_{ 0, -9 };
    std::int32_t security_id_{};
    std::uint32_t rpt_seq_{};
    std::optional<OpenCloseSettlFlag> open_close_settl_flag_{};
    MdUpdateAction md_update_action_{};
    MdEntryTypeStatistics md_entry_type_statistics_{};
    std::optional<std::int32_t> md_entry_size_short_optional_{};
    std::array<std::byte, 1> padding_1_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshSessionStatisticsGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_9
