#include "AddOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

AddOrderMessage::AddOrderMessage(std::uint32_t nanosecond, std::uint64_t order_id, Side side, std::uint32_t quantity, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, std::int64_t price, const AddOrderFlags& add_order_flags, const std::array<std::byte, 10>& reserved_10)
  : nanosecond_(nanosecond), order_id_(order_id), side_(side), quantity_(quantity), instrument_id_(instrument_id), reserved_a_(reserved_a), reserved_b_(reserved_b), price_(price), add_order_flags_(add_order_flags), reserved_10_(reserved_10) {}

std::uint32_t AddOrderMessage::nanosecond() const { return nanosecond_; }
void AddOrderMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint64_t AddOrderMessage::order_id() const { return order_id_; }
void AddOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

Side AddOrderMessage::side() const { return side_; }
void AddOrderMessage::set_side(Side value) { side_ = value; }

std::uint32_t AddOrderMessage::quantity() const { return quantity_; }
void AddOrderMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t AddOrderMessage::instrument_id() const { return instrument_id_; }
void AddOrderMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

const std::array<std::byte, 1>& AddOrderMessage::reserved_a() const { return reserved_a_; }
std::array<std::byte, 1>& AddOrderMessage::reserved_a() { return reserved_a_; }
void AddOrderMessage::set_reserved_a(const std::array<std::byte, 1>& value) { reserved_a_ = value; }

const std::array<std::byte, 1>& AddOrderMessage::reserved_b() const { return reserved_b_; }
std::array<std::byte, 1>& AddOrderMessage::reserved_b() { return reserved_b_; }
void AddOrderMessage::set_reserved_b(const std::array<std::byte, 1>& value) { reserved_b_ = value; }

std::int64_t AddOrderMessage::price() const { return price_; }
void AddOrderMessage::set_price(std::int64_t value) { price_ = value; }

const AddOrderFlags& AddOrderMessage::add_order_flags() const { return add_order_flags_; }
AddOrderFlags& AddOrderMessage::add_order_flags() { return add_order_flags_; }
void AddOrderMessage::set_add_order_flags(const AddOrderFlags& value) { add_order_flags_ = value; }

const std::array<std::byte, 10>& AddOrderMessage::reserved_10() const { return reserved_10_; }
std::array<std::byte, 10>& AddOrderMessage::reserved_10() { return reserved_10_; }
void AddOrderMessage::set_reserved_10(const std::array<std::byte, 10>& value) { reserved_10_ = value; }

MessageCode AddOrderMessage::type() const { return message_type; }

std::string_view AddOrderMessage::name() const { return "Add Order Message"; }

std::size_t AddOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    price_ = wire::read_i64_le(data + offset);
    offset += 8;

    offset += add_order_flags_.decode(data + offset, length - offset);

    wire::read_bytes(data + offset, reserved_10_.data(), 10);
    offset += 10;

    return offset;
}

std::size_t AddOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_));
    offset += 8;

    offset += add_order_flags_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, reserved_10_.data(), 10);
    offset += 10;

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
    out << "nanosecond=";
    out << nanosecond_;
    out << ", order_id=";
    out << order_id_;
    out << ", side=";
    out << side_;
    out << ", quantity=";
    out << quantity_;
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", reserved_a=";
    print::hex(out, reserved_a_.data(), reserved_a_.size());
    out << ", reserved_b=";
    print::hex(out, reserved_b_.data(), reserved_b_.size());
    out << ", price=";
    out << price_;
    out << ", add_order_flags=";
    add_order_flags_.print(out);
    out << ", reserved_10=";
    print::hex(out, reserved_10_.data(), reserved_10_.size());
    out << '}';
}

bool AddOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderMessage::operator==(const AddOrderMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && order_id_ == other.order_id_
        && side_ == other.side_
        && quantity_ == other.quantity_
        && instrument_id_ == other.instrument_id_
        && reserved_a_ == other.reserved_a_
        && reserved_b_ == other.reserved_b_
        && price_ == other.price_
        && add_order_flags_ == other.add_order_flags_
        && reserved_10_ == other.reserved_10_;
}

bool AddOrderMessage::operator!=(const AddOrderMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
