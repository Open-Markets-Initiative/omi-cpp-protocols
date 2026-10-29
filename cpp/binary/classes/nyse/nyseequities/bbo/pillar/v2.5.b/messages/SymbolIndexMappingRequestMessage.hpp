#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/RetransmitMethod.hpp"
#include "../messages/Message.hpp"

namespace nyse::nyseequities::bbo::pillar::v2_5_b {

class Visitor;

// This message is sent by clients via TCP/IP requesting the Symbol Index Mapping messages for
// one or all symbols in a specified channel.
class SymbolIndexMappingRequestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SymbolIndexMappingRequestMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    SymbolIndexMappingRequestMessage() = default;
    SymbolIndexMappingRequestMessage(std::uint32_t symbol_index, const std::string& source_id, std::uint8_t product_id, std::uint8_t channel_id, RetransmitMethod retransmit_method);

    // Symbol Index: The unique ID of this symbol for all products within this market. This ID
    // cannot be used to cross reference a security between markets.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Source Id: The ID of the client requesting this retransmission . This field is up to 9
    // characters, null terminated.
    const std::string& source_id() const;
    std::string& source_id();
    void set_source_id(const std::string& value);

    // Product Id: The unique ID for this NYSE feed listed in the feed’s client specification.
    std::uint8_t product_id() const;
    void set_product_id(std::uint8_t value);

    // Channel Id: The ID of the multicast channel over which the packet was sent.
    std::uint8_t channel_id() const;
    void set_channel_id(std::uint8_t value);

    // Retransmit Method: The delivery method for the requested symbol index mapping
    // information.
    RetransmitMethod retransmit_method() const;
    void set_retransmit_method(RetransmitMethod value);

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

    bool operator==(const SymbolIndexMappingRequestMessage& other) const;
    bool operator!=(const SymbolIndexMappingRequestMessage& other) const;

  private:
    std::uint32_t symbol_index_{};
    std::string source_id_{};
    std::uint8_t product_id_{};
    std::uint8_t channel_id_{};
    RetransmitMethod retransmit_method_{};
};

} // namespace nyse::nyseequities::bbo::pillar::v2_5_b
