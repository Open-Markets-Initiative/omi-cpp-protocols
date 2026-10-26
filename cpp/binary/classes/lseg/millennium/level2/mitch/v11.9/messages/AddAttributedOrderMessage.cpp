#include "AddAttributedOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

AddAttributedOrderMessage::AddAttributedOrderMessage(std::uint32_t nanosecond, std::uint64_t order_id, Side side, std::uint32_t quantity, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, std::int64_t price, const std::string& attribution, const AddAttributedOrderFlags& add_attributed_order_flags)
  : nanosecond_(nanosecond), order_id_(order_id), side_(side), quantity_(quantity), instrument_id_(instrument_id), reserved_a_(reserved_a), reserved_b_(reserved_b), price_(price), attribution_(attribution), add_attributed_order_flags_(add_attributed_order_flags) {}

std::uint32_t AddAttributedOrderMessage::nanosecond() const { return nanosecond_; }
void AddAttributedOrderMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint64_t AddAttributedOrderMessage::order_id() const { return order_id_; }
void AddAttributedOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

Side AddAttributedOrderMessage::side() const { return side_; }
void AddAttributedOrderMessage::set_side(Side value) { side_ = value; }

std::uint32_t AddAttributedOrderMessage::quantity() const { return quantity_; }
void AddAttributedOrderMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t AddAttributedOrderMessage::instrument_id() const { return instrument_id_; }
void AddAttributedOrderMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

const std::array<std::byte, 1>& AddAttributedOrderMessage::reserved_a() const { return reserved_a_; }
std::array<std::byte, 1>& AddAttributedOrderMessage::reserved_a() { return reserved_a_; }
void AddAttributedOrderMessage::set_reserved_a(const std::array<std::byte, 1>& value) { reserved_a_ = value; }

const std::array<std::byte, 1>& AddAttributedOrderMessage::reserved_b() const { return reserved_b_; }
std::array<std::byte, 1>& AddAttributedOrderMessage::reserved_b() { return reserved_b_; }
void AddAttributedOrderMessage::set_reserved_b(const std::array<std::byte, 1>& value) { reserved_b_ = value; }

std::int64_t AddAttributedOrderMessage::price() const { return price_; }
void AddAttributedOrderMessage::set_price(std::int64_t value) { price_ = value; }

const std::string& AddAttributedOrderMessage::attribution() const { return attribution_; }
std::string& AddAttributedOrderMessage::attribution() { return attribution_; }
void AddAttributedOrderMessage::set_attribution(const std::string& value) { attribution_ = value; }

const AddAttributedOrderFlags& AddAttributedOrderMessage::add_attributed_order_flags() const { return add_attributed_order_flags_; }
AddAttributedOrderFlags& AddAttributedOrderMessage::add_attributed_order_flags() { return add_attributed_order_flags_; }
void AddAttributedOrderMessage::set_add_attributed_order_flags(const AddAttributedOrderFlags& value) { add_attributed_order_flags_ = value; }

MessageCode AddAttributedOrderMessage::type() const { return message_type; }

std::string_view AddAttributedOrderMessage::name() const { return "Add Attributed Order Message"; }

std::size_t AddAttributedOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddAttributedOrderMessage", wire_size, length);

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

    attribution_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    offset += add_attributed_order_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t AddAttributedOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddAttributedOrderMessage", wire_size, capacity);

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

    wire::write_text(data + offset, 11, ' ', attribution_);
    offset += 11;

    offset += add_attributed_order_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t AddAttributedOrderMessage::encoded_size() const {
    return wire_size;
}

void AddAttributedOrderMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddAttributedOrderMessage::clone() const {
    return std::make_unique<AddAttributedOrderMessage>(*this);
}

void AddAttributedOrderMessage::print(std::ostream& out) const {
    out << "AddAttributedOrderMessage{";
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
    out << ", attribution=";
    print::text(out, attribution_);
    out << ", add_attributed_order_flags=";
    add_attributed_order_flags_.print(out);
    out << '}';
}

bool AddAttributedOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddAttributedOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddAttributedOrderMessage::operator==(const AddAttributedOrderMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && order_id_ == other.order_id_
        && side_ == other.side_
        && quantity_ == other.quantity_
        && instrument_id_ == other.instrument_id_
        && reserved_a_ == other.reserved_a_
        && reserved_b_ == other.reserved_b_
        && price_ == other.price_
        && attribution_ == other.attribution_
        && add_attributed_order_flags_ == other.add_attributed_order_flags_;
}

bool AddAttributedOrderMessage::operator!=(const AddAttributedOrderMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
