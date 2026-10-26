#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/SymbolCondition.hpp"
#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// C1 Only. The Constituent Symbol Mapping message is only available on the C1 Exchange. This
// message is used to communicate which options series (if any) are Constituent Series in a
// Volatility Settlement Special Opening Quote (SOQ). The message is identical to the Symbol
// Mapping message with the addition of the SOQ Identifier field, which is set to the CSMi
// symbol on which the final settlement SOQ value is disseminated. The Constituent Symbol
// Mapping message is sent as an unsequenced message with one message sent for each Constituent
// Series in a continuous loop as bandwidth allows.
class ConstituentSymbolMappingMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ConstituentSymbolMappingMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 56;

    ConstituentSymbolMappingMessage() = default;
    ConstituentSymbolMappingMessage(const std::string& feed_symbol, const std::string& osi_symbol, SymbolCondition symbol_condition, const std::string& underlying, const std::string& soq_identifier);

    // Feed Symbol: Symbol right padded with spaces.
    const std::string& feed_symbol() const;
    std::string& feed_symbol();
    void set_feed_symbol(const std::string& value);

    // Osi Symbol: OSI Symbol.
    const std::string& osi_symbol() const;
    std::string& osi_symbol();
    void set_osi_symbol(const std::string& value);

    // Symbol Condition: N = Normal, C = Closing Only.
    SymbolCondition symbol_condition() const;
    void set_symbol_condition(SymbolCondition value);

    // Underlying: Symbol of underlying equity right padded with spaces.
    const std::string& underlying() const;
    std::string& underlying();
    void set_underlying(const std::string& value);

    // Soq Identifier: Dissemination symbol of the final SOQ right padded with spaces.
    const std::string& soq_identifier() const;
    std::string& soq_identifier();
    void set_soq_identifier(const std::string& value);

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

    bool operator==(const ConstituentSymbolMappingMessage& other) const;
    bool operator!=(const ConstituentSymbolMappingMessage& other) const;

  private:
    std::string feed_symbol_{};
    std::string osi_symbol_{};
    SymbolCondition symbol_condition_{};
    std::string underlying_{};
    std::string soq_identifier_{};
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
