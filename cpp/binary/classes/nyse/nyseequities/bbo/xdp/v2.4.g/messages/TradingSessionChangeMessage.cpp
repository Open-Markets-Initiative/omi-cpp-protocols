#include "TradingSessionChangeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

TradingSessionChangeMessage::TradingSessionChangeMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint8_t trading_session)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), trading_session_(trading_session) {}

std::uint32_t TradingSessionChangeMessage::source_time() const { return source_time_; }
void TradingSessionChangeMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t TradingSessionChangeMessage::source_time_ns() const { return source_time_ns_; }
void TradingSessionChangeMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t TradingSessionChangeMessage::symbol_index() const { return symbol_index_; }
void TradingSessionChangeMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t TradingSessionChangeMessage::symbol_seq_num() const { return symbol_seq_num_; }
void TradingSessionChangeMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint8_t TradingSessionChangeMessage::trading_session() const { return trading_session_; }
void TradingSessionChangeMessage::set_trading_session(std::uint8_t value) { trading_session_ = value; }

MessageCode TradingSessionChangeMessage::type() const { return message_type; }

std::string_view TradingSessionChangeMessage::name() const { return "Trading Session Change Message"; }

std::size_t TradingSessionChangeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingSessionChangeMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    trading_session_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t TradingSessionChangeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingSessionChangeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_));
    offset += 1;

    return offset;
}

std::size_t TradingSessionChangeMessage::encoded_size() const {
    return wire_size;
}

void TradingSessionChangeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradingSessionChangeMessage::clone() const {
    return std::make_unique<TradingSessionChangeMessage>(*this);
}

void TradingSessionChangeMessage::print(std::ostream& out) const {
    out << "TradingSessionChangeMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", trading_session=";
    out << static_cast<int>(trading_session_);
    out << '}';
}

bool TradingSessionChangeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradingSessionChangeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingSessionChangeMessage::operator==(const TradingSessionChangeMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && trading_session_ == other.trading_session_;
}

bool TradingSessionChangeMessage::operator!=(const TradingSessionChangeMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
