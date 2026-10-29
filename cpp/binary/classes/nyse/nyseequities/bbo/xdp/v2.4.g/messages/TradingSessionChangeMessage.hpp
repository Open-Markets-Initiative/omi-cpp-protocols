#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

class Visitor;

// This message announces the start of a new trading session for a specified symbol.
class TradingSessionChangeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradingSessionChangeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    TradingSessionChangeMessage() = default;
    TradingSessionChangeMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint8_t trading_session);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset from the SourceTime
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Symbol Index: The unique ID of this symbol for all products within this market. This ID
    // cannot be used to cross reference a security between markets.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: Reserved for future use. Ignore any content. This usage will become
    // standard across all products in future releases.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Trading Session: Trading session value
    std::uint8_t trading_session() const;
    void set_trading_session(std::uint8_t value);

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

    bool operator==(const TradingSessionChangeMessage& other) const;
    bool operator!=(const TradingSessionChangeMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint8_t trading_session_{};
};

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
