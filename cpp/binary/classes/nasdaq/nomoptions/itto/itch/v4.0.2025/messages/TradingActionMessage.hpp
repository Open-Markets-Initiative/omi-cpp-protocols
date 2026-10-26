#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/CurrentTradingState.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class SequencedMessageVisitor;

// After the start of system hours, NASDAQ will use the Trading Action message to relay changes
// in trading status for an individual option. Messages will be sent when an option is halted,
// is released for quotation, released for trading, or temporarily suspended for trading on the
// buy or sell side.
class TradingActionMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::TradingActionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    TradingActionMessage() = default;
    TradingActionMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t option_id, CurrentTradingState current_trading_state);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Option Id: Option ID assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Current Trading State: Reflects the current trading state for the options security in
    // the NASDAQ Options Market. The allowable values are:
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
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t option_id_{};
    CurrentTradingState current_trading_state_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
