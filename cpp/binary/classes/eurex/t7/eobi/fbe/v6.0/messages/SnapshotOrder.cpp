#include "SnapshotOrder.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

SnapshotOrder::SnapshotOrder(const OrderDetailsComp& order_details_comp)
  : order_details_comp_(order_details_comp) {}

const OrderDetailsComp& SnapshotOrder::order_details_comp() const { return order_details_comp_; }
OrderDetailsComp& SnapshotOrder::order_details_comp() { return order_details_comp_; }
void SnapshotOrder::set_order_details_comp(const OrderDetailsComp& value) { order_details_comp_ = value; }

MessageCode SnapshotOrder::type() const { return message_type; }

std::string_view SnapshotOrder::name() const { return "Snapshot Order"; }

std::size_t SnapshotOrder::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotOrder", wire_size, length);

    offset += order_details_comp_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SnapshotOrder::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotOrder", wire_size, capacity);

    offset += order_details_comp_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SnapshotOrder::encoded_size() const {
    return wire_size;
}

void SnapshotOrder::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SnapshotOrder::clone() const {
    return std::make_unique<SnapshotOrder>(*this);
}

void SnapshotOrder::print(std::ostream& out) const {
    out << "SnapshotOrder{";
    out << "order_details_comp=";
    order_details_comp_.print(out);
    out << '}';
}

bool SnapshotOrder::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SnapshotOrder*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotOrder::operator==(const SnapshotOrder& other) const {
    return order_details_comp_ == other.order_details_comp_;
}

bool SnapshotOrder::operator!=(const SnapshotOrder& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v6_0
