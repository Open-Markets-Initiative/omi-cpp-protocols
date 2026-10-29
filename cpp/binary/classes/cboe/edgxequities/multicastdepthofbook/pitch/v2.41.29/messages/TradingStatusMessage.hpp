#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/RegShoAction.hpp"
#include "../enums/TradingStatus.hpp"
#include "../messages/Message.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

class Visitor;

// The Trading Status message is used to indicate the current trading status of a complex
// instrument.
class TradingStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradingStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    TradingStatusMessage() = default;
    TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& symbol_long, TradingStatus trading_status, RegShoAction reg_sho_action, const std::array<std::byte, 2>& padding);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol Long: Symbol
    const std::string& symbol_long() const;
    std::string& symbol_long();
    void set_symbol_long(const std::string& value);

    // Trading Status: Trading Status
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Reg Sho Action: Reg SHO Action Values
    RegShoAction reg_sho_action() const;
    void set_reg_sho_action(RegShoAction value);

    // Padding: Reserved
    const std::array<std::byte, 2>& padding() const;
    std::array<std::byte, 2>& padding();
    void set_padding(const std::array<std::byte, 2>& value);

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
    std::array<std::byte, 2> padding_{};
};

} // namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29
