#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/AggressorSide.hpp"
#include "../enums/MdUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// Number of Trade Summary entries
class IncrementalRefreshTradeSummaryGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    IncrementalRefreshTradeSummaryGroup() = default;
    IncrementalRefreshTradeSummaryGroup(Decimal md_entry_px_ex, std::int32_t md_entry_size_short, std::int32_t security_id, std::uint32_t rpt_seq, std::int32_t number_of_orders, std::optional<AggressorSide> aggressor_side, MdUpdateAction md_update_action, std::optional<std::uint32_t> md_trade_entry_id, const std::array<std::byte, 2>& padding_2);

    // Md Entry Px Ex: Trade price
    Decimal md_entry_px_ex() const;
    void set_md_entry_px_ex(Decimal value);

    // Md Entry Size Short: Cumulative traded volume
    std::int32_t md_entry_size_short() const;
    void set_md_entry_size_short(std::int32_t value);

    // Security Id: Unique instrument ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Rpt Seq: Sequence number of the last Market Data entry processed for the instrument
    std::uint32_t rpt_seq() const;
    void set_rpt_seq(std::uint32_t value);

    // Number Of Orders: The total number of real orders per instrument that participated in a
    // match step within a match event
    std::int32_t number_of_orders() const;
    void set_number_of_orders(std::int32_t value);

    // Aggressor Side: Indicates which side is the aggressor or if there is no aggressor
    std::optional<AggressorSide> aggressor_side() const;
    void set_aggressor_side(std::optional<AggressorSide> value);

    // Md Update Action: Market Data update action
    MdUpdateAction md_update_action() const;
    void set_md_update_action(MdUpdateAction value);

    // Md Trade Entry Id: Market Data Trade entry ID
    std::optional<std::uint32_t> md_trade_entry_id() const;
    void set_md_trade_entry_id(std::optional<std::uint32_t> value);

    // Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& padding_2() const;
    std::array<std::byte, 2>& padding_2();
    void set_padding_2(const std::array<std::byte, 2>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshTradeSummaryGroup& other) const;
    bool operator!=(const IncrementalRefreshTradeSummaryGroup& other) const;

  private:
    Decimal md_entry_px_ex_{ 0, -9 };
    std::int32_t md_entry_size_short_{};
    std::int32_t security_id_{};
    std::uint32_t rpt_seq_{};
    std::int32_t number_of_orders_{};
    std::optional<AggressorSide> aggressor_side_{};
    MdUpdateAction md_update_action_{};
    std::optional<std::uint32_t> md_trade_entry_id_{};
    std::array<std::byte, 2> padding_2_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_9
