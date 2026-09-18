#include "AddOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

AddOrderMessage::AddOrderMessage(std::chrono::microseconds time_microseconds, std::uint32_t order_id, Side side, std::uint64_t quantity, std::optional<Decimal> price, OrderCondition order_condition, ModificationFlag modification_flag)
  : time_microseconds_(time_microseconds), order_id_(order_id), side_(side), quantity_(quantity), price_(price), order_condition_(order_condition), modification_flag_(modification_flag) {}

std::chrono::microseconds AddOrderMessage::time_microseconds() const { return time_microseconds_; }
void AddOrderMessage::set_time_microseconds(std::chrono::microseconds value) { time_microseconds_ = value; }

std::uint32_t AddOrderMessage::order_id() const { return order_id_; }
void AddOrderMessage::set_order_id(std::uint32_t value) { order_id_ = value; }

Side AddOrderMessage::side() const { return side_; }
void AddOrderMessage::set_side(Side value) { side_ = value; }

std::uint64_t AddOrderMessage::quantity() const { return quantity_; }
void AddOrderMessage::set_quantity(std::uint64_t value) { quantity_ = value; }

std::optional<Decimal> AddOrderMessage::price() const { return price_; }
void AddOrderMessage::set_price(std::optional<Decimal> value) { price_ = value; }

OrderCondition AddOrderMessage::order_condition() const { return order_condition_; }
void AddOrderMessage::set_order_condition(OrderCondition value) { order_condition_ = value; }

ModificationFlag AddOrderMessage::modification_flag() const { return modification_flag_; }
void AddOrderMessage::set_modification_flag(ModificationFlag value) { modification_flag_ = value; }

MessageCode AddOrderMessage::type() const { return message_type; }

std::string_view AddOrderMessage::name() const { return "Add Order Message"; }

std::size_t AddOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderMessage", wire_size, length);

    time_microseconds_ = std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u48_be(data + offset);
    offset += 6;

    price_ = wire::nullable_decimal(wire::read_u64_be(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL), -4);
    offset += 8;

    order_condition_ = static_cast<OrderCondition>(wire::read_u8(data + offset));
    offset += 1;

    modification_flag_ = static_cast<ModificationFlag>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t AddOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(time_microseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(quantity_));
    offset += 6;

    wire::write_u64_be(data + offset, price_ ? static_cast<std::uint64_t>(price_->mantissa()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(order_condition_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(modification_flag_));
    offset += 1;

    return offset;
}

std::size_t AddOrderMessage::encoded_size() const {
    return wire_size;
}

void AddOrderMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddOrderMessage::clone() const {
    return std::make_unique<AddOrderMessage>(*this);
}

void AddOrderMessage::print(std::ostream& out) const {
    out << "AddOrderMessage{";
    out << "time_microseconds=";
    out << time_microseconds_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", side=";
    out << side_;
    out << ", quantity=";
    out << quantity_;
    out << ", price=";
    print::optional(out, price_);
    out << ", order_condition=";
    out << order_condition_;
    out << ", modification_flag=";
    out << modification_flag_;
    out << '}';
}

bool AddOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderMessage::operator==(const AddOrderMessage& other) const {
    return time_microseconds_ == other.time_microseconds_
        && order_id_ == other.order_id_
        && side_ == other.side_
        && quantity_ == other.quantity_
        && price_ == other.price_
        && order_condition_ == other.order_condition_
        && modification_flag_ == other.modification_flag_;
}

bool AddOrderMessage::operator!=(const AddOrderMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
