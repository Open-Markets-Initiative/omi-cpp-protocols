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
#include "../enums/AggressorSide.hpp"
#include "../enums/TradeCondition.hpp"
#include "../messages/Message.hpp"
#include "../structs/RemainingOrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class Visitor;

// Execution Summary
class ExecutionSummary : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExecutionSummary;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 96;

    ExecutionSummary() = default;
    ExecutionSummary(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> request_time, std::optional<std::chrono::nanoseconds> exec_id, std::optional<Decimal> last_qty, std::optional<AggressorSide> aggressor_side, const std::array<std::byte, 1>& pad1, std::optional<TradeCondition> trade_condition, std::optional<std::uint8_t> trading_hhi_indicator, const std::array<std::byte, 3>& pad3, std::optional<Decimal> last_px, const RemainingOrderDetailsComp& remaining_order_details_comp, std::optional<Decimal> resting_hidden_qty, std::optional<Decimal> resting_cxl_qty, std::optional<std::chrono::nanoseconds> aggressor_time);

    // Security Id: Unique instrument identifier
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Request Time:
    std::optional<std::chrono::nanoseconds> request_time() const;
    void set_request_time(std::optional<std::chrono::nanoseconds> value);

    // Exec Id:
    std::optional<std::chrono::nanoseconds> exec_id() const;
    void set_exec_id(std::optional<std::chrono::nanoseconds> value);

    // Last Qty: Total executed matched quantity of this match event
    std::optional<Decimal> last_qty() const;
    void set_last_qty(std::optional<Decimal> value);

    // Aggressor Side:
    std::optional<AggressorSide> aggressor_side() const;
    void set_aggressor_side(std::optional<AggressorSide> value);

    // Pad1:
    const std::array<std::byte, 1>& pad1() const;
    std::array<std::byte, 1>& pad1();
    void set_pad1(const std::array<std::byte, 1>& value);

    // Trade Condition:
    std::optional<TradeCondition> trade_condition() const;
    void set_trade_condition(std::optional<TradeCondition> value);

    // Trading Hhi Indicator:
    std::optional<std::uint8_t> trading_hhi_indicator() const;
    void set_trading_hhi_indicator(std::optional<std::uint8_t> value);

    // Pad3:
    const std::array<std::byte, 3>& pad3() const;
    std::array<std::byte, 3>& pad3();
    void set_pad3(const std::array<std::byte, 3>& value);

    // Last Px:
    std::optional<Decimal> last_px() const;
    void set_last_px(std::optional<Decimal> value);

    // Remaining Order Details Comp:
    const RemainingOrderDetailsComp& remaining_order_details_comp() const;
    RemainingOrderDetailsComp& remaining_order_details_comp();
    void set_remaining_order_details_comp(const RemainingOrderDetailsComp& value);

    // Resting Hidden Qty:
    std::optional<Decimal> resting_hidden_qty() const;
    void set_resting_hidden_qty(std::optional<Decimal> value);

    // Resting Cxl Qty:
    std::optional<Decimal> resting_cxl_qty() const;
    void set_resting_cxl_qty(std::optional<Decimal> value);

    // Aggressor Time:
    std::optional<std::chrono::nanoseconds> aggressor_time() const;
    void set_aggressor_time(std::optional<std::chrono::nanoseconds> value);

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

    bool operator==(const ExecutionSummary& other) const;
    bool operator!=(const ExecutionSummary& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<std::chrono::nanoseconds> request_time_{};
    std::optional<std::chrono::nanoseconds> exec_id_{};
    std::optional<Decimal> last_qty_{};
    std::optional<AggressorSide> aggressor_side_{};
    std::array<std::byte, 1> pad1_{};
    std::optional<TradeCondition> trade_condition_{};
    std::optional<std::uint8_t> trading_hhi_indicator_{};
    std::array<std::byte, 3> pad3_{};
    std::optional<Decimal> last_px_{};
    RemainingOrderDetailsComp remaining_order_details_comp_{};
    std::optional<Decimal> resting_hidden_qty_{};
    std::optional<Decimal> resting_cxl_qty_{};
    std::optional<std::chrono::nanoseconds> aggressor_time_{};
};

} // namespace eurex::t7::eobi::fbe::v15_0
