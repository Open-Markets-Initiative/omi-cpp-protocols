#include "OptionsOrderExecutionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

OptionsOrderExecutionMessage::OptionsOrderExecutionMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint64_t order_id, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, PrintableFlag printable_flag, const std::array<std::byte, 1>& reserved_1, TradeCond1 trade_cond_1, const std::array<std::byte, 3>& reserved_3)
  : source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), order_id_(order_id), trade_id_(trade_id), price_(price), volume_(volume), printable_flag_(printable_flag), reserved_1_(reserved_1), trade_cond_1_(trade_cond_1), reserved_3_(reserved_3) {}

std::uint32_t OptionsOrderExecutionMessage::source_time_ns() const { return source_time_ns_; }
void OptionsOrderExecutionMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsOrderExecutionMessage::series_index() const { return series_index_; }
void OptionsOrderExecutionMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsOrderExecutionMessage::series_seq_num() const { return series_seq_num_; }
void OptionsOrderExecutionMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

std::uint64_t OptionsOrderExecutionMessage::order_id() const { return order_id_; }
void OptionsOrderExecutionMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OptionsOrderExecutionMessage::trade_id() const { return trade_id_; }
void OptionsOrderExecutionMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t OptionsOrderExecutionMessage::price() const { return price_; }
void OptionsOrderExecutionMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t OptionsOrderExecutionMessage::volume() const { return volume_; }
void OptionsOrderExecutionMessage::set_volume(std::uint32_t value) { volume_ = value; }

PrintableFlag OptionsOrderExecutionMessage::printable_flag() const { return printable_flag_; }
void OptionsOrderExecutionMessage::set_printable_flag(PrintableFlag value) { printable_flag_ = value; }

const std::array<std::byte, 1>& OptionsOrderExecutionMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& OptionsOrderExecutionMessage::reserved_1() { return reserved_1_; }
void OptionsOrderExecutionMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

TradeCond1 OptionsOrderExecutionMessage::trade_cond_1() const { return trade_cond_1_; }
void OptionsOrderExecutionMessage::set_trade_cond_1(TradeCond1 value) { trade_cond_1_ = value; }

const std::array<std::byte, 3>& OptionsOrderExecutionMessage::reserved_3() const { return reserved_3_; }
std::array<std::byte, 3>& OptionsOrderExecutionMessage::reserved_3() { return reserved_3_; }
void OptionsOrderExecutionMessage::set_reserved_3(const std::array<std::byte, 3>& value) { reserved_3_ = value; }

MessageCode OptionsOrderExecutionMessage::type() const { return message_type; }

std::string_view OptionsOrderExecutionMessage::name() const { return "Options Order Execution Message"; }

std::size_t OptionsOrderExecutionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsOrderExecutionMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    printable_flag_ = static_cast<PrintableFlag>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    trade_cond_1_ = static_cast<TradeCond1>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t OptionsOrderExecutionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsOrderExecutionMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(printable_flag_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_cond_1_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t OptionsOrderExecutionMessage::encoded_size() const {
    return wire_size;
}

void OptionsOrderExecutionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsOrderExecutionMessage::clone() const {
    return std::make_unique<OptionsOrderExecutionMessage>(*this);
}

void OptionsOrderExecutionMessage::print(std::ostream& out) const {
    out << "OptionsOrderExecutionMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", series_seq_num=";
    out << series_seq_num_;
    out << ", order_id=";
    out << order_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", price=";
    out << price_;
    out << ", volume=";
    out << volume_;
    out << ", printable_flag=";
    out << printable_flag_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", trade_cond_1=";
    out << trade_cond_1_;
    out << ", reserved_3=";
    print::hex(out, reserved_3_.data(), reserved_3_.size());
    out << '}';
}

bool OptionsOrderExecutionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsOrderExecutionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsOrderExecutionMessage::operator==(const OptionsOrderExecutionMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && order_id_ == other.order_id_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && printable_flag_ == other.printable_flag_
        && reserved_1_ == other.reserved_1_
        && trade_cond_1_ == other.trade_cond_1_
        && reserved_3_ == other.reserved_3_;
}

bool OptionsOrderExecutionMessage::operator!=(const OptionsOrderExecutionMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
