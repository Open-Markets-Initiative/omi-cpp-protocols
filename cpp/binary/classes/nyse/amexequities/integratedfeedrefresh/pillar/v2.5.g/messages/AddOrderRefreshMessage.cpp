#include "AddOrderRefreshMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

AddOrderRefreshMessage::AddOrderRefreshMessage(std::chrono::seconds source_time, std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::int32_t price, std::uint32_t volume, Side side, const std::string& firm_id, const std::array<std::byte, 1>& reserved_1)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), order_id_(order_id), price_(price), volume_(volume), side_(side), firm_id_(firm_id), reserved_1_(reserved_1) {}

std::chrono::seconds AddOrderRefreshMessage::source_time() const { return source_time_; }
void AddOrderRefreshMessage::set_source_time(std::chrono::seconds value) { source_time_ = value; }

std::chrono::nanoseconds AddOrderRefreshMessage::source_time_ns() const { return source_time_ns_; }
void AddOrderRefreshMessage::set_source_time_ns(std::chrono::nanoseconds value) { source_time_ns_ = value; }

std::uint32_t AddOrderRefreshMessage::symbol_index() const { return symbol_index_; }
void AddOrderRefreshMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t AddOrderRefreshMessage::symbol_seq_num() const { return symbol_seq_num_; }
void AddOrderRefreshMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint64_t AddOrderRefreshMessage::order_id() const { return order_id_; }
void AddOrderRefreshMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::int32_t AddOrderRefreshMessage::price() const { return price_; }
void AddOrderRefreshMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t AddOrderRefreshMessage::volume() const { return volume_; }
void AddOrderRefreshMessage::set_volume(std::uint32_t value) { volume_ = value; }

Side AddOrderRefreshMessage::side() const { return side_; }
void AddOrderRefreshMessage::set_side(Side value) { side_ = value; }

const std::string& AddOrderRefreshMessage::firm_id() const { return firm_id_; }
std::string& AddOrderRefreshMessage::firm_id() { return firm_id_; }
void AddOrderRefreshMessage::set_firm_id(const std::string& value) { firm_id_ = value; }

const std::array<std::byte, 1>& AddOrderRefreshMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& AddOrderRefreshMessage::reserved_1() { return reserved_1_; }
void AddOrderRefreshMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

MessageCode AddOrderRefreshMessage::type() const { return message_type; }

std::string_view AddOrderRefreshMessage::name() const { return "Add Order Refresh Message"; }

std::size_t AddOrderRefreshMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderRefreshMessage", wire_size, length);

    source_time_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    source_time_ns_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    firm_id_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t AddOrderRefreshMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderRefreshMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_text(data + offset, 5, ' ', firm_id_);
    offset += 5;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t AddOrderRefreshMessage::encoded_size() const {
    return wire_size;
}

void AddOrderRefreshMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddOrderRefreshMessage::clone() const {
    return std::make_unique<AddOrderRefreshMessage>(*this);
}

void AddOrderRefreshMessage::print(std::ostream& out) const {
    out << "AddOrderRefreshMessage{";
    out << "source_time=";
    out << source_time_.count();
    out << ", source_time_ns=";
    out << source_time_ns_.count();
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
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << '}';
}

bool AddOrderRefreshMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderRefreshMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderRefreshMessage::operator==(const AddOrderRefreshMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && order_id_ == other.order_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && side_ == other.side_
        && firm_id_ == other.firm_id_
        && reserved_1_ == other.reserved_1_;
}

bool AddOrderRefreshMessage::operator!=(const AddOrderRefreshMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g
