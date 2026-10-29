#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "../enums/MarketId.hpp"
#include "../groups/LegDefinition.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

class Visitor;

// The Complex Symbol Definition message provides a description of the legs in a Complex
// symbol, and specifies its Complex symbol ID, which is unique for its stream. If the same
// symbol ID appears in a different stream, it represents a different Complex symbol.
class ComplexSymbolDefinitionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ComplexSymbolDefinitionMessage;

    ComplexSymbolDefinitionMessage() = default;
    ComplexSymbolDefinitionMessage(std::uint32_t complex_index, const std::string& complex_symbol, std::uint8_t channel_id, MarketId market_id, std::uint8_t system_id, const std::array<std::byte, 1>& reserved_1, std::uint16_t stream_id, std::uint16_t no_of_legs, const std::array<std::byte, 2>& reserved_2, const std::vector<LegDefinition>& leg_definition);

    // Complex Index: The unique ID of the symbol in the Complex Index msg
    std::uint32_t complex_index() const;
    void set_complex_index(std::uint32_t value);

    // Complex Symbol: Complex Symbol. This is an alpha numeric symbol which can be used for a
    // unique strategy until one of the legs expire.
    const std::string& complex_symbol() const;
    std::string& complex_symbol();
    void set_complex_symbol(const std::string& value);

    // Channel Id: Multicast channel ID of the symbols being provided.
    std::uint8_t channel_id() const;
    void set_channel_id(std::uint8_t value);

    // Market Id: Identifies originating market
    MarketId market_id() const;
    void set_market_id(MarketId value);

    // System Id: Identifies Trading unit (TU)
    std::uint8_t system_id() const;
    void set_system_id(std::uint8_t value);

    // Reserved 1: Filler
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Stream Id: Identifies Stream on which this symbol will be updated
    std::uint16_t stream_id() const;
    void set_stream_id(std::uint16_t value);

    // No Of Legs: Number of legs in complex symbol: 1 – 5
    std::uint16_t no_of_legs() const;
    void set_no_of_legs(std::uint16_t value);

    // Reserved 2: Filler
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

    // Leg Definition: Leg definition
    const std::vector<LegDefinition>& leg_definition() const;
    std::vector<LegDefinition>& leg_definition();
    void set_leg_definition(const std::vector<LegDefinition>& value);

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

    bool operator==(const ComplexSymbolDefinitionMessage& other) const;
    bool operator!=(const ComplexSymbolDefinitionMessage& other) const;

  private:
    std::uint32_t complex_index_{};
    std::string complex_symbol_{};
    std::uint8_t channel_id_{};
    MarketId market_id_{};
    std::uint8_t system_id_{};
    std::array<std::byte, 1> reserved_1_{};
    std::uint16_t stream_id_{};
    std::uint16_t no_of_legs_{};
    std::array<std::byte, 2> reserved_2_{};
    std::vector<LegDefinition> leg_definition_{};
};

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
