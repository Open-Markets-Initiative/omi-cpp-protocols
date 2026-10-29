#include "TradeCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

TradeCancelMessage::TradeCancelMessage(std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t trade_id)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), trade_id_(trade_id) {}

std::chrono::nanoseconds TradeCancelMessage::source_time_ns() const { return source_time_ns_; }
void TradeCancelMessage::set_source_time_ns(std::chrono::nanoseconds value) { source_time_ns_ = value; }

std::uint32_t TradeCancelMessage::symbol_index() const { return symbol_index_; }
void TradeCancelMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t TradeCancelMessage::symbol_seq_num() const { return symbol_seq_num_; }
void TradeCancelMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t TradeCancelMessage::trade_id() const { return trade_id_; }
void TradeCancelMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

MessageCode TradeCancelMessage::type() const { return message_type; }

std::string_view TradeCancelMessage::name() const { return "Trade Cancel Message"; }

std::size_t TradeCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCancelMessage", wire_size, length);

    source_time_ns_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t TradeCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCancelMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    return offset;
}

std::size_t TradeCancelMessage::encoded_size() const {
    return wire_size;
}

void TradeCancelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeCancelMessage::clone() const {
    return std::make_unique<TradeCancelMessage>(*this);
}

void TradeCancelMessage::print(std::ostream& out) const {
    out << "TradeCancelMessage{";
    out << "source_time_ns=";
    out << source_time_ns_.count();
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", trade_id=";
    out << trade_id_;
    out << '}';
}

bool TradeCancelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeCancelMessage::operator==(const TradeCancelMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && trade_id_ == other.trade_id_;
}

bool TradeCancelMessage::operator!=(const TradeCancelMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g
