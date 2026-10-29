#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

class Visitor;

// The ticker message is used to send real time trade information
class ComplexStrategyTickerMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ComplexStrategyTickerMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 51;

    ComplexStrategyTickerMessage() = default;
    ComplexStrategyTickerMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, Decimal last_price, std::uint32_t size, std::uint32_t volume, std::uint64_t high, std::uint64_t low, std::uint64_t first, char trade_condition);

    // Timestamp: The time, expressed as the number of nanoseconds after midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Strategy Id: ISE’s Strategy ID assigned daily, valid while there are any open complex
    // orders for the day
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Last Price: Most recent price.
    Decimal last_price() const;
    void set_last_price(Decimal value);

    // Size: Aggregated number of contracts on the bid or ask side being displayed in the
    // options market at the current time.
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Volume: Total traded quantity.
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // High: High price for the day.
    std::uint64_t high() const;
    void set_high(std::uint64_t value);

    // Low: Low price for the day.
    std::uint64_t low() const;
    void set_low(std::uint64_t value);

    // First: Opening price for the day
    std::uint64_t first() const;
    void set_first(std::uint64_t value);

    // Trade Condition: Same value as the Trade Condition sent to OPRA for this trade. To
    // obtain a list of Trade Conditions, refer to the NOTES below.
    char trade_condition() const;
    void set_trade_condition(char value);

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

    bool operator==(const ComplexStrategyTickerMessage& other) const;
    bool operator!=(const ComplexStrategyTickerMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t strategy_id_{};
    Decimal last_price_{ 0, -8 };
    std::uint32_t size_{};
    std::uint32_t volume_{};
    std::uint64_t high_{};
    std::uint64_t low_{};
    std::uint64_t first_{};
    char trade_condition_{};
};

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
