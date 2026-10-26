#include "OrderModifyMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deepplus::iextp::v1_05 {

OrderModifyMessage::OrderModifyMessage(const ModifyFlags& modify_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint64_t order_id_reference, std::uint32_t size, Decimal price)
  : modify_flags_(modify_flags), timestamp_(timestamp), symbol_(symbol), order_id_reference_(order_id_reference), size_(size), price_(price) {}

const ModifyFlags& OrderModifyMessage::modify_flags() const { return modify_flags_; }
ModifyFlags& OrderModifyMessage::modify_flags() { return modify_flags_; }
void OrderModifyMessage::set_modify_flags(const ModifyFlags& value) { modify_flags_ = value; }

std::chrono::nanoseconds OrderModifyMessage::timestamp() const { return timestamp_; }
void OrderModifyMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& OrderModifyMessage::symbol() const { return symbol_; }
std::string& OrderModifyMessage::symbol() { return symbol_; }
void OrderModifyMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint64_t OrderModifyMessage::order_id_reference() const { return order_id_reference_; }
void OrderModifyMessage::set_order_id_reference(std::uint64_t value) { order_id_reference_ = value; }

std::uint32_t OrderModifyMessage::size() const { return size_; }
void OrderModifyMessage::set_size(std::uint32_t value) { size_ = value; }

Decimal OrderModifyMessage::price() const { return price_; }
void OrderModifyMessage::set_price(Decimal value) { price_ = value; }

MessageCode OrderModifyMessage::type() const { return message_type; }

std::string_view OrderModifyMessage::name() const { return "Order Modify Message"; }

std::size_t OrderModifyMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderModifyMessage", wire_size, length);

    offset += modify_flags_.decode(data + offset, length - offset);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    order_id_reference_ = wire::read_u64_le(data + offset);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t OrderModifyMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderModifyMessage", wire_size, capacity);

    offset += modify_flags_.encode(data + offset, capacity - offset);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_reference_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t OrderModifyMessage::encoded_size() const {
    return wire_size;
}

void OrderModifyMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderModifyMessage::clone() const {
    return std::make_unique<OrderModifyMessage>(*this);
}

void OrderModifyMessage::print(std::ostream& out) const {
    out << "OrderModifyMessage{";
    out << "modify_flags=";
    modify_flags_.print(out);
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", order_id_reference=";
    out << order_id_reference_;
    out << ", size=";
    out << size_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool OrderModifyMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderModifyMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderModifyMessage::operator==(const OrderModifyMessage& other) const {
    return modify_flags_ == other.modify_flags_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && order_id_reference_ == other.order_id_reference_
        && size_ == other.size_
        && price_ == other.price_;
}

bool OrderModifyMessage::operator!=(const OrderModifyMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deepplus::iextp::v1_05
