#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/OrderDetails.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Represents each individual order or quote in a snapshot cycle on the snapshot channel.
class SnapshotOrderMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SnapshotOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 32;

    SnapshotOrderMessage() = default;
    SnapshotOrderMessage(const OrderDetails& order_details);

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

    bool operator==(const SnapshotOrderMessage& other) const;
    bool operator!=(const SnapshotOrderMessage& other) const;

  private:
    OrderDetails order_details_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
