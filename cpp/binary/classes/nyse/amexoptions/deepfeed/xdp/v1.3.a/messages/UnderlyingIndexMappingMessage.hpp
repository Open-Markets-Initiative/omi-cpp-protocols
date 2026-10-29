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
#include "../enums/SecurityType.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

class Visitor;

// On system startup, each multicast channel sends all the symbols on its channel. Underlying
// Index Mapping messages are published first, followed by all Series Index Mapping messages,
// and for the Complex feed, Complex Symbol Definitions last of all.
class UnderlyingIndexMappingMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::UnderlyingIndexMappingMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    UnderlyingIndexMappingMessage() = default;
    UnderlyingIndexMappingMessage(std::uint32_t underlying_index, const std::string& underlying_symbol, std::uint8_t channel_id, MarketId market_id, std::uint8_t system_id, ExchangeCode exchange_code, std::uint8_t price_scale_code, SecurityType security_type, PriceResolution price_resolution, const std::array<std::byte, 1>& reserved_1);

    // Underlying Index: The unique ID of the symbol in the Series Index message
    std::uint32_t underlying_index() const;
    void set_underlying_index(std::uint32_t value);

    // Underlying Symbol: Full symbol in NYSE Symbology.
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Channel Id: Multicast channel ID of the symbols being provided.
    std::uint8_t channel_id() const;
    void set_channel_id(std::uint8_t value);

    // Market Id: Identifies originating market
    MarketId market_id() const;
    void set_market_id(MarketId value);

    // System Id: ID of the Originating System
    std::uint8_t system_id() const;
    void set_system_id(std::uint8_t value);

    // Exchange Code: Exchanges where it is listed
    ExchangeCode exchange_code() const;
    void set_exchange_code(ExchangeCode value);

    // Price Scale Code: Price Scale Code for price conversion of the symbol. See Price
    // Formats.
    std::uint8_t price_scale_code() const;
    void set_price_scale_code(std::uint8_t value);

    // Security Type: Type of Security
    SecurityType security_type() const;
    void set_security_type(SecurityType value);

    // Price Resolution: Price Resolution value
    PriceResolution price_resolution() const;
    void set_price_resolution(PriceResolution value);

    // Reserved 1: Filler
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

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

    bool operator==(const UnderlyingIndexMappingMessage& other) const;
    bool operator!=(const UnderlyingIndexMappingMessage& other) const;

  private:
    std::uint32_t underlying_index_{};
    std::string underlying_symbol_{};
    std::uint8_t channel_id_{};
    MarketId market_id_{};
    std::uint8_t system_id_{};
    ExchangeCode exchange_code_{};
    std::uint8_t price_scale_code_{};
    SecurityType security_type_{};
    PriceResolution price_resolution_{};
    std::array<std::byte, 1> reserved_1_{};
};

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
