#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

class Visitor;

// This message is published over the real-time data channels at system startup or in the
// context of a refresh sequence after a Matching Engine or XDP Publisher failover. It provides
// referential data for a single specified symbol.
class SymbolIndexMappingMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SymbolIndexMappingMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    SymbolIndexMappingMessage() = default;
    SymbolIndexMappingMessage(std::uint32_t symbol_index, const std::string& symbol, const std::array<std::byte, 1>& reserved_1, std::uint16_t market_id, std::uint8_t system_id, char exchange_code, std::uint8_t price_scale_code, char security_type, std::uint16_t lot_size, std::uint32_t prev_close_price, std::uint32_t prev_close_volume, std::uint8_t price_resolution, char round_lot, std::uint16_t mpv, std::uint16_t unit_of_trade, const std::array<std::byte, 2>& reserved_2);

    // Symbol Index: The unique ID of this symbol for all products within this market. This ID
    // cannot be used to cross reference a security between markets.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol: Null-terminated ASCII symbol in NYSE Symbology.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Reserved 1: This field is reserved for future use
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Market Id: ID of the Originating Market
    std::uint16_t market_id() const;
    void set_market_id(std::uint16_t value);

    // System Id: ID of the Originating matching engine server.
    std::uint8_t system_id() const;
    void set_system_id(std::uint8_t value);

    // Exchange Code: For listed equity markets, the market where this symbol is listed
    char exchange_code() const;
    void set_exchange_code(char value);

    // Price Scale Code: Specifies placement of the decimal point in price fields for this
    // security.
    std::uint8_t price_scale_code() const;
    void set_price_scale_code(std::uint8_t value);

    // Security Type: Type of Security used by Arca, National and American
    char security_type() const;
    void set_security_type(char value);

    // Lot Size: Round lot size in shares.
    std::uint16_t lot_size() const;
    void set_lot_size(std::uint16_t value);

    // Prev Close Price: The previous day’s closing price for this security.
    std::uint32_t prev_close_price() const;
    void set_prev_close_price(std::uint32_t value);

    // Prev Close Volume: The previous day’s closing volume for the security.
    std::uint32_t prev_close_volume() const;
    void set_prev_close_volume(std::uint32_t value);

    // Price Resolution: All Penny, Penny/Nickel, Nickel/Dime
    std::uint8_t price_resolution() const;
    void set_price_resolution(std::uint8_t value);

    // Round Lot: Round Lots Accepted
    char round_lot() const;
    void set_round_lot(char value);

    // Mpv: The minimum increment for a trade price, in 100ths of a cent. Typically 1, or
    // $0.0001, but for some Tick Pilot stocks, can be 500, or $0.05.
    std::uint16_t mpv() const;
    void set_mpv(std::uint16_t value);

    // Unit Of Trade: This field specifies the security Unit of Trade in shares. Valid values
    // are 1, 10, 50 and 100
    std::uint16_t unit_of_trade() const;
    void set_unit_of_trade(std::uint16_t value);

    // Reserved 2: Reserved for future use. Disregard any content.
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

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

    bool operator==(const SymbolIndexMappingMessage& other) const;
    bool operator!=(const SymbolIndexMappingMessage& other) const;

  private:
    std::uint32_t symbol_index_{};
    std::string symbol_{};
    std::array<std::byte, 1> reserved_1_{};
    std::uint16_t market_id_{};
    std::uint8_t system_id_{};
    char exchange_code_{};
    std::uint8_t price_scale_code_{};
    char security_type_{};
    std::uint16_t lot_size_{};
    std::uint32_t prev_close_price_{};
    std::uint32_t prev_close_volume_{};
    std::uint8_t price_resolution_{};
    char round_lot_{};
    std::uint16_t mpv_{};
    std::uint16_t unit_of_trade_{};
    std::array<std::byte, 2> reserved_2_{};
};

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f
