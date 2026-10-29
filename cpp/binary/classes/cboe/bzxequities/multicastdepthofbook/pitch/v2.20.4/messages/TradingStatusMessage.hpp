#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/RegShoAction.hpp"
#include "../enums/TradingStatus.hpp"
#include "../messages/Message.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

class Visitor;

// Trading Status message
class TradingStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradingStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    TradingStatusMessage() = default;
    TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& symbol_long, TradingStatus trading_status, RegShoAction reg_sho_action, char reserved_1, char second_reserved_1);

    // Time Offset: Nanosecond offset from last
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol Long: Symbol right padded with spaces
    const std::string& symbol_long() const;
    std::string& symbol_long();
    void set_symbol_long(const std::string& value);

    // Trading Status: "H" = Halted "Q" = Quote-Only "T" = Trading Reg SHO
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Reg Sho Action: "0" = No price test in effect "1" = Reg SHO price test restriction in
    // effect
    RegShoAction reg_sho_action() const;
    void set_reg_sho_action(RegShoAction value);

    // Reserved 1: Reserved
    char reserved_1() const;
    void set_reserved_1(char value);

    // Second Reserved 1: Reserved
    char second_reserved_1() const;
    void set_second_reserved_1(char value);

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
    std::string symbol_long_{};
    TradingStatus trading_status_{};
    RegShoAction reg_sho_action_{};
    char reserved_1_{};
    char second_reserved_1_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
