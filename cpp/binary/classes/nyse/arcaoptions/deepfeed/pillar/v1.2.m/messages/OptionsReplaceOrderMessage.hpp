#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/CustIndicator.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class Visitor;

// Published when a cancel/replace order is received. The resting order is replaced with a new
// order containing the same outright or complex series, side and attribution, a new Order ID,
// and the price and size specified.
class OptionsReplaceOrderMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsReplaceOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    OptionsReplaceOrderMessage() = default;
    OptionsReplaceOrderMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint64_t order_id, std::uint64_t new_order_id, std::int32_t price, std::uint32_t volume, Side side, const std::array<std::byte, 1>& reserved_1, CustIndicator cust_indicator);

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

    // New Order Id: The new Order ID of the replacement order
    std::uint64_t new_order_id() const;
    void set_new_order_id(std::uint64_t value);

    // Price: The order price. Use with the Price Scale from the series index mapping.
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Volume: The order quantity in contracts
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Side: The side of the order (Buy/Sell).
    Side side() const;
    void set_side(Side value);

    // Reserved 1: Reserved for future use
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Cust Indicator: Capacity of the order.
    CustIndicator cust_indicator() const;
    void set_cust_indicator(CustIndicator value);

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

    bool operator==(const OptionsReplaceOrderMessage& other) const;
    bool operator!=(const OptionsReplaceOrderMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    std::uint64_t order_id_{};
    std::uint64_t new_order_id_{};
    std::int32_t price_{};
    std::uint32_t volume_{};
    Side side_{};
    std::array<std::byte, 1> reserved_1_{};
    CustIndicator cust_indicator_{};
};

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
