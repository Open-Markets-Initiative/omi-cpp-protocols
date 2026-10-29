#include "ComplexSymbolDefinitionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

ComplexSymbolDefinitionMessage::ComplexSymbolDefinitionMessage(std::uint32_t complex_index, const std::string& complex_symbol, std::uint8_t channel_id, MarketId market_id, std::uint8_t system_id, const std::array<std::byte, 1>& reserved_1, std::uint16_t stream_id, std::uint16_t no_of_legs, const std::array<std::byte, 2>& reserved_2, const std::vector<LegDefinition>& leg_definition)
  : complex_index_(complex_index), complex_symbol_(complex_symbol), channel_id_(channel_id), market_id_(market_id), system_id_(system_id), reserved_1_(reserved_1), stream_id_(stream_id), no_of_legs_(no_of_legs), reserved_2_(reserved_2), leg_definition_(leg_definition) {}

std::uint32_t ComplexSymbolDefinitionMessage::complex_index() const { return complex_index_; }
void ComplexSymbolDefinitionMessage::set_complex_index(std::uint32_t value) { complex_index_ = value; }

const std::string& ComplexSymbolDefinitionMessage::complex_symbol() const { return complex_symbol_; }
std::string& ComplexSymbolDefinitionMessage::complex_symbol() { return complex_symbol_; }
void ComplexSymbolDefinitionMessage::set_complex_symbol(const std::string& value) { complex_symbol_ = value; }

std::uint8_t ComplexSymbolDefinitionMessage::channel_id() const { return channel_id_; }
void ComplexSymbolDefinitionMessage::set_channel_id(std::uint8_t value) { channel_id_ = value; }

MarketId ComplexSymbolDefinitionMessage::market_id() const { return market_id_; }
void ComplexSymbolDefinitionMessage::set_market_id(MarketId value) { market_id_ = value; }

std::uint8_t ComplexSymbolDefinitionMessage::system_id() const { return system_id_; }
void ComplexSymbolDefinitionMessage::set_system_id(std::uint8_t value) { system_id_ = value; }

const std::array<std::byte, 1>& ComplexSymbolDefinitionMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& ComplexSymbolDefinitionMessage::reserved_1() { return reserved_1_; }
void ComplexSymbolDefinitionMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

std::uint16_t ComplexSymbolDefinitionMessage::stream_id() const { return stream_id_; }
void ComplexSymbolDefinitionMessage::set_stream_id(std::uint16_t value) { stream_id_ = value; }

std::uint16_t ComplexSymbolDefinitionMessage::no_of_legs() const { return no_of_legs_; }
void ComplexSymbolDefinitionMessage::set_no_of_legs(std::uint16_t value) { no_of_legs_ = value; }

const std::array<std::byte, 2>& ComplexSymbolDefinitionMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& ComplexSymbolDefinitionMessage::reserved_2() { return reserved_2_; }
void ComplexSymbolDefinitionMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

const std::vector<LegDefinition>& ComplexSymbolDefinitionMessage::leg_definition() const { return leg_definition_; }
std::vector<LegDefinition>& ComplexSymbolDefinitionMessage::leg_definition() { return leg_definition_; }
void ComplexSymbolDefinitionMessage::set_leg_definition(const std::vector<LegDefinition>& value) { leg_definition_ = value; }

MessageCode ComplexSymbolDefinitionMessage::type() const { return message_type; }

std::string_view ComplexSymbolDefinitionMessage::name() const { return "Complex Symbol Definition Message"; }

std::size_t ComplexSymbolDefinitionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ComplexSymbolDefinitionMessage", offset + 4, length);
    complex_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ComplexSymbolDefinitionMessage", offset + 21, length);
    complex_symbol_ = wire::read_text(data + offset, 21, '\0');
    offset += 21;

    wire::require("ComplexSymbolDefinitionMessage", offset + 1, length);
    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ComplexSymbolDefinitionMessage", offset + 2, length);
    market_id_ = static_cast<MarketId>(wire::read_u16_le(data + offset));
    offset += 2;

    wire::require("ComplexSymbolDefinitionMessage", offset + 1, length);
    system_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ComplexSymbolDefinitionMessage", offset + 1, length);
    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::require("ComplexSymbolDefinitionMessage", offset + 2, length);
    stream_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("ComplexSymbolDefinitionMessage", offset + 2, length);
    no_of_legs_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("ComplexSymbolDefinitionMessage", offset + 2, length);
    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    {
        const std::size_t count = wire::count(no_of_legs_);
        leg_definition_.clear();
        leg_definition_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            LegDefinition entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            leg_definition_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t ComplexSymbolDefinitionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexSymbolDefinitionMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto no_of_legs = no_of_legs_;
    no_of_legs = static_cast<std::uint16_t>(leg_definition_.size());

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(complex_index_));
    offset += 4;

    wire::write_text(data + offset, 21, '\0', complex_symbol_);
    offset += 21;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(market_id_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(system_id_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(stream_id_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(no_of_legs));
    offset += 2;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    for (const auto& entry : leg_definition_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t ComplexSymbolDefinitionMessage::encoded_size() const {
    return 4 + 21 + 1 + 2 + 1 + 1 + 2 + 2 + 2 + wire::encoded_size_of(leg_definition_);
}

void ComplexSymbolDefinitionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ComplexSymbolDefinitionMessage::clone() const {
    return std::make_unique<ComplexSymbolDefinitionMessage>(*this);
}

void ComplexSymbolDefinitionMessage::print(std::ostream& out) const {
    out << "ComplexSymbolDefinitionMessage{";
    out << "complex_index=";
    out << complex_index_;
    out << ", complex_symbol=";
    print::text(out, complex_symbol_);
    out << ", channel_id=";
    out << static_cast<int>(channel_id_);
    out << ", market_id=";
    out << market_id_;
    out << ", system_id=";
    out << static_cast<int>(system_id_);
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", stream_id=";
    out << stream_id_;
    out << ", no_of_legs=";
    out << no_of_legs_;
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << ", leg_definition=";
    print::sequence(out, leg_definition_);
    out << '}';
}

bool ComplexSymbolDefinitionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ComplexSymbolDefinitionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexSymbolDefinitionMessage::operator==(const ComplexSymbolDefinitionMessage& other) const {
    return complex_index_ == other.complex_index_
        && complex_symbol_ == other.complex_symbol_
        && channel_id_ == other.channel_id_
        && market_id_ == other.market_id_
        && system_id_ == other.system_id_
        && reserved_1_ == other.reserved_1_
        && stream_id_ == other.stream_id_
        && no_of_legs_ == other.no_of_legs_
        && reserved_2_ == other.reserved_2_
        && leg_definition_ == other.leg_definition_;
}

bool ComplexSymbolDefinitionMessage::operator!=(const ComplexSymbolDefinitionMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
