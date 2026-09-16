#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/ReasonCode.hpp"
#include "../enums/TradingState.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// Nasdaq uses this administrative message to indicate the current trading status of a security
// to the trading community
class StockTradingActionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StockTradingActionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    StockTradingActionMessage() = default;
    StockTradingActionMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, TradingState trading_state, char reserved, const std::string& reason_code);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Trading State: Indicates the current trading state for the stock
    TradingState trading_state() const;
    void set_trading_state(TradingState value);

    // Reserved: Reserved
    char reserved() const;
    void set_reserved(char value);

    // Reason Code: Trading Action reason
    const std::string& reason_code() const;
    std::string& reason_code();
    void set_reason_code(const std::string& value);

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

    bool operator==(const StockTradingActionMessage& other) const;
    bool operator!=(const StockTradingActionMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::string stock_{};
    TradingState trading_state_{};
    char reserved_{};
    std::string reason_code_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
