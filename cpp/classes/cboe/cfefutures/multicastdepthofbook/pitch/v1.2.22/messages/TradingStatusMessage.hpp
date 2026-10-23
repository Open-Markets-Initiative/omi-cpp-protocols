#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/TradingStatus.hpp"
#include "../messages/Message.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

class Visitor;

// The Trading Status message is used to indicate the current trading status of a Futures
// contract.
class TradingStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradingStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    TradingStatusMessage() = default;
    TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, const std::string& reserved_2, TradingStatus trading_status, const std::string& reserved_3);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol: Six character, base 62 symbol.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Reserved 2: Reserved
    const std::string& reserved_2() const;
    std::string& reserved_2();
    void set_reserved_2(const std::string& value);

    // Trading Status: Trading Status Values
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Reserved 3: Reserved
    const std::string& reserved_3() const;
    std::string& reserved_3();
    void set_reserved_3(const std::string& value);

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
    std::chrono::nanoseconds time_offset_{};
    std::string symbol_{};
    std::string reserved_2_{};
    TradingStatus trading_status_{};
    std::string reserved_3_{};
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
