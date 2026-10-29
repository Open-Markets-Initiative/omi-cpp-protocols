#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/State.hpp"
#include "../messages/Message.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

class Visitor;

// Individual symbol trading state (halts)
class SymbolStateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SymbolStateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 27;

    SymbolStateMessage() = default;
    SymbolStateMessage(std::chrono::nanoseconds timestamp, std::uint16_t symbol_id, const std::string& symbol, State state, char reserved_1, const std::string& info);

    // Timestamp: Nanoseconds Since Epoch (UTC)
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol Id: Symbol Index
    std::uint16_t symbol_id() const;
    void set_symbol_id(std::uint16_t value);

    // Symbol: Stock Symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // State: Symbol trading state
    State state() const;
    void set_state(State value);

    // Reserved 1: Reserved for future use
    char reserved_1() const;
    void set_reserved_1(char value);

    // Info: optional text
    const std::string& info() const;
    std::string& info();
    void set_info(const std::string& value);

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

    bool operator==(const SymbolStateMessage& other) const;
    bool operator!=(const SymbolStateMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t symbol_id_{};
    std::string symbol_{};
    State state_{};
    char reserved_1_{};
    std::string info_{};
};

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
