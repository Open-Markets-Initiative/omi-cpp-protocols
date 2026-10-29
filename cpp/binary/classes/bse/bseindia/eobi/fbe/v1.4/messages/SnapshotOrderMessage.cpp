#include "SnapshotOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

SnapshotOrderMessage::SnapshotOrderMessage(const OrderDetails& order_details)
  : order_details_(order_details) {}

const OrderDetails& SnapshotOrderMessage::order_details() const { return order_details_; }
OrderDetails& SnapshotOrderMessage::order_details() { return order_details_; }
void SnapshotOrderMessage::set_order_details(const OrderDetails& value) { order_details_ = value; }

MessageCode SnapshotOrderMessage::type() const { return message_type; }

std::string_view SnapshotOrderMessage::name() const { return "Snapshot Order Message"; }

std::size_t SnapshotOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotOrderMessage", wire_size, length);

    offset += order_details_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SnapshotOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotOrderMessage", wire_size, capacity);

    offset += order_details_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SnapshotOrderMessage::encoded_size() const {
    return wire_size;
}

void SnapshotOrderMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SnapshotOrderMessage::clone() const {
    return std::make_unique<SnapshotOrderMessage>(*this);
}

void SnapshotOrderMessage::print(std::ostream& out) const {
    out << "SnapshotOrderMessage{";
    out << "order_details=";
    order_details_.print(out);
    out << '}';
}

bool SnapshotOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SnapshotOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotOrderMessage::operator==(const SnapshotOrderMessage& other) const {
    return order_details_ == other.order_details_;
}

bool SnapshotOrderMessage::operator!=(const SnapshotOrderMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
