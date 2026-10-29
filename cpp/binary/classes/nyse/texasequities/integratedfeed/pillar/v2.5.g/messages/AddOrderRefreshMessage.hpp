#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

class Visitor;

// The Add Order Refresh message can be sent in either of two contexts: refresh response or
// symbol refresh.
class AddOrderRefreshMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddOrderRefreshMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 39;

    AddOrderRefreshMessage() = default;
    AddOrderRefreshMessage(std::chrono::seconds source_time, std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::int32_t price, std::uint32_t volume, Side side, const std::string& firm_id, const std::array<std::byte, 1>& reserved_1);

    // Source Time: The time when this msg was generated in the order book, in secs since
    // 1/1/1970 00:00:00 UTC
    std::chrono::seconds source_time() const;
    void set_source_time(std::chrono::seconds value);

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

    // Price: The order price. Use with the Price Scale from the symbol-mapping index.
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Volume: The order quantity in shares
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Side: The side of the order (Buy/Sell).
    Side side() const;
    void set_side(Side value);

    // Firm Id: The market participant's firm ID.
    const std::string& firm_id() const;
    std::string& firm_id();
    void set_firm_id(const std::string& value);

    // Reserved 1: Defaulted to 0. Future use only.
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

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

    bool operator==(const AddOrderRefreshMessage& other) const;
    bool operator!=(const AddOrderRefreshMessage& other) const;

  private:
    std::chrono::seconds source_time_{};
    std::chrono::nanoseconds source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint64_t order_id_{};
    std::int32_t price_{};
    std::uint32_t volume_{};
    Side side_{};
    std::string firm_id_{};
    std::array<std::byte, 1> reserved_1_{};
};

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
