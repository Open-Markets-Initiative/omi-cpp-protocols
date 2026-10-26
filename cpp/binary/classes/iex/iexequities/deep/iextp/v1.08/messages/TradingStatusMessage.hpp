#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/TradingStatus.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

class Visitor;

// The Trading Status Message is used to indicate the current trading status of a security.
class TradingStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradingStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 21;

    TradingStatusMessage() = default;
    TradingStatusMessage(TradingStatus trading_status, std::chrono::nanoseconds timestamp, const std::string& symbol, const std::string& reason);

    // Trading Status: Trading status identifier
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Reason: Reason for the trading status change
    const std::string& reason() const;
    std::string& reason();
    void set_reason(const std::string& value);

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

    bool operator==(const TradingStatusMessage& other) const;
    bool operator!=(const TradingStatusMessage& other) const;

  private:
    TradingStatus trading_status_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
    std::string reason_{};
};

} // namespace iex::iexequities::deep::iextp::v1_08
