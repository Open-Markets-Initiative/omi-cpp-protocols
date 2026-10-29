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

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

class Visitor;

// The Trading Status message is used to indicate the current trading status of a security. A
// Trading Status message will be sent whenever a security’s trading status changes.
class TradingStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradingStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    TradingStatusMessage() = default;
    TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& expanded_symbol, TradingStatus trading_status, RegShoAction reg_sho_action, const std::array<std::byte, 1>& reserved_1, const std::array<std::byte, 1>& second_reserved_1);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Expanded Symbol: Symbol right padded with spaces.
    const std::string& expanded_symbol() const;
    std::string& expanded_symbol();
    void set_expanded_symbol(const std::string& value);

    // Trading Status: A, H, Q, S, T
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Reg Sho Action: 0, 1
    RegShoAction reg_sho_action() const;
    void set_reg_sho_action(RegShoAction value);

    // Reserved 1: Reserved
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Second Reserved 1: Reserved
    const std::array<std::byte, 1>& second_reserved_1() const;
    std::array<std::byte, 1>& second_reserved_1();
    void set_second_reserved_1(const std::array<std::byte, 1>& value);

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
    std::string expanded_symbol_{};
    TradingStatus trading_status_{};
    RegShoAction reg_sho_action_{};
    std::array<std::byte, 1> reserved_1_{};
    std::array<std::byte, 1> second_reserved_1_{};
};

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
