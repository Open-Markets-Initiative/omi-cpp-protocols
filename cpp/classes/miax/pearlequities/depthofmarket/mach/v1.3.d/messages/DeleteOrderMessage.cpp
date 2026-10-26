#include "DeleteOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

DeleteOrderMessage::DeleteOrderMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, std::uint64_t order_id)
  : nanoseconds_(nanoseconds), symbol_id_(symbol_id), order_id_(order_id) {}

std::chrono::nanoseconds DeleteOrderMessage::nanoseconds() const { return nanoseconds_; }
void DeleteOrderMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t DeleteOrderMessage::symbol_id() const { return symbol_id_; }
void DeleteOrderMessage::set_symbol_id(std::uint32_t value) { symbol_id_ = value; }

std::uint64_t DeleteOrderMessage::order_id() const { return order_id_; }
void DeleteOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

DataCode DeleteOrderMessage::type() const { return message_type; }

std::string_view DeleteOrderMessage::name() const { return "Delete Order Message"; }

std::size_t DeleteOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("DeleteOrderMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t DeleteOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DeleteOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    return offset;
}

std::size_t DeleteOrderMessage::encoded_size() const {
    return wire_size;
}

void DeleteOrderMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> DeleteOrderMessage::clone() const {
    return std::make_unique<DeleteOrderMessage>(*this);
}

void DeleteOrderMessage::print(std::ostream& out) const {
    out << "DeleteOrderMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << ", order_id=";
    out << order_id_;
    out << '}';
}

bool DeleteOrderMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const DeleteOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool DeleteOrderMessage::operator==(const DeleteOrderMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && symbol_id_ == other.symbol_id_
        && order_id_ == other.order_id_;
}

bool DeleteOrderMessage::operator!=(const DeleteOrderMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
