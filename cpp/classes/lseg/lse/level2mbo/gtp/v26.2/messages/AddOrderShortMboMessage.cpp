#include "AddOrderShortMboMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

AddOrderShortMboMessage::AddOrderShortMboMessage(std::uint64_t order_id, Decimal size, Decimal price, const std::array<std::byte, 8>& reserved_8, const std::string& participant)
  : order_id_(order_id), size_(size), price_(price), reserved_8_(reserved_8), participant_(participant) {}

std::uint64_t AddOrderShortMboMessage::order_id() const { return order_id_; }
void AddOrderShortMboMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

Decimal AddOrderShortMboMessage::size() const { return size_; }
void AddOrderShortMboMessage::set_size(Decimal value) { size_ = value; }

Decimal AddOrderShortMboMessage::price() const { return price_; }
void AddOrderShortMboMessage::set_price(Decimal value) { price_ = value; }

const std::array<std::byte, 8>& AddOrderShortMboMessage::reserved_8() const { return reserved_8_; }
std::array<std::byte, 8>& AddOrderShortMboMessage::reserved_8() { return reserved_8_; }
void AddOrderShortMboMessage::set_reserved_8(const std::array<std::byte, 8>& value) { reserved_8_ = value; }

const std::string& AddOrderShortMboMessage::participant() const { return participant_; }
std::string& AddOrderShortMboMessage::participant() { return participant_; }
void AddOrderShortMboMessage::set_participant(const std::string& value) { participant_ = value; }

MessageCode AddOrderShortMboMessage::type() const { return message_type; }

std::string_view AddOrderShortMboMessage::name() const { return "Add Order Short Mbo Message"; }

std::size_t AddOrderShortMboMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderShortMboMessage", wire_size, length);

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    size_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -8);
    offset += 8;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -8);
    offset += 8;

    wire::read_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    participant_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    return offset;
}

std::size_t AddOrderShortMboMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderShortMboMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(size_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    wire::write_text(data + offset, 11, ' ', participant_);
    offset += 11;

    return offset;
}

std::size_t AddOrderShortMboMessage::encoded_size() const {
    return wire_size;
}

void AddOrderShortMboMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddOrderShortMboMessage::clone() const {
    return std::make_unique<AddOrderShortMboMessage>(*this);
}

void AddOrderShortMboMessage::print(std::ostream& out) const {
    out << "AddOrderShortMboMessage{";
    out << "order_id=";
    out << order_id_;
    out << ", size=";
    out << size_;
    out << ", price=";
    out << price_;
    out << ", reserved_8=";
    print::hex(out, reserved_8_.data(), reserved_8_.size());
    out << ", participant=";
    print::text(out, participant_);
    out << '}';
}

bool AddOrderShortMboMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderShortMboMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderShortMboMessage::operator==(const AddOrderShortMboMessage& other) const {
    return order_id_ == other.order_id_
        && size_ == other.size_
        && price_ == other.price_
        && reserved_8_ == other.reserved_8_
        && participant_ == other.participant_;
}

bool AddOrderShortMboMessage::operator!=(const AddOrderShortMboMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
