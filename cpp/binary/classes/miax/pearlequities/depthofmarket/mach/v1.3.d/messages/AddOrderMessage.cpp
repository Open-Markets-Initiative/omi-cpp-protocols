#include "AddOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

AddOrderMessage::AddOrderMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, std::uint64_t order_id, OrderSide order_side, Decimal price, std::uint32_t size, const std::string& attributable_id)
  : nanoseconds_(nanoseconds), symbol_id_(symbol_id), order_id_(order_id), order_side_(order_side), price_(price), size_(size), attributable_id_(attributable_id) {}

std::chrono::nanoseconds AddOrderMessage::nanoseconds() const { return nanoseconds_; }
void AddOrderMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t AddOrderMessage::symbol_id() const { return symbol_id_; }
void AddOrderMessage::set_symbol_id(std::uint32_t value) { symbol_id_ = value; }

std::uint64_t AddOrderMessage::order_id() const { return order_id_; }
void AddOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

OrderSide AddOrderMessage::order_side() const { return order_side_; }
void AddOrderMessage::set_order_side(OrderSide value) { order_side_ = value; }

Decimal AddOrderMessage::price() const { return price_; }
void AddOrderMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t AddOrderMessage::size() const { return size_; }
void AddOrderMessage::set_size(std::uint32_t value) { size_ = value; }

const std::string& AddOrderMessage::attributable_id() const { return attributable_id_; }
std::string& AddOrderMessage::attributable_id() { return attributable_id_; }
void AddOrderMessage::set_attributable_id(const std::string& value) { attributable_id_ = value; }

DataCode AddOrderMessage::type() const { return message_type; }

std::string_view AddOrderMessage::name() const { return "Add Order Message"; }

std::size_t AddOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    order_side_ = static_cast<OrderSide>(wire::read_char(data + offset));
    offset += 1;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -6);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    attributable_id_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t AddOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(order_side_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', attributable_id_);
    offset += 4;

    return offset;
}

std::size_t AddOrderMessage::encoded_size() const {
    return wire_size;
}

void AddOrderMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> AddOrderMessage::clone() const {
    return std::make_unique<AddOrderMessage>(*this);
}

void AddOrderMessage::print(std::ostream& out) const {
    out << "AddOrderMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << ", order_id=";
    out << order_id_;
    out << ", order_side=";
    out << order_side_;
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << ", attributable_id=";
    print::text(out, attributable_id_);
    out << '}';
}

bool AddOrderMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const AddOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderMessage::operator==(const AddOrderMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && symbol_id_ == other.symbol_id_
        && order_id_ == other.order_id_
        && order_side_ == other.order_side_
        && price_ == other.price_
        && size_ == other.size_
        && attributable_id_ == other.attributable_id_;
}

bool AddOrderMessage::operator!=(const AddOrderMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
