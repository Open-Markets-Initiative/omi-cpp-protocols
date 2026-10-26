#include "AddOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

AddOrderMessage::AddOrderMessage(Side side, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint64_t order_id, std::uint32_t size, Decimal price)
  : side_(side), timestamp_(timestamp), symbol_(symbol), order_id_(order_id), size_(size), price_(price) {}

Side AddOrderMessage::side() const { return side_; }
void AddOrderMessage::set_side(Side value) { side_ = value; }

std::chrono::nanoseconds AddOrderMessage::timestamp() const { return timestamp_; }
void AddOrderMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& AddOrderMessage::symbol() const { return symbol_; }
std::string& AddOrderMessage::symbol() { return symbol_; }
void AddOrderMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint64_t AddOrderMessage::order_id() const { return order_id_; }
void AddOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t AddOrderMessage::size() const { return size_; }
void AddOrderMessage::set_size(std::uint32_t value) { size_ = value; }

Decimal AddOrderMessage::price() const { return price_; }
void AddOrderMessage::set_price(Decimal value) { price_ = value; }

MessageCode AddOrderMessage::type() const { return message_type; }

std::string_view AddOrderMessage::name() const { return "Add Order Message"; }

std::size_t AddOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderMessage", wire_size, length);

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t AddOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

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
    out << "side=";
    out << side_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", order_id=";
    out << order_id_;
    out << ", size=";
    out << size_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool AddOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderMessage::operator==(const AddOrderMessage& other) const {
    return side_ == other.side_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && order_id_ == other.order_id_
        && size_ == other.size_
        && price_ == other.price_;
}

bool AddOrderMessage::operator!=(const AddOrderMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deepplus::iextp::v1_01
