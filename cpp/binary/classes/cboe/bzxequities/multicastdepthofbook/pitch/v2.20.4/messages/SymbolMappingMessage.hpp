#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/SymbolCondition.hpp"
#include "../messages/Message.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

class Visitor;

// Symbol Mapping message
class SymbolMappingMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SymbolMappingMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    SymbolMappingMessage() = default;
    SymbolMappingMessage(const std::string& feed_symbol, const std::string& osi_symbol, SymbolCondition symbol_condition);

    // Feed Symbol: Symbol right padded with spaces
    const std::string& feed_symbol() const;
    std::string& feed_symbol();
    void set_feed_symbol(const std::string& value);

    // Osi Symbol: OSI Symbol Symbol
    const std::string& osi_symbol() const;
    std::string& osi_symbol();
    void set_osi_symbol(const std::string& value);

    // Symbol Condition: "N" = Normal
    SymbolCondition symbol_condition() const;
    void set_symbol_condition(SymbolCondition value);

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

    bool operator==(const SymbolMappingMessage& other) const;
    bool operator!=(const SymbolMappingMessage& other) const;

  private:
    std::string feed_symbol_{};
    std::string osi_symbol_{};
    SymbolCondition symbol_condition_{};
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
