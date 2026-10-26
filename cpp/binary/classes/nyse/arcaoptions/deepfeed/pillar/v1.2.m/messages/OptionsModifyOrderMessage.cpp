#include "OptionsModifyOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

OptionsModifyOrderMessage::OptionsModifyOrderMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint64_t order_id, std::int32_t price, std::uint32_t volume, std::uint8_t position_change, Side side, CustIndicator cust_indicator)
  : source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), order_id_(order_id), price_(price), volume_(volume), position_change_(position_change), side_(side), cust_indicator_(cust_indicator) {}

std::uint32_t OptionsModifyOrderMessage::source_time_ns() const { return source_time_ns_; }
void OptionsModifyOrderMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsModifyOrderMessage::series_index() const { return series_index_; }
void OptionsModifyOrderMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsModifyOrderMessage::series_seq_num() const { return series_seq_num_; }
void OptionsModifyOrderMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

std::uint64_t OptionsModifyOrderMessage::order_id() const { return order_id_; }
void OptionsModifyOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::int32_t OptionsModifyOrderMessage::price() const { return price_; }
void OptionsModifyOrderMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t OptionsModifyOrderMessage::volume() const { return volume_; }
void OptionsModifyOrderMessage::set_volume(std::uint32_t value) { volume_ = value; }

std::uint8_t OptionsModifyOrderMessage::position_change() const { return position_change_; }
void OptionsModifyOrderMessage::set_position_change(std::uint8_t value) { position_change_ = value; }

Side OptionsModifyOrderMessage::side() const { return side_; }
void OptionsModifyOrderMessage::set_side(Side value) { side_ = value; }

CustIndicator OptionsModifyOrderMessage::cust_indicator() const { return cust_indicator_; }
void OptionsModifyOrderMessage::set_cust_indicator(CustIndicator value) { cust_indicator_ = value; }

MessageCode OptionsModifyOrderMessage::type() const { return message_type; }

std::string_view OptionsModifyOrderMessage::name() const { return "Options Modify Order Message"; }

std::size_t OptionsModifyOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsModifyOrderMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    position_change_ = wire::read_u8(data + offset);
    offset += 1;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    cust_indicator_ = static_cast<CustIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OptionsModifyOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsModifyOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(position_change_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(cust_indicator_));
    offset += 1;

    return offset;
}

std::size_t OptionsModifyOrderMessage::encoded_size() const {
    return wire_size;
}

void OptionsModifyOrderMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsModifyOrderMessage::clone() const {
    return std::make_unique<OptionsModifyOrderMessage>(*this);
}

void OptionsModifyOrderMessage::print(std::ostream& out) const {
    out << "OptionsModifyOrderMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", series_seq_num=";
    out << series_seq_num_;
    out << ", order_id=";
    out << order_id_;
    out << ", price=";
    out << price_;
    out << ", volume=";
    out << volume_;
    out << ", position_change=";
    out << static_cast<int>(position_change_);
    out << ", side=";
    out << side_;
    out << ", cust_indicator=";
    out << cust_indicator_;
    out << '}';
}

bool OptionsModifyOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsModifyOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsModifyOrderMessage::operator==(const OptionsModifyOrderMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && order_id_ == other.order_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && position_change_ == other.position_change_
        && side_ == other.side_
        && cust_indicator_ == other.cust_indicator_;
}

bool OptionsModifyOrderMessage::operator!=(const OptionsModifyOrderMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
