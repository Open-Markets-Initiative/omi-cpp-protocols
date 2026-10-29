#include "TrfTradeCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

TrfTradeCancelMessage::TrfTradeCancelMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t original_trade_id)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), original_trade_id_(original_trade_id) {}

std::uint32_t TrfTradeCancelMessage::source_time() const { return source_time_; }
void TrfTradeCancelMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t TrfTradeCancelMessage::source_time_ns() const { return source_time_ns_; }
void TrfTradeCancelMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t TrfTradeCancelMessage::symbol_index() const { return symbol_index_; }
void TrfTradeCancelMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t TrfTradeCancelMessage::symbol_seq_num() const { return symbol_seq_num_; }
void TrfTradeCancelMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t TrfTradeCancelMessage::original_trade_id() const { return original_trade_id_; }
void TrfTradeCancelMessage::set_original_trade_id(std::uint32_t value) { original_trade_id_ = value; }

MessageCode TrfTradeCancelMessage::type() const { return message_type; }

std::string_view TrfTradeCancelMessage::name() const { return "Trf Trade Cancel Message"; }

std::size_t TrfTradeCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TrfTradeCancelMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    original_trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t TrfTradeCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TrfTradeCancelMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(original_trade_id_));
    offset += 4;

    return offset;
}

std::size_t TrfTradeCancelMessage::encoded_size() const {
    return wire_size;
}

void TrfTradeCancelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TrfTradeCancelMessage::clone() const {
    return std::make_unique<TrfTradeCancelMessage>(*this);
}

void TrfTradeCancelMessage::print(std::ostream& out) const {
    out << "TrfTradeCancelMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", original_trade_id=";
    out << original_trade_id_;
    out << '}';
}

bool TrfTradeCancelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TrfTradeCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TrfTradeCancelMessage::operator==(const TrfTradeCancelMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && original_trade_id_ == other.original_trade_id_;
}

bool TrfTradeCancelMessage::operator!=(const TrfTradeCancelMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
