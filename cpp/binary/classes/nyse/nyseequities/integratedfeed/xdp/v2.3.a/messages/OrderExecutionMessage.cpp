#include "OrderExecutionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

OrderExecutionMessage::OrderExecutionMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::uint32_t trade_id, std::uint32_t price, std::uint32_t volume, PrintableFlag printable_flag, std::uint8_t num_parity_splits, std::uint32_t db_exec_id)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), order_id_(order_id), trade_id_(trade_id), price_(price), volume_(volume), printable_flag_(printable_flag), num_parity_splits_(num_parity_splits), db_exec_id_(db_exec_id) {}

std::uint32_t OrderExecutionMessage::source_time_ns() const { return source_time_ns_; }
void OrderExecutionMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OrderExecutionMessage::symbol_index() const { return symbol_index_; }
void OrderExecutionMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t OrderExecutionMessage::symbol_seq_num() const { return symbol_seq_num_; }
void OrderExecutionMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint64_t OrderExecutionMessage::order_id() const { return order_id_; }
void OrderExecutionMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderExecutionMessage::trade_id() const { return trade_id_; }
void OrderExecutionMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::uint32_t OrderExecutionMessage::price() const { return price_; }
void OrderExecutionMessage::set_price(std::uint32_t value) { price_ = value; }

std::uint32_t OrderExecutionMessage::volume() const { return volume_; }
void OrderExecutionMessage::set_volume(std::uint32_t value) { volume_ = value; }

PrintableFlag OrderExecutionMessage::printable_flag() const { return printable_flag_; }
void OrderExecutionMessage::set_printable_flag(PrintableFlag value) { printable_flag_ = value; }

std::uint8_t OrderExecutionMessage::num_parity_splits() const { return num_parity_splits_; }
void OrderExecutionMessage::set_num_parity_splits(std::uint8_t value) { num_parity_splits_ = value; }

std::uint32_t OrderExecutionMessage::db_exec_id() const { return db_exec_id_; }
void OrderExecutionMessage::set_db_exec_id(std::uint32_t value) { db_exec_id_ = value; }

MessageCode OrderExecutionMessage::type() const { return message_type; }

std::string_view OrderExecutionMessage::name() const { return "Order Execution Message"; }

std::size_t OrderExecutionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutionMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = wire::read_u32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    printable_flag_ = static_cast<PrintableFlag>(wire::read_u8(data + offset));
    offset += 1;

    num_parity_splits_ = wire::read_u8(data + offset);
    offset += 1;

    db_exec_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t OrderExecutionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutionMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(printable_flag_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(num_parity_splits_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(db_exec_id_));
    offset += 4;

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
    out << source_time_ns_;
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
    out << ", num_parity_splits=";
    out << static_cast<int>(num_parity_splits_);
    out << ", db_exec_id=";
    out << db_exec_id_;
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
        && num_parity_splits_ == other.num_parity_splits_
        && db_exec_id_ == other.db_exec_id_;
}

bool OrderExecutionMessage::operator!=(const OrderExecutionMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
