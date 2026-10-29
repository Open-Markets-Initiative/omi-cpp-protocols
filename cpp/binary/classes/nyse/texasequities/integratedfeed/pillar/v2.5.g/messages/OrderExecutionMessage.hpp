#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/PrintableFlag.hpp"
#include "../enums/TradeCond1.hpp"
#include "../enums/TradeCond2.hpp"
#include "../enums/TradeCond3.hpp"
#include "../enums/TradeCond4.hpp"
#include "../messages/Message.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

class Visitor;

// An Order Execution message is sent when an order is partially or fully executed.
class OrderExecutionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 38;

    OrderExecutionMessage() = default;
    OrderExecutionMessage(std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, PrintableFlag printable_flag, const std::array<std::byte, 1>& reserved_1, TradeCond1 trade_cond_1, TradeCond2 trade_cond_2, TradeCond3 trade_cond_3, TradeCond4 trade_cond_4);

    // Source Time Ns: The nanosecond offset from the Time Reference second.
    std::chrono::nanoseconds source_time_ns() const;
    void set_source_time_ns(std::chrono::nanoseconds value);

    // Symbol Index: The ID of the symbol in the Symbol Index msg
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: The sequence number of this message in the set of all messages for this
    // symbol
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Order Id: The unique ID assigned by the matching engine to this order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Trade Id: Unique ID assigned by the matching engine to this execution.
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Price: The order price. Use with the Price Scale from the symbol-mapping index.
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Volume: The order quantity in shares
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Printable Flag: 0 = Not Printed to the SIP. 1 = Printed to the SIP.
    PrintableFlag printable_flag() const;
    void set_printable_flag(PrintableFlag value);

    // Reserved 1: Defaulted to 0. Future use only.
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Trade Cond 1: Settlement related conditions.
    TradeCond1 trade_cond_1() const;
    void set_trade_cond_1(TradeCond1 value);

    // Trade Cond 2: The reason for Trade Through Exemptions.
    TradeCond2 trade_cond_2() const;
    void set_trade_cond_2(TradeCond2 value);

    // Trade Cond 3: Extended hours/sequencing related conditions.
    TradeCond3 trade_cond_3() const;
    void set_trade_cond_3(TradeCond3 value);

    // Trade Cond 4: SRO Required Detail.
    TradeCond4 trade_cond_4() const;
    void set_trade_cond_4(TradeCond4 value);

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

    bool operator==(const OrderExecutionMessage& other) const;
    bool operator!=(const OrderExecutionMessage& other) const;

  private:
    std::chrono::nanoseconds source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint64_t order_id_{};
    std::uint32_t trade_id_{};
    std::int32_t price_{};
    std::uint32_t volume_{};
    PrintableFlag printable_flag_{};
    std::array<std::byte, 1> reserved_1_{};
    TradeCond1 trade_cond_1_{};
    TradeCond2 trade_cond_2_{};
    TradeCond3 trade_cond_3_{};
    TradeCond4 trade_cond_4_{};
};

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
