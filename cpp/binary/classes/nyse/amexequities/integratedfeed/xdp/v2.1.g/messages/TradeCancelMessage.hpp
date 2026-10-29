#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

class Visitor;

// In the event that an earlier trade has been reported in error, a Trade Cancel message is
// sent. This occurs whether the initial report was an Order Execution or a Non-Displayed Trade
// message.
class TradeCancelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    TradeCancelMessage() = default;
    TradeCancelMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t trade_id);

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

    // Trade Id: The TradeID of the original Trade or Execution message to be cancelled.
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

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

    bool operator==(const TradeCancelMessage& other) const;
    bool operator!=(const TradeCancelMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint32_t trade_id_{};
};

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
