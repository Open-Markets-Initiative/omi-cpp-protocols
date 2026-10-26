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

// Options Only. A Symbol Mapping message is used to map the 6 character multicast feed symbol
// field to an OSI symbol and Underlying. These messages are not sequenced (sequence = 0) and
// are sent continuously through the day at variable rates as bandwidth allows. Members who
// consume the 5 Gig or 8 Gig-Shaped Multicast PITCH feeds will be able to receive the full
// list of symbols in approximately 5 minutes.
class SymbolMappingMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SymbolMappingMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    SymbolMappingMessage() = default;
    SymbolMappingMessage(const std::string& feed_symbol, const std::string& osi_symbol, SymbolCondition symbol_condition, const std::string& underlying);

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
    std::string underlying_{};
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
