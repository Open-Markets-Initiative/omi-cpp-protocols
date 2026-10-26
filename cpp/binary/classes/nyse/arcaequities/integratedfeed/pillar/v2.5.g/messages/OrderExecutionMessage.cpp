#include "OrderExecutionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

OrderExecutionMessage::OrderExecutionMessage(std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, PrintableFlag printable_flag, const std::array<std::byte, 1>& reserved_1, TradeCond1 trade_cond_1, TradeCond2 trade_cond_2, TradeCond3 trade_cond_3, TradeCond4 trade_cond_4)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), order_id_(order_id), trade_id_(trade_id), price_(price), volume_(volume), printable_flag_(printable_flag), reserved_1_(reserved_1), trade_cond_1_(trade_cond_1), trade_cond_2_(trade_cond_2), trade_cond_3_(trade_cond_3), trade_cond_4_(trade_cond_4) {}

std::chrono::nanoseconds OrderExecutionMessage::source_time_ns() const { return source_time_ns_; }
void OrderExecutionMessage::set_source_time_ns(std::chrono::nanoseconds value) { source_time_ns_ = value; }

std::uint32_t OrderExecutionMessage::symbol_index() const { return symbol_index_; }
void OrderExecutionMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t OrderExecutionMessage::symbol_seq_num() const { return symbol_seq_num_; }
void OrderExecutionMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint64_t OrderExecutionMessage::order_id() const { return order_id_; }
void OrderExecutionMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderExecutionMessage::trade_id() const { return trade_id_; }
void OrderExecutionMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t OrderExecutionMessage::price() const { return price_; }
void OrderExecutionMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t OrderExecutionMessage::volume() const { return volume_; }
void OrderExecutionMessage::set_volume(std::uint32_t value) { volume_ = value; }

PrintableFlag OrderExecutionMessage::printable_flag() const { return printable_flag_; }
void OrderExecutionMessage::set_printable_flag(PrintableFlag value) { printable_flag_ = value; }

const std::array<std::byte, 1>& OrderExecutionMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& OrderExecutionMessage::reserved_1() { return reserved_1_; }
void OrderExecutionMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

TradeCond1 OrderExecutionMessage::trade_cond_1() const { return trade_cond_1_; }
void OrderExecutionMessage::set_trade_cond_1(TradeCond1 value) { trade_cond_1_ = value; }

TradeCond2 OrderExecutionMessage::trade_cond_2() const { return trade_cond_2_; }
void OrderExecutionMessage::set_trade_cond_2(TradeCond2 value) { trade_cond_2_ = value; }

TradeCond3 OrderExecutionMessage::trade_cond_3() const { return trade_cond_3_; }
void OrderExecutionMessage::set_trade_cond_3(TradeCond3 value) { trade_cond_3_ = value; }

TradeCond4 OrderExecutionMessage::trade_cond_4() const { return trade_cond_4_; }
void OrderExecutionMessage::set_trade_cond_4(TradeCond4 value) { trade_cond_4_ = value; }

MessageCode OrderExecutionMessage::type() const { return message_type; }

std::string_view OrderExecutionMessage::name() const { return "Order Execution Message"; }

std::size_t OrderExecutionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutionMessage", wire_size, length);

    source_time_ns_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
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

    trade_cond_2_ = static_cast<TradeCond2>(wire::read_char(data + offset));
    offset += 1;

    trade_cond_3_ = static_cast<TradeCond3>(wire::read_char(data + offset));
    offset += 1;

    trade_cond_4_ = static_cast<TradeCond4>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderExecutionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutionMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
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

    wire::write_char(data + offset, static_cast<char>(trade_cond_2_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_cond_3_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_cond_4_));
    offset += 1;

    return offset;
}

std::size_t OrderExecutionMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderExecutionMessage::clone() const {
    return std::make_unique<OrderExecutionMessage>(*this);
}

void OrderExecutionMessage::print(std::ostream& out) const {
    out << "OrderExecutionMessage{";
    out << "source_time_ns=";
    out << source_time_ns_.count();
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
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
    out << ", trade_cond_2=";
    out << trade_cond_2_;
    out << ", trade_cond_3=";
    out << trade_cond_3_;
    out << ", trade_cond_4=";
    out << trade_cond_4_;
    out << '}';
}

bool OrderExecutionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutionMessage::operator==(const OrderExecutionMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && order_id_ == other.order_id_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && printable_flag_ == other.printable_flag_
        && reserved_1_ == other.reserved_1_
        && trade_cond_1_ == other.trade_cond_1_
        && trade_cond_2_ == other.trade_cond_2_
        && trade_cond_3_ == other.trade_cond_3_
        && trade_cond_4_ == other.trade_cond_4_;
}

bool OrderExecutionMessage::operator!=(const OrderExecutionMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g
