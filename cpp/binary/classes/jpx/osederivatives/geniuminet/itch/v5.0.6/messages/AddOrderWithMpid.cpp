#include "AddOrderWithMpid.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

AddOrderWithMpid::AddOrderWithMpid(std::chrono::nanoseconds nanoseconds, std::uint64_t order_id, std::uint32_t order_book_id, Side side, std::uint32_t order_book_position, std::uint64_t quantity, std::int32_t price, const OrderAttributes& order_attributes, LotType lot_type, const std::string& participant_id)
  : nanoseconds_(nanoseconds), order_id_(order_id), order_book_id_(order_book_id), side_(side), order_book_position_(order_book_position), quantity_(quantity), price_(price), order_attributes_(order_attributes), lot_type_(lot_type), participant_id_(participant_id) {}

std::chrono::nanoseconds AddOrderWithMpid::nanoseconds() const { return nanoseconds_; }
void AddOrderWithMpid::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t AddOrderWithMpid::order_id() const { return order_id_; }
void AddOrderWithMpid::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t AddOrderWithMpid::order_book_id() const { return order_book_id_; }
void AddOrderWithMpid::set_order_book_id(std::uint32_t value) { order_book_id_ = value; }

Side AddOrderWithMpid::side() const { return side_; }
void AddOrderWithMpid::set_side(Side value) { side_ = value; }

std::uint32_t AddOrderWithMpid::order_book_position() const { return order_book_position_; }
void AddOrderWithMpid::set_order_book_position(std::uint32_t value) { order_book_position_ = value; }

std::uint64_t AddOrderWithMpid::quantity() const { return quantity_; }
void AddOrderWithMpid::set_quantity(std::uint64_t value) { quantity_ = value; }

std::int32_t AddOrderWithMpid::price() const { return price_; }
void AddOrderWithMpid::set_price(std::int32_t value) { price_ = value; }

const OrderAttributes& AddOrderWithMpid::order_attributes() const { return order_attributes_; }
OrderAttributes& AddOrderWithMpid::order_attributes() { return order_attributes_; }
void AddOrderWithMpid::set_order_attributes(const OrderAttributes& value) { order_attributes_ = value; }

LotType AddOrderWithMpid::lot_type() const { return lot_type_; }
void AddOrderWithMpid::set_lot_type(LotType value) { lot_type_ = value; }

const std::string& AddOrderWithMpid::participant_id() const { return participant_id_; }
std::string& AddOrderWithMpid::participant_id() { return participant_id_; }
void AddOrderWithMpid::set_participant_id(const std::string& value) { participant_id_ = value; }

MessageCode AddOrderWithMpid::type() const { return message_type; }

std::string_view AddOrderWithMpid::name() const { return "Add Order With Mpid"; }

std::size_t AddOrderWithMpid::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderWithMpid", wire_size, length);

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

    participant_id_ = wire::read_text(data + offset, 7, ' ');
    offset += 7;

    return offset;
}

std::size_t AddOrderWithMpid::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderWithMpid", wire_size, capacity);

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

    wire::write_text(data + offset, 7, ' ', participant_id_);
    offset += 7;

    return offset;
}

std::size_t AddOrderWithMpid::encoded_size() const {
    return wire_size;
}

void AddOrderWithMpid::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddOrderWithMpid::clone() const {
    return std::make_unique<AddOrderWithMpid>(*this);
}

void AddOrderWithMpid::print(std::ostream& out) const {
    out << "AddOrderWithMpid{";
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
    out << ", participant_id=";
    print::text(out, participant_id_);
    out << '}';
}

bool AddOrderWithMpid::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderWithMpid*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderWithMpid::operator==(const AddOrderWithMpid& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_id_ == other.order_id_
        && order_book_id_ == other.order_book_id_
        && side_ == other.side_
        && order_book_position_ == other.order_book_position_
        && quantity_ == other.quantity_
        && price_ == other.price_
        && order_attributes_ == other.order_attributes_
        && lot_type_ == other.lot_type_
        && participant_id_ == other.participant_id_;
}

bool AddOrderWithMpid::operator!=(const AddOrderWithMpid& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
