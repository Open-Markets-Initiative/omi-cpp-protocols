#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/AggressorSide.hpp"
#include "../enums/MdUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of Trade Summary entries
class IncrementalRefreshTradeSummaryLongGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 40;

    IncrementalRefreshTradeSummaryLongGroup() = default;
    IncrementalRefreshTradeSummaryLongGroup(Decimal md_entry_px_ex, std::uint64_t md_entry_size, std::int32_t security_id, std::uint32_t rpt_seq, std::int32_t number_of_orders, std::uint32_t md_trade_entry, std::optional<AggressorSide> aggressor_side, MdUpdateAction md_update_action, const std::array<std::byte, 6>& padding_6);

    // Md Entry Px Ex: Trade price
    Decimal md_entry_px_ex() const;
    void set_md_entry_px_ex(Decimal value);

    // Md Entry Size: Consolidated trade quantity, notional
    std::uint64_t md_entry_size() const;
    void set_md_entry_size(std::uint64_t value);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Rpt Seq: Sequence number of the last Market Data entry processed for the instrument
    std::uint32_t rpt_seq() const;
    void set_rpt_seq(std::uint32_t value);

    // Number Of Orders: The total number of real orders per instrument that participated in a
    // match step within a match event
    std::int32_t number_of_orders() const;
    void set_number_of_orders(std::int32_t value);

    // Md Trade Entry: Market Data Trade Entry ID
    std::uint32_t md_trade_entry() const;
    void set_md_trade_entry(std::uint32_t value);

    // Aggressor Side: Indicates which side is the aggressor or if there is no aggressor
    std::optional<AggressorSide> aggressor_side() const;
    void set_aggressor_side(std::optional<AggressorSide> value);

    // Md Update Action: Market Data update action
    MdUpdateAction md_update_action() const;
    void set_md_update_action(MdUpdateAction value);

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

    bool operator==(const IncrementalRefreshTradeSummaryLongGroup& other) const;
    bool operator!=(const IncrementalRefreshTradeSummaryLongGroup& other) const;

  private:
    Decimal md_entry_px_ex_{ 0, -9 };
    std::uint64_t md_entry_size_{};
    std::int32_t security_id_{};
    std::uint32_t rpt_seq_{};
    std::int32_t number_of_orders_{};
    std::uint32_t md_trade_entry_{};
    std::optional<AggressorSide> aggressor_side_{};
    MdUpdateAction md_update_action_{};
    std::array<std::byte, 6> padding_6_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryLongGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
