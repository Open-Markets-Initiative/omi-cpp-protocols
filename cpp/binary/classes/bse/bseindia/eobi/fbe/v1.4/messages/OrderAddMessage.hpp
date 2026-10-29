#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/OrderDetails.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published for each new order that was entered in the order book.
class OrderAddMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::OrderAddMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 48;

    OrderAddMessage() = default;
    OrderAddMessage(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in, std::int64_t security_id, const OrderDetails& order_details);

    // Trd Reg Ts Time In: Matching engine In timestamp.
    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in() const;
    void set_trd_reg_ts_time_in(std::optional<std::chrono::nanoseconds> value);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Order Details: OrderDetails
    const OrderDetails& order_details() const;
    OrderDetails& order_details();
    void set_order_details(const OrderDetails& value);

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

    bool operator==(const OrderAddMessage& other) const;
    bool operator!=(const OrderAddMessage& other) const;

  private:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in_{};
    std::int64_t security_id_{};
    OrderDetails order_details_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
