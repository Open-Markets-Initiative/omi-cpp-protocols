#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/TradeCond1.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

class Visitor;

// The Complex Trade message is used to publish all complex Last Sales.
class ComplexTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ComplexTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    ComplexTradeMessage() = default;
    ComplexTradeMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t complex_index, std::uint32_t symbol_seq_num, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume_4, TradeCond1 trade_cond_1, char trade_cond_2, const std::array<std::byte, 2>& reserved_2);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset from the SourceTime.
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Complex Index: The unique ID of the symbol in the Complex Index msg
    std::uint32_t complex_index() const;
    void set_complex_index(std::uint32_t value);

    // Symbol Seq Num: Sequence number of messages for the complex symbol.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Trade Id: n/a for complex symbols
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Price: The net amount of money made by the Seller* (the price of the Sell legs minus the
    // price of the Buy legs).
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Volume 4: Volume of the trade in actual number of contracts
    std::uint32_t volume_4() const;
    void set_volume_4(std::uint32_t value);

    // Trade Cond 1: TradeCond1 value
    TradeCond1 trade_cond_1() const;
    void set_trade_cond_1(TradeCond1 value);

    // Trade Cond 2: (blank) n/a for complex symbols
    char trade_cond_2() const;
    void set_trade_cond_2(char value);

    // Reserved 2: Filler
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

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

    bool operator==(const ComplexTradeMessage& other) const;
    bool operator!=(const ComplexTradeMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t complex_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint32_t trade_id_{};
    std::int32_t price_{};
    std::uint32_t volume_4_{};
    TradeCond1 trade_cond_1_{};
    char trade_cond_2_{};
    std::array<std::byte, 2> reserved_2_{};
};

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
