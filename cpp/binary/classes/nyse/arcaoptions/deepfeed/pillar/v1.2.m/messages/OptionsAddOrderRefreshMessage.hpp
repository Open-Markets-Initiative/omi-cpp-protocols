#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/CustIndicator.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class Visitor;

// Sent as part of a refresh response for every order currently resting on the book.
class OptionsAddOrderRefreshMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsAddOrderRefreshMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    OptionsAddOrderRefreshMessage() = default;
    OptionsAddOrderRefreshMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint64_t order_id, std::int32_t price, std::uint32_t volume, Side side, const std::string& firm_id, const std::array<std::byte, 1>& reserved_1, CustIndicator cust_indicator);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

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

    // Side: The side of the order (Buy/Sell).
    Side side() const;
    void set_side(Side value);

    // Firm Id: The market participant's firm ID (always space). ' ' - (space or 0x20)
    const std::string& firm_id() const;
    std::string& firm_id();
    void set_firm_id(const std::string& value);

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

    bool operator==(const OptionsAddOrderRefreshMessage& other) const;
    bool operator!=(const OptionsAddOrderRefreshMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    std::uint64_t order_id_{};
    std::int32_t price_{};
    std::uint32_t volume_{};
    Side side_{};
    std::string firm_id_{};
    std::array<std::byte, 1> reserved_1_{};
    CustIndicator cust_indicator_{};
};

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
