#include "AddOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

AddOrderMessage::AddOrderMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::uint32_t price, std::uint32_t volume, Side side, const std::string& firm_id, std::uint8_t num_parity_splits)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), order_id_(order_id), price_(price), volume_(volume), side_(side), firm_id_(firm_id), num_parity_splits_(num_parity_splits) {}

std::uint32_t AddOrderMessage::source_time_ns() const { return source_time_ns_; }
void AddOrderMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t AddOrderMessage::symbol_index() const { return symbol_index_; }
void AddOrderMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t AddOrderMessage::symbol_seq_num() const { return symbol_seq_num_; }
void AddOrderMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint64_t AddOrderMessage::order_id() const { return order_id_; }
void AddOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t AddOrderMessage::price() const { return price_; }
void AddOrderMessage::set_price(std::uint32_t value) { price_ = value; }

std::uint32_t AddOrderMessage::volume() const { return volume_; }
void AddOrderMessage::set_volume(std::uint32_t value) { volume_ = value; }

Side AddOrderMessage::side() const { return side_; }
void AddOrderMessage::set_side(Side value) { side_ = value; }

const std::string& AddOrderMessage::firm_id() const { return firm_id_; }
std::string& AddOrderMessage::firm_id() { return firm_id_; }
void AddOrderMessage::set_firm_id(const std::string& value) { firm_id_ = value; }

std::uint8_t AddOrderMessage::num_parity_splits() const { return num_parity_splits_; }
void AddOrderMessage::set_num_parity_splits(std::uint8_t value) { num_parity_splits_ = value; }

MessageCode AddOrderMessage::type() const { return message_type; }

std::string_view AddOrderMessage::name() const { return "Add Order Message"; }

std::size_t AddOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = wire::read_u32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    firm_id_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    num_parity_splits_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t AddOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_text(data + offset, 5, ' ', firm_id_);
    offset += 5;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(num_parity_splits_));
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
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", order_id=";
    out << order_id_;
    out << ", price=";
    out << price_;
    out << ", volume=";
    out << volume_;
    out << ", side=";
    out << side_;
    out << ", firm_id=";
    print::text(out, firm_id_);
    out << ", num_parity_splits=";
    out << static_cast<int>(num_parity_splits_);
    out << '}';
}

bool AddOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderMessage::operator==(const AddOrderMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && order_id_ == other.order_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && side_ == other.side_
        && firm_id_ == other.firm_id_
        && num_parity_splits_ == other.num_parity_splits_;
}

bool AddOrderMessage::operator!=(const AddOrderMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
