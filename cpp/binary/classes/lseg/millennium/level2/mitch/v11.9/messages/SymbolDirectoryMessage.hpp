// Lseg.Millennium.Level2.Mitch.v11.9: messages/SymbolDirectoryMessage.hpp
#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/SymbolStatus.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Used to disseminate information (symbol, segment, ISIN, underlying, etc.) on each instrument
class SymbolDirectoryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SymbolDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 63;

    SymbolDirectoryMessage() = default;
    SymbolDirectoryMessage(std::chrono::nanoseconds nanosecond, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, SymbolStatus symbol_status, const std::string& isin, const std::string& sedol, const std::string& segment, const std::string& underlying, const std::string& currency, const std::array<std::byte, 1>& reserved_byte, const std::array<std::byte, 4>& reserved_4, Decimal previous_close_price);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::chrono::nanoseconds nanosecond() const;
    void set_nanosecond(std::chrono::nanoseconds value);

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

    // Symbol Status: This field will contain a space if the instrument is active.
    SymbolStatus symbol_status() const;
    void set_symbol_status(SymbolStatus value);

    // Isin: Instrument identification number
    const std::string& isin() const;
    std::string& isin();
    void set_isin(const std::string& value);

    // Sedol: Instrument identification number
    const std::string& sedol() const;
    std::string& sedol();
    void set_sedol(const std::string& value);

    // Segment: Segment the instrument is assigned to.
    const std::string& segment() const;
    std::string& segment();
    void set_segment(const std::string& value);

    // Underlying: Reserved for future use
    const std::string& underlying() const;
    std::string& underlying();
    void set_underlying(const std::string& value);

    // Currency: ISO Currency Code
    const std::string& currency() const;
    std::string& currency();
    void set_currency(const std::string& value);

    // Reserved Byte: Reserved field
    const std::array<std::byte, 1>& reserved_byte() const;
    std::array<std::byte, 1>& reserved_byte();
    void set_reserved_byte(const std::array<std::byte, 1>& value);

    // Reserved 4: Reserved field
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Previous Close Price: Previous Close Price of instrument
    Decimal previous_close_price() const;
    void set_previous_close_price(Decimal value);

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

    bool operator==(const SymbolDirectoryMessage& other) const;
    bool operator!=(const SymbolDirectoryMessage& other) const;

  private:
    std::chrono::nanoseconds nanosecond_{};
    std::uint32_t instrument_id_{};
    std::array<std::byte, 1> reserved_a_{};
    std::array<std::byte, 1> reserved_b_{};
    SymbolStatus symbol_status_{};
    std::string isin_{};
    std::string sedol_{};
    std::string segment_{};
    std::string underlying_{};
    std::string currency_{};
    std::array<std::byte, 1> reserved_byte_{};
    std::array<std::byte, 4> reserved_4_{};
    Decimal previous_close_price_{ 0, -8 };
};

} // namespace lseg::millennium::level2::mitch::v11_9
