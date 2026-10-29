#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

class Visitor;

// Clients who have experienced a failure and need a refresh of the state of one or all symbols
// in a specific channel should send a Retransmission Request message via TCP to the Request
// Controller. A Request Response message will be sent over the TCP connection back to the
// client, and if the request was valid, the requested message(s) will be published over the
// relevant Refresh multicast channel.
class RefreshRequestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RefreshRequestMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    RefreshRequestMessage() = default;
    RefreshRequestMessage(std::uint32_t symbol_index, const std::string& source_id, std::uint8_t product_id, std::uint8_t channel_id);

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

    bool operator==(const RefreshRequestMessage& other) const;
    bool operator!=(const RefreshRequestMessage& other) const;

  private:
    std::uint32_t symbol_index_{};
    std::string source_id_{};
    std::uint8_t product_id_{};
    std::uint8_t channel_id_{};
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
