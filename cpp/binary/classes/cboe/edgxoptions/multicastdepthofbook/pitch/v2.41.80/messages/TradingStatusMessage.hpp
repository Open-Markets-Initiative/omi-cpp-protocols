#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/GthTradingStatus.hpp"
#include "../enums/TradingStatus.hpp"
#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// The Trading Status message is used to indicate the current trading status of a security. A
// Trading Status message will be sent whenever a security's trading status changes. The
// Trading Status field will be used to represent the status of the RTH (9:30 a.m. ET - 4:15
// p.m. ET) and Curb sessions. The GTH Trading Status field will be used to represent the
// status of series that trade during the GTH session. The GTH session runs from 8:15 p.m. to
// 9:25 a.m. ET for GTH-eligible Products (C1 Options Only).
class TradingStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradingStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    TradingStatusMessage() = default;
    TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, const std::array<std::byte, 2>& reserved_2, TradingStatus trading_status, const std::array<std::byte, 1>& reserved_1, GthTradingStatus gth_trading_status, const std::array<std::byte, 1>& second_reserved_1);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Symbol: Symbol right padded with spaces.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Reserved 2: Reserved.
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

    // Trading Status: H = Halted, L = Curb Trading (C1 Only), Q = Quote-Only, R = Opening
    // Rotation, T = RTH Trading.
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Reserved 1: Reserved.
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Gth Trading Status: C1 Only. H = Halted, Q = Quote-Only, R = Opening Rotation, T =
    // Trading.
    GthTradingStatus gth_trading_status() const;
    void set_gth_trading_status(GthTradingStatus value);

    // Second Reserved 1: Reserved.
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
    std::string symbol_{};
    std::array<std::byte, 2> reserved_2_{};
    TradingStatus trading_status_{};
    std::array<std::byte, 1> reserved_1_{};
    GthTradingStatus gth_trading_status_{};
    std::array<std::byte, 1> second_reserved_1_{};
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
