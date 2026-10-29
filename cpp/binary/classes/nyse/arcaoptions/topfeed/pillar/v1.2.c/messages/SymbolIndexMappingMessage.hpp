#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/ExchangeCode.hpp"
#include "../enums/MarketId.hpp"
#include "../enums/PriceResolution.hpp"
#include "../enums/PriceScaleCode.hpp"
#include "../enums/RoundLot.hpp"
#include "../enums/SecurityType.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

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
    SymbolIndexMappingMessage(std::uint32_t symbol_index, const std::string& symbol, const std::array<std::byte, 1>& reserved_1, MarketId market_id, std::uint8_t system_id, ExchangeCode exchange_code, PriceScaleCode price_scale_code, SecurityType security_type, std::uint16_t lot_size, std::uint32_t prev_close_price, std::uint32_t prev_close_volume, PriceResolution price_resolution, RoundLot round_lot, const std::array<std::byte, 6>& reserved_6);

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
    MarketId market_id() const;
    void set_market_id(MarketId value);

    // System Id: ID of the Originating matching engine server.
    std::uint8_t system_id() const;
    void set_system_id(std::uint8_t value);

    // Exchange Code: For listed equity markets, the market where this symbol is listed
    ExchangeCode exchange_code() const;
    void set_exchange_code(ExchangeCode value);

    // Price Scale Code: Specifies placement of the decimal point in price fields for this
    // security.
    PriceScaleCode price_scale_code() const;
    void set_price_scale_code(PriceScaleCode value);

    // Security Type: Type of Security used by Arca, National and American
    SecurityType security_type() const;
    void set_security_type(SecurityType value);

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
    PriceResolution price_resolution() const;
    void set_price_resolution(PriceResolution value);

    // Round Lot: Round Lots Accepted
    RoundLot round_lot() const;
    void set_round_lot(RoundLot value);

    // Reserved 6: Reserved for future use.
    const std::array<std::byte, 6>& reserved_6() const;
    std::array<std::byte, 6>& reserved_6();
    void set_reserved_6(const std::array<std::byte, 6>& value);

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
    MarketId market_id_{};
    std::uint8_t system_id_{};
    ExchangeCode exchange_code_{};
    PriceScaleCode price_scale_code_{};
    SecurityType security_type_{};
    std::uint16_t lot_size_{};
    std::uint32_t prev_close_price_{};
    std::uint32_t prev_close_volume_{};
    PriceResolution price_resolution_{};
    RoundLot round_lot_{};
    std::array<std::byte, 6> reserved_6_{};
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
