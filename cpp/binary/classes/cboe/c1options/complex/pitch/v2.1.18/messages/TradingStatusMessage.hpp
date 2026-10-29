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

namespace cboe::c1options::complex::pitch::v2_1_18 {

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
    TradingStatusMessage(std::chrono::nanoseconds time_offset, const std::string& complex_symbol_id, const std::array<std::byte, 2>& unused, TradingStatus trading_status, const std::array<std::byte, 1>& reserved_1, GthTradingStatus gth_trading_status, const std::array<std::byte, 1>& padding);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Complex Symbol Id: Complex Symbol right padded with spaces.
    const std::string& complex_symbol_id() const;
    std::string& complex_symbol_id();
    void set_complex_symbol_id(const std::string& value);

    // Unused: Reserved
    const std::array<std::byte, 2>& unused() const;
    std::array<std::byte, 2>& unused();
    void set_unused(const std::array<std::byte, 2>& value);

    // Trading Status: Trading Status
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Reserved 1: Reserved
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Gth Trading Status: GTH Trading Status (C1 Only)
    GthTradingStatus gth_trading_status() const;
    void set_gth_trading_status(GthTradingStatus value);

    // Padding: Reserved
    const std::array<std::byte, 1>& padding() const;
    std::array<std::byte, 1>& padding();
    void set_padding(const std::array<std::byte, 1>& value);

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
    std::string complex_symbol_id_{};
    std::array<std::byte, 2> unused_{};
    TradingStatus trading_status_{};
    std::array<std::byte, 1> reserved_1_{};
    GthTradingStatus gth_trading_status_{};
    std::array<std::byte, 1> padding_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
