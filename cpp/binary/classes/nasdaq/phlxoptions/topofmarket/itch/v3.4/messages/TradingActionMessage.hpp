#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/CurrentTradingState.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

class SequencedMessageVisitor;

// The options system uses this administrative message to indicate the current trading status
// of an index or equity option within the options market.
class TradingActionMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::TradingActionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    TradingActionMessage() = default;
    TradingActionMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, CurrentTradingState current_trading_state);

    // Nanoseconds: The sub-second portion of the time, in nanoseconds (0-999999999). The
    // second portion of the time is obtained from the most recent timestamp message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Option Id: Option ID for this option, assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Current Trading State: Reflects the current trading state for the option in the options
    // market.
    CurrentTradingState current_trading_state() const;
    void set_current_trading_state(CurrentTradingState value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const TradingActionMessage& other) const;
    bool operator!=(const TradingActionMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t option_id_{};
    CurrentTradingState current_trading_state_{};
};

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
