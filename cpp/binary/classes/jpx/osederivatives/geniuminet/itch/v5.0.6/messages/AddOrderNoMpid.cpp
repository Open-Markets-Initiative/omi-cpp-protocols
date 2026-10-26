#include "AddOrderNoMpid.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

AddOrderNoMpid::AddOrderNoMpid(std::chrono::nanoseconds nanoseconds, std::uint64_t order_id, std::uint32_t order_book_id, Side side, std::uint32_t order_book_position, std::uint64_t quantity, std::int32_t price, const OrderAttributes& order_attributes, LotType lot_type)
  : nanoseconds_(nanoseconds), order_id_(order_id), order_book_id_(order_book_id), side_(side), order_book_position_(order_book_position), quantity_(quantity), price_(price), order_attributes_(order_attributes), lot_type_(lot_type) {}

std::chrono::nanoseconds AddOrderNoMpid::nanoseconds() const { return nanoseconds_; }
void AddOrderNoMpid::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t AddOrderNoMpid::order_id() const { return order_id_; }
void AddOrderNoMpid::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t AddOrderNoMpid::order_book_id() const { return order_book_id_; }
void AddOrderNoMpid::set_order_book_id(std::uint32_t value) { order_book_id_ = value; }

Side AddOrderNoMpid::side() const { return side_; }
void AddOrderNoMpid::set_side(Side value) { side_ = value; }

std::uint32_t AddOrderNoMpid::order_book_position() const { return order_book_position_; }
void AddOrderNoMpid::set_order_book_position(std::uint32_t value) { order_book_position_ = value; }

std::uint64_t AddOrderNoMpid::quantity() const { return quantity_; }
void AddOrderNoMpid::set_quantity(std::uint64_t value) { quantity_ = value; }

std::int32_t AddOrderNoMpid::price() const { return price_; }
void AddOrderNoMpid::set_price(std::int32_t value) { price_ = value; }

const OrderAttributes& AddOrderNoMpid::order_attributes() const { return order_attributes_; }
OrderAttributes& AddOrderNoMpid::order_attributes() { return order_attributes_; }
void AddOrderNoMpid::set_order_attributes(const OrderAttributes& value) { order_attributes_ = value; }

LotType AddOrderNoMpid::lot_type() const { return lot_type_; }
void AddOrderNoMpid::set_lot_type(LotType value) { lot_type_ = value; }

MessageCode AddOrderNoMpid::type() const { return message_type; }

std::string_view AddOrderNoMpid::name() const { return "Add Order No Mpid"; }

std::size_t AddOrderNoMpid::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderNoMpid", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    order_book_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    order_book_position_ = wire::read_u32_be(data + offset);
    offset += 4;

    quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    price_ = wire::read_i32_be(data + offset);
    offset += 4;

    offset += order_attributes_.decode(data + offset, length - offset);

    lot_type_ = static_cast<LotType>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t AddOrderNoMpid::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderNoMpid", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_position_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(quantity_));
    offset += 8;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    offset += order_attributes_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(lot_type_));
    offset += 1;

    return offset;
}

std::size_t AddOrderNoMpid::encoded_size() const {
    return wire_size;
}

void AddOrderNoMpid::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddOrderNoMpid::clone() const {
    return std::make_unique<AddOrderNoMpid>(*this);
}

void AddOrderNoMpid::print(std::ostream& out) const {
    out << "AddOrderNoMpid{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", order_book_id=";
    out << order_book_id_;
    out << ", side=";
    out << side_;
    out << ", order_book_position=";
    out << order_book_position_;
    out << ", quantity=";
    out << quantity_;
    out << ", price=";
    out << price_;
    out << ", order_attributes=";
    order_attributes_.print(out);
    out << ", lot_type=";
    out << lot_type_;
    out << '}';
}

bool AddOrderNoMpid::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderNoMpid*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderNoMpid::operator==(const AddOrderNoMpid& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_id_ == other.order_id_
        && order_book_id_ == other.order_book_id_
        && side_ == other.side_
        && order_book_position_ == other.order_book_position_
        && quantity_ == other.quantity_
        && price_ == other.price_
        && order_attributes_ == other.order_attributes_
        && lot_type_ == other.lot_type_;
}

bool AddOrderNoMpid::operator!=(const AddOrderNoMpid& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
