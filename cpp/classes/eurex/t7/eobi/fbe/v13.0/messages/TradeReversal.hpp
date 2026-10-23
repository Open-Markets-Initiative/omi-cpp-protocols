#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/MdOriginType.hpp"
#include "../enums/TradeCondition.hpp"
#include "../groups/MdTradeEntryGrpComp.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class Visitor;

// Trade Reversal
class TradeReversal : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::TradeReversal;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 408;

    TradeReversal() = default;
    TradeReversal(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, std::optional<Decimal> last_qty, std::optional<Decimal> last_px, std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time, std::optional<std::uint32_t> trd_match_id, std::optional<TradeCondition> trade_condition, std::optional<MdOriginType> md_origin_type, std::optional<std::uint8_t> no_md_entries, const std::array<MdTradeEntryGrpComp, 15>& md_trade_entry_grp_comp);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Last Qty:
    std::optional<Decimal> last_qty() const;
    void set_last_qty(std::optional<Decimal> value);

    // Last Px:
    std::optional<Decimal> last_px() const;
    void set_last_px(std::optional<Decimal> value);

    // Trd Reg Ts Execution Time:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time() const;
    void set_trd_reg_ts_execution_time(std::optional<std::chrono::nanoseconds> value);

    // Trd Match Id:
    std::optional<std::uint32_t> trd_match_id() const;
    void set_trd_match_id(std::optional<std::uint32_t> value);

    // Trade Condition:
    std::optional<TradeCondition> trade_condition() const;
    void set_trade_condition(std::optional<TradeCondition> value);

    // Md Origin Type:
    std::optional<MdOriginType> md_origin_type() const;
    void set_md_origin_type(std::optional<MdOriginType> value);

    // No Md Entries:
    std::optional<std::uint8_t> no_md_entries() const;
    void set_no_md_entries(std::optional<std::uint8_t> value);

    // Md Trade Entry Grp Comp:
    const std::array<MdTradeEntryGrpComp, 15>& md_trade_entry_grp_comp() const;
    std::array<MdTradeEntryGrpComp, 15>& md_trade_entry_grp_comp();
    void set_md_trade_entry_grp_comp(const std::array<MdTradeEntryGrpComp, 15>& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const TradeReversal& other) const;
    bool operator!=(const TradeReversal& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::optional<Decimal> last_qty_{};
    std::optional<Decimal> last_px_{};
    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time_{};
    std::optional<std::uint32_t> trd_match_id_{};
    std::optional<TradeCondition> trade_condition_{};
    std::optional<MdOriginType> md_origin_type_{};
    std::optional<std::uint8_t> no_md_entries_{};
    std::array<MdTradeEntryGrpComp, 15> md_trade_entry_grp_comp_{};
};

} // namespace eurex::t7::eobi::fbe::v13_0
