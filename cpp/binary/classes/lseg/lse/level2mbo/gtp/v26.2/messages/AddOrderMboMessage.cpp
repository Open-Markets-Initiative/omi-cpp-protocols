#include "AddOrderMboMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

AddOrderMboMessage::AddOrderMboMessage(std::chrono::nanoseconds timestamp, std::uint64_t order_id, Side side, Decimal size, std::uint64_t instrument, Decimal price, const std::array<std::byte, 8>& reserved_8, SourceVenue source_venue, OrderBookType order_book_type, const std::string& participant, std::uint8_t depth)
  : timestamp_(timestamp), order_id_(order_id), side_(side), size_(size), instrument_(instrument), price_(price), reserved_8_(reserved_8), source_venue_(source_venue), order_book_type_(order_book_type), participant_(participant), depth_(depth) {}

std::chrono::nanoseconds AddOrderMboMessage::timestamp() const { return timestamp_; }
void AddOrderMboMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t AddOrderMboMessage::order_id() const { return order_id_; }
void AddOrderMboMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

Side AddOrderMboMessage::side() const { return side_; }
void AddOrderMboMessage::set_side(Side value) { side_ = value; }

Decimal AddOrderMboMessage::size() const { return size_; }
void AddOrderMboMessage::set_size(Decimal value) { size_ = value; }

std::uint64_t AddOrderMboMessage::instrument() const { return instrument_; }
void AddOrderMboMessage::set_instrument(std::uint64_t value) { instrument_ = value; }

Decimal AddOrderMboMessage::price() const { return price_; }
void AddOrderMboMessage::set_price(Decimal value) { price_ = value; }

const std::array<std::byte, 8>& AddOrderMboMessage::reserved_8() const { return reserved_8_; }
std::array<std::byte, 8>& AddOrderMboMessage::reserved_8() { return reserved_8_; }
void AddOrderMboMessage::set_reserved_8(const std::array<std::byte, 8>& value) { reserved_8_ = value; }

SourceVenue AddOrderMboMessage::source_venue() const { return source_venue_; }
void AddOrderMboMessage::set_source_venue(SourceVenue value) { source_venue_ = value; }

OrderBookType AddOrderMboMessage::order_book_type() const { return order_book_type_; }
void AddOrderMboMessage::set_order_book_type(OrderBookType value) { order_book_type_ = value; }

const std::string& AddOrderMboMessage::participant() const { return participant_; }
std::string& AddOrderMboMessage::participant() { return participant_; }
void AddOrderMboMessage::set_participant(const std::string& value) { participant_ = value; }

std::uint8_t AddOrderMboMessage::depth() const { return depth_; }
void AddOrderMboMessage::set_depth(std::uint8_t value) { depth_ = value; }

MessageCode AddOrderMboMessage::type() const { return message_type; }

std::string_view AddOrderMboMessage::name() const { return "Add Order Mbo Message"; }

std::size_t AddOrderMboMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderMboMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    size_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -8);
    offset += 8;

    instrument_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -8);
    offset += 8;

    wire::read_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    source_venue_ = static_cast<SourceVenue>(wire::read_u16_le(data + offset));
    offset += 2;

    order_book_type_ = static_cast<OrderBookType>(wire::read_u8(data + offset));
    offset += 1;

    participant_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    depth_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t AddOrderMboMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderMboMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(size_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(instrument_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_bytes(data + offset, reserved_8_.data(), 8);
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(source_venue_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(order_book_type_));
    offset += 1;

    wire::write_text(data + offset, 11, ' ', participant_);
    offset += 11;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(depth_));
    offset += 1;

    return offset;
}

std::size_t AddOrderMboMessage::encoded_size() const {
    return wire_size;
}

void AddOrderMboMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddOrderMboMessage::clone() const {
    return std::make_unique<AddOrderMboMessage>(*this);
}

void AddOrderMboMessage::print(std::ostream& out) const {
    out << "AddOrderMboMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", side=";
    out << side_;
    out << ", size=";
    out << size_;
    out << ", instrument=";
    out << instrument_;
    out << ", price=";
    out << price_;
    out << ", reserved_8=";
    print::hex(out, reserved_8_.data(), reserved_8_.size());
    out << ", source_venue=";
    out << source_venue_;
    out << ", order_book_type=";
    out << order_book_type_;
    out << ", participant=";
    print::text(out, participant_);
    out << ", depth=";
    out << static_cast<int>(depth_);
    out << '}';
}

bool AddOrderMboMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderMboMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderMboMessage::operator==(const AddOrderMboMessage& other) const {
    return timestamp_ == other.timestamp_
        && order_id_ == other.order_id_
        && side_ == other.side_
        && size_ == other.size_
        && instrument_ == other.instrument_
        && price_ == other.price_
        && reserved_8_ == other.reserved_8_
        && source_venue_ == other.source_venue_
        && order_book_type_ == other.order_book_type_
        && participant_ == other.participant_
        && depth_ == other.depth_;
}

bool AddOrderMboMessage::operator!=(const AddOrderMboMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
