#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/OrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

class Visitor;

// Order Add
class OrderAdd : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::OrderAdd;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    OrderAdd() = default;
    OrderAdd(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in, std::optional<std::int64_t> security_id, const OrderDetailsComp& order_details_comp);

    // Trd Reg Ts Time In:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in() const;
    void set_trd_reg_ts_time_in(std::optional<std::chrono::nanoseconds> value);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Order Details Comp:
    const OrderDetailsComp& order_details_comp() const;
    OrderDetailsComp& order_details_comp();
    void set_order_details_comp(const OrderDetailsComp& value);

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

    bool operator==(const OrderAdd& other) const;
    bool operator!=(const OrderAdd& other) const;

  private:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in_{};
    std::optional<std::int64_t> security_id_{};
    OrderDetailsComp order_details_comp_{};
};

} // namespace eurex::t7::eobi::fbe::v6_0
