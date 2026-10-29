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

namespace eurex::t7::eobi::fbe::v3_0 {

class Visitor;

// Execution Summary
class ExecutionSummary : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExecutionSummary;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 56;

    ExecutionSummary() = default;
    ExecutionSummary(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> aggressor_timestamp, std::optional<std::chrono::nanoseconds> request_time, std::optional<std::chrono::nanoseconds> exec_id, std::optional<std::int32_t> last_qty, std::optional<AggressorSide> aggressor_side, std::optional<TradeCondition> trade_condition, const std::array<std::byte, 2>& pad2, std::optional<Decimal> last_px, std::optional<std::int32_t> resting_hidden_qty, std::optional<std::int32_t> resting_cxl_qty);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Aggressor Timestamp:
    std::optional<std::chrono::nanoseconds> aggressor_timestamp() const;
    void set_aggressor_timestamp(std::optional<std::chrono::nanoseconds> value);

    // Request Time:
    std::optional<std::chrono::nanoseconds> request_time() const;
    void set_request_time(std::optional<std::chrono::nanoseconds> value);

    // Exec Id:
    std::optional<std::chrono::nanoseconds> exec_id() const;
    void set_exec_id(std::optional<std::chrono::nanoseconds> value);

    // Last Qty:
    std::optional<std::int32_t> last_qty() const;
    void set_last_qty(std::optional<std::int32_t> value);

    // Aggressor Side:
    std::optional<AggressorSide> aggressor_side() const;
    void set_aggressor_side(std::optional<AggressorSide> value);

    // Trade Condition:
    std::optional<TradeCondition> trade_condition() const;
    void set_trade_condition(std::optional<TradeCondition> value);

    // Pad2:
    const std::array<std::byte, 2>& pad2() const;
    std::array<std::byte, 2>& pad2();
    void set_pad2(const std::array<std::byte, 2>& value);

    // Last Px:
    std::optional<Decimal> last_px() const;
    void set_last_px(std::optional<Decimal> value);

    // Resting Hidden Qty:
    std::optional<std::int32_t> resting_hidden_qty() const;
    void set_resting_hidden_qty(std::optional<std::int32_t> value);

    // Resting Cxl Qty:
    std::optional<std::int32_t> resting_cxl_qty() const;
    void set_resting_cxl_qty(std::optional<std::int32_t> value);

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
    std::optional<std::chrono::nanoseconds> aggressor_timestamp_{};
    std::optional<std::chrono::nanoseconds> request_time_{};
    std::optional<std::chrono::nanoseconds> exec_id_{};
    std::optional<std::int32_t> last_qty_{};
    std::optional<AggressorSide> aggressor_side_{};
    std::optional<TradeCondition> trade_condition_{};
    std::array<std::byte, 2> pad2_{};
    std::optional<Decimal> last_px_{};
    std::optional<std::int32_t> resting_hidden_qty_{};
    std::optional<std::int32_t> resting_cxl_qty_{};
};

} // namespace eurex::t7::eobi::fbe::v3_0
