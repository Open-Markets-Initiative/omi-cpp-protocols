#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/CurrentTradingState.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

class Visitor;

// ISE uses this administrative message to indicate the current trading status of a strategy
// within the ISE Options Market.
class StrategyTradingActionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StrategyTradingActionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 11;

    StrategyTradingActionMessage() = default;
    StrategyTradingActionMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, CurrentTradingState current_trading_state);

    // Timestamp: The time, expressed as the number of nanoseconds after midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Strategy Id: ISE’s Strategy ID assigned daily, valid while there are any open complex
    // orders for the day
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Current Trading State: Reflects the current trading state for the strategy on the ISE
    // market.
    CurrentTradingState current_trading_state() const;
    void set_current_trading_state(CurrentTradingState value);

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

    bool operator==(const StrategyTradingActionMessage& other) const;
    bool operator!=(const StrategyTradingActionMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t strategy_id_{};
    CurrentTradingState current_trading_state_{};
};

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
