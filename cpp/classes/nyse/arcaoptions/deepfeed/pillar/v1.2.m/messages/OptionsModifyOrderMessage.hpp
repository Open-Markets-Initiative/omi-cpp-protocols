#pragma once

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

// Sent when the price or volume of an order is changed due to an event other than a
// cancel-replace, or full or partial execution.
class OptionsModifyOrderMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsModifyOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 31;

    OptionsModifyOrderMessage() = default;
    OptionsModifyOrderMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint64_t order_id, std::int32_t price, std::uint32_t volume, std::uint8_t position_change, Side side, CustIndicator cust_indicator);

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

    // Price: The order price. Use with the Price Scale from the series index mapping.
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Volume: The order quantity in contracts
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Position Change: Defaulted to '0'. If the price didn't change, order keeps position. If
    // price changed, order loses position.
    std::uint8_t position_change() const;
    void set_position_change(std::uint8_t value);

    // Side: The side of the order (Buy/Sell).
    Side side() const;
    void set_side(Side value);

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

    bool operator==(const OptionsModifyOrderMessage& other) const;
    bool operator!=(const OptionsModifyOrderMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    std::uint64_t order_id_{};
    std::int32_t price_{};
    std::uint32_t volume_{};
    std::uint8_t position_change_{};
    Side side_{};
    CustIndicator cust_indicator_{};
};

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
