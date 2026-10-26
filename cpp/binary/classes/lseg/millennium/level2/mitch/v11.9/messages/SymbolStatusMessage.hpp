#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/SymbolStatusFlags.hpp"
#include "../enums/BookType.hpp"
#include "../enums/SessionChangeReason.hpp"
#include "../enums/TradingStatus.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Indicates the trading session (pre-opening, regular trading, etc.) that currently applies to
// an instrument.
class SymbolStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SymbolStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 26;

    SymbolStatusMessage() = default;
    SymbolStatusMessage(std::uint32_t nanosecond, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, TradingStatus trading_status, const SymbolStatusFlags& symbol_status_flags, const std::string& reason, SessionChangeReason session_change_reason, const std::string& new_end_time, BookType book_type);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::uint32_t nanosecond() const;
    void set_nanosecond(std::uint32_t value);

    // Instrument Id: Instrument's symbol.
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Reserved A: Reserved field
    const std::array<std::byte, 1>& reserved_a() const;
    std::array<std::byte, 1>& reserved_a();
    void set_reserved_a(const std::array<std::byte, 1>& value);

    // Reserved B: Reserved field
    const std::array<std::byte, 1>& reserved_b() const;
    std::array<std::byte, 1>& reserved_b();
    void set_reserved_b(const std::array<std::byte, 1>& value);

    // Trading Status: Trading Status
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Symbol Status Flags: Symbol Status Flags
    const SymbolStatusFlags& symbol_status_flags() const;
    SymbolStatusFlags& symbol_status_flags();
    void set_symbol_status_flags(const SymbolStatusFlags& value);

    // Reason: Reason for the manual session change or the trading halt.
    const std::string& reason() const;
    std::string& reason();
    void set_reason(const std::string& value);

    // Session Change Reason: Session Change Reason
    SessionChangeReason session_change_reason() const;
    void set_session_change_reason(SessionChangeReason value);

    // New End Time: New time the session will end. Will only be stamped if the session change
    // was not in the original schedule e.g. AESP auction call or unscheduled session.
    const std::string& new_end_time() const;
    std::string& new_end_time();
    void set_new_end_time(const std::string& value);

    // Book Type: Book Type
    BookType book_type() const;
    void set_book_type(BookType value);

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

    bool operator==(const SymbolStatusMessage& other) const;
    bool operator!=(const SymbolStatusMessage& other) const;

  private:
    std::uint32_t nanosecond_{};
    std::uint32_t instrument_id_{};
    std::array<std::byte, 1> reserved_a_{};
    std::array<std::byte, 1> reserved_b_{};
    TradingStatus trading_status_{};
    SymbolStatusFlags symbol_status_flags_{};
    std::string reason_{};
    SessionChangeReason session_change_reason_{};
    std::string new_end_time_{};
    BookType book_type_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
