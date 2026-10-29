#include "SymbolStateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

SymbolStateMessage::SymbolStateMessage(std::chrono::nanoseconds timestamp, std::uint16_t symbol_id, const std::string& symbol, State state, char reserved_1, const std::string& info)
  : timestamp_(timestamp), symbol_id_(symbol_id), symbol_(symbol), state_(state), reserved_1_(reserved_1), info_(info) {}

std::chrono::nanoseconds SymbolStateMessage::timestamp() const { return timestamp_; }
void SymbolStateMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t SymbolStateMessage::symbol_id() const { return symbol_id_; }
void SymbolStateMessage::set_symbol_id(std::uint16_t value) { symbol_id_ = value; }

const std::string& SymbolStateMessage::symbol() const { return symbol_; }
std::string& SymbolStateMessage::symbol() { return symbol_; }
void SymbolStateMessage::set_symbol(const std::string& value) { symbol_ = value; }

State SymbolStateMessage::state() const { return state_; }
void SymbolStateMessage::set_state(State value) { state_ = value; }

char SymbolStateMessage::reserved_1() const { return reserved_1_; }
void SymbolStateMessage::set_reserved_1(char value) { reserved_1_ = value; }

const std::string& SymbolStateMessage::info() const { return info_; }
std::string& SymbolStateMessage::info() { return info_; }
void SymbolStateMessage::set_info(const std::string& value) { info_ = value; }

MessageCode SymbolStateMessage::type() const { return message_type; }

std::string_view SymbolStateMessage::name() const { return "Symbol State Message"; }

std::size_t SymbolStateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolStateMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    symbol_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    state_ = static_cast<State>(wire::read_char(data + offset));
    offset += 1;

    reserved_1_ = wire::read_char(data + offset);
    offset += 1;

    info_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t SymbolStateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolStateMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(symbol_id_));
    offset += 2;

    wire::write_text(data + offset, 11, ' ', symbol_);
    offset += 11;

    wire::write_char(data + offset, static_cast<char>(state_));
    offset += 1;

    wire::write_char(data + offset, reserved_1_);
    offset += 1;

    wire::write_text(data + offset, 4, ' ', info_);
    offset += 4;

    return offset;
}

std::size_t SymbolStateMessage::encoded_size() const {
    return wire_size;
}

void SymbolStateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SymbolStateMessage::clone() const {
    return std::make_unique<SymbolStateMessage>(*this);
}

void SymbolStateMessage::print(std::ostream& out) const {
    out << "SymbolStateMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", state=";
    out << state_;
    out << ", reserved_1=";
    print::character(out, reserved_1_);
    out << ", info=";
    print::text(out, info_);
    out << '}';
}

bool SymbolStateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SymbolStateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolStateMessage::operator==(const SymbolStateMessage& other) const {
    return timestamp_ == other.timestamp_
        && symbol_id_ == other.symbol_id_
        && symbol_ == other.symbol_
        && state_ == other.state_
        && reserved_1_ == other.reserved_1_
        && info_ == other.info_;
}

bool SymbolStateMessage::operator!=(const SymbolStateMessage& other) const {
    return !(*this == other);
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
