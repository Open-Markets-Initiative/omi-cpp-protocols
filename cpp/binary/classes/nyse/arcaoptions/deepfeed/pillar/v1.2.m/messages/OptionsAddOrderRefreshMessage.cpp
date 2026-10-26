#include "OptionsAddOrderRefreshMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

OptionsAddOrderRefreshMessage::OptionsAddOrderRefreshMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint64_t order_id, std::int32_t price, std::uint32_t volume, Side side, const std::string& firm_id, const std::array<std::byte, 1>& reserved_1, CustIndicator cust_indicator)
  : source_time_(source_time), source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), order_id_(order_id), price_(price), volume_(volume), side_(side), firm_id_(firm_id), reserved_1_(reserved_1), cust_indicator_(cust_indicator) {}

std::uint32_t OptionsAddOrderRefreshMessage::source_time() const { return source_time_; }
void OptionsAddOrderRefreshMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t OptionsAddOrderRefreshMessage::source_time_ns() const { return source_time_ns_; }
void OptionsAddOrderRefreshMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsAddOrderRefreshMessage::series_index() const { return series_index_; }
void OptionsAddOrderRefreshMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsAddOrderRefreshMessage::series_seq_num() const { return series_seq_num_; }
void OptionsAddOrderRefreshMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

std::uint64_t OptionsAddOrderRefreshMessage::order_id() const { return order_id_; }
void OptionsAddOrderRefreshMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::int32_t OptionsAddOrderRefreshMessage::price() const { return price_; }
void OptionsAddOrderRefreshMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t OptionsAddOrderRefreshMessage::volume() const { return volume_; }
void OptionsAddOrderRefreshMessage::set_volume(std::uint32_t value) { volume_ = value; }

Side OptionsAddOrderRefreshMessage::side() const { return side_; }
void OptionsAddOrderRefreshMessage::set_side(Side value) { side_ = value; }

const std::string& OptionsAddOrderRefreshMessage::firm_id() const { return firm_id_; }
std::string& OptionsAddOrderRefreshMessage::firm_id() { return firm_id_; }
void OptionsAddOrderRefreshMessage::set_firm_id(const std::string& value) { firm_id_ = value; }

const std::array<std::byte, 1>& OptionsAddOrderRefreshMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& OptionsAddOrderRefreshMessage::reserved_1() { return reserved_1_; }
void OptionsAddOrderRefreshMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

CustIndicator OptionsAddOrderRefreshMessage::cust_indicator() const { return cust_indicator_; }
void OptionsAddOrderRefreshMessage::set_cust_indicator(CustIndicator value) { cust_indicator_ = value; }

MessageCode OptionsAddOrderRefreshMessage::type() const { return message_type; }

std::string_view OptionsAddOrderRefreshMessage::name() const { return "Options Add Order Refresh Message"; }

std::size_t OptionsAddOrderRefreshMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsAddOrderRefreshMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

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

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    firm_id_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    cust_indicator_ = static_cast<CustIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OptionsAddOrderRefreshMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsAddOrderRefreshMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

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

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_text(data + offset, 5, ' ', firm_id_);
    offset += 5;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(cust_indicator_));
    offset += 1;

    return offset;
}

std::size_t OptionsAddOrderRefreshMessage::encoded_size() const {
    return wire_size;
}

void OptionsAddOrderRefreshMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsAddOrderRefreshMessage::clone() const {
    return std::make_unique<OptionsAddOrderRefreshMessage>(*this);
}

void OptionsAddOrderRefreshMessage::print(std::ostream& out) const {
    out << "OptionsAddOrderRefreshMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
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
    out << ", side=";
    out << side_;
    out << ", firm_id=";
    print::text(out, firm_id_);
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", cust_indicator=";
    out << cust_indicator_;
    out << '}';
}

bool OptionsAddOrderRefreshMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsAddOrderRefreshMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsAddOrderRefreshMessage::operator==(const OptionsAddOrderRefreshMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && order_id_ == other.order_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && side_ == other.side_
        && firm_id_ == other.firm_id_
        && reserved_1_ == other.reserved_1_
        && cust_indicator_ == other.cust_indicator_;
}

bool OptionsAddOrderRefreshMessage::operator!=(const OptionsAddOrderRefreshMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
