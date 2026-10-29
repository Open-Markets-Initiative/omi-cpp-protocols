#include "RefreshComplexTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

RefreshComplexTradeMessage::RefreshComplexTradeMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t complex_index, std::uint32_t symbol_seq_num, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume_4, TradeCond1 trade_cond_1, char trade_cond_2, const std::array<std::byte, 2>& reserved_2)
  : source_time_(source_time), source_time_ns_(source_time_ns), complex_index_(complex_index), symbol_seq_num_(symbol_seq_num), trade_id_(trade_id), price_(price), volume_4_(volume_4), trade_cond_1_(trade_cond_1), trade_cond_2_(trade_cond_2), reserved_2_(reserved_2) {}

std::uint32_t RefreshComplexTradeMessage::source_time() const { return source_time_; }
void RefreshComplexTradeMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t RefreshComplexTradeMessage::source_time_ns() const { return source_time_ns_; }
void RefreshComplexTradeMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t RefreshComplexTradeMessage::complex_index() const { return complex_index_; }
void RefreshComplexTradeMessage::set_complex_index(std::uint32_t value) { complex_index_ = value; }

std::uint32_t RefreshComplexTradeMessage::symbol_seq_num() const { return symbol_seq_num_; }
void RefreshComplexTradeMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t RefreshComplexTradeMessage::trade_id() const { return trade_id_; }
void RefreshComplexTradeMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t RefreshComplexTradeMessage::price() const { return price_; }
void RefreshComplexTradeMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t RefreshComplexTradeMessage::volume_4() const { return volume_4_; }
void RefreshComplexTradeMessage::set_volume_4(std::uint32_t value) { volume_4_ = value; }

TradeCond1 RefreshComplexTradeMessage::trade_cond_1() const { return trade_cond_1_; }
void RefreshComplexTradeMessage::set_trade_cond_1(TradeCond1 value) { trade_cond_1_ = value; }

char RefreshComplexTradeMessage::trade_cond_2() const { return trade_cond_2_; }
void RefreshComplexTradeMessage::set_trade_cond_2(char value) { trade_cond_2_ = value; }

const std::array<std::byte, 2>& RefreshComplexTradeMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& RefreshComplexTradeMessage::reserved_2() { return reserved_2_; }
void RefreshComplexTradeMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

MessageCode RefreshComplexTradeMessage::type() const { return message_type; }

std::string_view RefreshComplexTradeMessage::name() const { return "Refresh Complex Trade Message"; }

std::size_t RefreshComplexTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RefreshComplexTradeMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    complex_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    volume_4_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_cond_1_ = static_cast<TradeCond1>(wire::read_char(data + offset));
    offset += 1;

    trade_cond_2_ = wire::read_char(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t RefreshComplexTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RefreshComplexTradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(complex_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_4_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(trade_cond_1_));
    offset += 1;

    wire::write_char(data + offset, trade_cond_2_);
    offset += 1;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t RefreshComplexTradeMessage::encoded_size() const {
    return wire_size;
}

void RefreshComplexTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RefreshComplexTradeMessage::clone() const {
    return std::make_unique<RefreshComplexTradeMessage>(*this);
}

void RefreshComplexTradeMessage::print(std::ostream& out) const {
    out << "RefreshComplexTradeMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", complex_index=";
    out << complex_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", price=";
    out << price_;
    out << ", volume_4=";
    out << volume_4_;
    out << ", trade_cond_1=";
    out << trade_cond_1_;
    out << ", trade_cond_2=";
    print::character(out, trade_cond_2_);
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << '}';
}

bool RefreshComplexTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RefreshComplexTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RefreshComplexTradeMessage::operator==(const RefreshComplexTradeMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && complex_index_ == other.complex_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && volume_4_ == other.volume_4_
        && trade_cond_1_ == other.trade_cond_1_
        && trade_cond_2_ == other.trade_cond_2_
        && reserved_2_ == other.reserved_2_;
}

bool RefreshComplexTradeMessage::operator!=(const RefreshComplexTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
