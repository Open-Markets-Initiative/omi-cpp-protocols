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

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published whenever an incoming order is executed, carrying information on the execution of
// that incoming order.
class ExecutionSummaryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExecutionSummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 56;

    ExecutionSummaryMessage() = default;
    ExecutionSummaryMessage(std::int64_t security_id, std::optional<std::chrono::nanoseconds> aggressor_timestamp, std::chrono::nanoseconds exec_id, std::int64_t last_qty, AggressorSide aggressor_side, std::optional<TradeCondition> trade_condition, const std::array<std::byte, 6>& pad_6, Decimal last_px, std::optional<std::int64_t> resting_hidden_qty);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Aggressor Timestamp: Always identical to the matching engine in timestamp.
    std::optional<std::chrono::nanoseconds> aggressor_timestamp() const;
    void set_aggressor_timestamp(std::optional<std::chrono::nanoseconds> value);

    // Exec Id: Matching timestamp.
    std::chrono::nanoseconds exec_id() const;
    void set_exec_id(std::chrono::nanoseconds value);

    // Last Qty: The potential matchable quantity for the auction.
    std::int64_t last_qty() const;
    void set_last_qty(std::int64_t value);

    // Aggressor Side: Side of the incoming order.
    AggressorSide aggressor_side() const;
    void set_aggressor_side(AggressorSide value);

    // Trade Condition: Indicates whether a synthetic match is occured.
    std::optional<TradeCondition> trade_condition() const;
    void set_trade_condition(std::optional<TradeCondition> value);

    // Pad 6: not used
    const std::array<std::byte, 6>& pad_6() const;
    std::array<std::byte, 6>& pad_6();
    void set_pad_6(const std::array<std::byte, 6>& value);

    // Last Px: Indicating the potential Auction price for a crossed order book.
    Decimal last_px() const;
    void set_last_px(Decimal value);

    // Resting Hidden Qty: Quantity of matched passive orders that is not displayed to the
    // market.
    std::optional<std::int64_t> resting_hidden_qty() const;
    void set_resting_hidden_qty(std::optional<std::int64_t> value);

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

    bool operator==(const ExecutionSummaryMessage& other) const;
    bool operator!=(const ExecutionSummaryMessage& other) const;

  private:
    std::int64_t security_id_{};
    std::optional<std::chrono::nanoseconds> aggressor_timestamp_{};
    std::chrono::nanoseconds exec_id_{};
    std::int64_t last_qty_{};
    AggressorSide aggressor_side_{};
    std::optional<TradeCondition> trade_condition_{};
    std::array<std::byte, 6> pad_6_{};
    Decimal last_px_{ 0, -6 };
    std::optional<std::int64_t> resting_hidden_qty_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
