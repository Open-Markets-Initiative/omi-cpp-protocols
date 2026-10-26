#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/PrintableFlag.hpp"
#include "../enums/TradeCond1.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class Visitor;

// Sent when an order is partially or fully executed.
class OptionsOrderExecutionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsOrderExecutionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 38;

    OptionsOrderExecutionMessage() = default;
    OptionsOrderExecutionMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint64_t order_id, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, PrintableFlag printable_flag, const std::array<std::byte, 1>& reserved_1, TradeCond1 trade_cond_1, const std::array<std::byte, 3>& reserved_3);

    // Source Time Ns: The nanosecond offset (UTC Time) from the Time Reference message.
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Series Index: The unique ID of this series within this market.
    std::uint32_t series_index() const;
    void set_series_index(std::uint32_t value);

    // Series Seq Num: The sequence number of this message in the set of all messages for this
    // series
    std::uint32_t series_seq_num() const;
    void set_series_seq_num(std::uint32_t value);

    // Order Id: The unique ID assigned by the matching engine to this order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Trade Id: Unique ID assigned by the matching engine to this execution.
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Price: The order price. Use with the Price Scale from the series index mapping.
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Volume: The order quantity in contracts
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Printable Flag: Indicates whether trade is included in total volume.
    PrintableFlag printable_flag() const;
    void set_printable_flag(PrintableFlag value);

    // Reserved 1: Reserved for future use
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Trade Cond 1: Settlement related conditions.
    TradeCond1 trade_cond_1() const;
    void set_trade_cond_1(TradeCond1 value);

    // Reserved 3: Reserved for future use
    const std::array<std::byte, 3>& reserved_3() const;
    std::array<std::byte, 3>& reserved_3();
    void set_reserved_3(const std::array<std::byte, 3>& value);

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

    bool operator==(const OptionsOrderExecutionMessage& other) const;
    bool operator!=(const OptionsOrderExecutionMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    std::uint64_t order_id_{};
    std::uint32_t trade_id_{};
    std::int32_t price_{};
    std::uint32_t volume_{};
    PrintableFlag printable_flag_{};
    std::array<std::byte, 1> reserved_1_{};
    TradeCond1 trade_cond_1_{};
    std::array<std::byte, 3> reserved_3_{};
};

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
