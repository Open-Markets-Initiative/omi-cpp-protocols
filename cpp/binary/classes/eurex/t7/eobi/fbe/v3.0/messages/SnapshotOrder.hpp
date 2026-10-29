#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/OrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

class Visitor;

// Snapshot Order
class SnapshotOrder : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SnapshotOrder;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    SnapshotOrder() = default;
    SnapshotOrder(const OrderDetailsComp& order_details_comp);

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

    bool operator==(const SnapshotOrder& other) const;
    bool operator!=(const SnapshotOrder& other) const;

  private:
    OrderDetailsComp order_details_comp_{};
};

} // namespace eurex::t7::eobi::fbe::v3_0
