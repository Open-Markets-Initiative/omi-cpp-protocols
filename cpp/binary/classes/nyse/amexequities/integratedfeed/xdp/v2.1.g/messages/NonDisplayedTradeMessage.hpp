#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/PrintableFlag.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

class Visitor;

// An Non Displayed Trade message is sent as a result of a match between two non-displayed
// orders.
class NonDisplayedTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::NonDisplayedTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 29;

    NonDisplayedTradeMessage() = default;
    NonDisplayedTradeMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t trade_id, std::uint32_t price, std::uint32_t volume, PrintableFlag printable_flag, std::uint32_t db_exec_id);

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

    // Price: The order price. Use with the Price Scale from the symbol-mapping index.
    std::uint32_t price() const;
    void set_price(std::uint32_t value);

    // Volume: The order quantity in shares
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Printable Flag: Printable flag values
    PrintableFlag printable_flag() const;
    void set_printable_flag(PrintableFlag value);

    // Db Exec Id: For Pillar-powered markets, unused, defaulted to 0. For NYSE Tape A symbols,
    // DB ExecID is assigned by the matching engine to all orders that participated in this
    // trade event.
    std::uint32_t db_exec_id() const;
    void set_db_exec_id(std::uint32_t value);

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

    bool operator==(const NonDisplayedTradeMessage& other) const;
    bool operator!=(const NonDisplayedTradeMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint32_t trade_id_{};
    std::uint32_t price_{};
    std::uint32_t volume_{};
    PrintableFlag printable_flag_{};
    std::uint32_t db_exec_id_{};
};

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
