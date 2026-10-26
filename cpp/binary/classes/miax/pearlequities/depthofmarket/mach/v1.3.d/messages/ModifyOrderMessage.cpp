#include "ModifyOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

ModifyOrderMessage::ModifyOrderMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, std::uint64_t order_id, Decimal price, std::uint32_t size, const ModifyOrderFlags& modify_order_flags)
  : nanoseconds_(nanoseconds), symbol_id_(symbol_id), order_id_(order_id), price_(price), size_(size), modify_order_flags_(modify_order_flags) {}

std::chrono::nanoseconds ModifyOrderMessage::nanoseconds() const { return nanoseconds_; }
void ModifyOrderMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t ModifyOrderMessage::symbol_id() const { return symbol_id_; }
void ModifyOrderMessage::set_symbol_id(std::uint32_t value) { symbol_id_ = value; }

std::uint64_t ModifyOrderMessage::order_id() const { return order_id_; }
void ModifyOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

Decimal ModifyOrderMessage::price() const { return price_; }
void ModifyOrderMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t ModifyOrderMessage::size() const { return size_; }
void ModifyOrderMessage::set_size(std::uint32_t value) { size_ = value; }

const ModifyOrderFlags& ModifyOrderMessage::modify_order_flags() const { return modify_order_flags_; }
ModifyOrderFlags& ModifyOrderMessage::modify_order_flags() { return modify_order_flags_; }
void ModifyOrderMessage::set_modify_order_flags(const ModifyOrderFlags& value) { modify_order_flags_ = value; }

DataCode ModifyOrderMessage::type() const { return message_type; }

std::string_view ModifyOrderMessage::name() const { return "Modify Order Message"; }

std::size_t ModifyOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ModifyOrderMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -6);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += modify_order_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ModifyOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ModifyOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    offset += modify_order_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ModifyOrderMessage::encoded_size() const {
    return wire_size;
}

void ModifyOrderMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> ModifyOrderMessage::clone() const {
    return std::make_unique<ModifyOrderMessage>(*this);
}

void ModifyOrderMessage::print(std::ostream& out) const {
    out << "ModifyOrderMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << ", order_id=";
    out << order_id_;
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << ", modify_order_flags=";
    modify_order_flags_.print(out);
    out << '}';
}

bool ModifyOrderMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const ModifyOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ModifyOrderMessage::operator==(const ModifyOrderMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && symbol_id_ == other.symbol_id_
        && order_id_ == other.order_id_
        && price_ == other.price_
        && size_ == other.size_
        && modify_order_flags_ == other.modify_order_flags_;
}

bool ModifyOrderMessage::operator!=(const ModifyOrderMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
