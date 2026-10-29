#include "ComplexInstrumentDefinitionExpandedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

ComplexInstrumentDefinitionExpandedMessage::ComplexInstrumentDefinitionExpandedMessage(std::chrono::nanoseconds time_offset, const std::string& complex_instrument_id, const std::string& complex_instrument_underlying, const std::string& complex_instrument_type, std::uint8_t leg_count, const std::vector<ComplexInstrumentLeg>& complex_instrument_leg)
  : time_offset_(time_offset), complex_instrument_id_(complex_instrument_id), complex_instrument_underlying_(complex_instrument_underlying), complex_instrument_type_(complex_instrument_type), leg_count_(leg_count), complex_instrument_leg_(complex_instrument_leg) {}

std::chrono::nanoseconds ComplexInstrumentDefinitionExpandedMessage::time_offset() const { return time_offset_; }
void ComplexInstrumentDefinitionExpandedMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& ComplexInstrumentDefinitionExpandedMessage::complex_instrument_id() const { return complex_instrument_id_; }
std::string& ComplexInstrumentDefinitionExpandedMessage::complex_instrument_id() { return complex_instrument_id_; }
void ComplexInstrumentDefinitionExpandedMessage::set_complex_instrument_id(const std::string& value) { complex_instrument_id_ = value; }

const std::string& ComplexInstrumentDefinitionExpandedMessage::complex_instrument_underlying() const { return complex_instrument_underlying_; }
std::string& ComplexInstrumentDefinitionExpandedMessage::complex_instrument_underlying() { return complex_instrument_underlying_; }
void ComplexInstrumentDefinitionExpandedMessage::set_complex_instrument_underlying(const std::string& value) { complex_instrument_underlying_ = value; }

const std::string& ComplexInstrumentDefinitionExpandedMessage::complex_instrument_type() const { return complex_instrument_type_; }
std::string& ComplexInstrumentDefinitionExpandedMessage::complex_instrument_type() { return complex_instrument_type_; }
void ComplexInstrumentDefinitionExpandedMessage::set_complex_instrument_type(const std::string& value) { complex_instrument_type_ = value; }

std::uint8_t ComplexInstrumentDefinitionExpandedMessage::leg_count() const { return leg_count_; }
void ComplexInstrumentDefinitionExpandedMessage::set_leg_count(std::uint8_t value) { leg_count_ = value; }

const std::vector<ComplexInstrumentLeg>& ComplexInstrumentDefinitionExpandedMessage::complex_instrument_leg() const { return complex_instrument_leg_; }
std::vector<ComplexInstrumentLeg>& ComplexInstrumentDefinitionExpandedMessage::complex_instrument_leg() { return complex_instrument_leg_; }
void ComplexInstrumentDefinitionExpandedMessage::set_complex_instrument_leg(const std::vector<ComplexInstrumentLeg>& value) { complex_instrument_leg_ = value; }

MessageCode ComplexInstrumentDefinitionExpandedMessage::type() const { return message_type; }

std::string_view ComplexInstrumentDefinitionExpandedMessage::name() const { return "Complex Instrument Definition Expanded Message"; }

std::size_t ComplexInstrumentDefinitionExpandedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ComplexInstrumentDefinitionExpandedMessage", offset + 4, length);
    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    wire::require("ComplexInstrumentDefinitionExpandedMessage", offset + 6, length);
    complex_instrument_id_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    wire::require("ComplexInstrumentDefinitionExpandedMessage", offset + 8, length);
    complex_instrument_underlying_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    wire::require("ComplexInstrumentDefinitionExpandedMessage", offset + 4, length);
    complex_instrument_type_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    wire::require("ComplexInstrumentDefinitionExpandedMessage", offset + 1, length);
    leg_count_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(leg_count_);
        complex_instrument_leg_.clear();
        complex_instrument_leg_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            ComplexInstrumentLeg entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            complex_instrument_leg_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t ComplexInstrumentDefinitionExpandedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexInstrumentDefinitionExpandedMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto leg_count = leg_count_;
    leg_count = static_cast<std::uint8_t>(complex_instrument_leg_.size());

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', complex_instrument_id_);
    offset += 6;

    wire::write_text(data + offset, 8, ' ', complex_instrument_underlying_);
    offset += 8;

    wire::write_text(data + offset, 4, ' ', complex_instrument_type_);
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(leg_count));
    offset += 1;

    for (const auto& entry : complex_instrument_leg_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t ComplexInstrumentDefinitionExpandedMessage::encoded_size() const {
    return 4 + 6 + 8 + 4 + 1 + wire::encoded_size_of(complex_instrument_leg_);
}

void ComplexInstrumentDefinitionExpandedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ComplexInstrumentDefinitionExpandedMessage::clone() const {
    return std::make_unique<ComplexInstrumentDefinitionExpandedMessage>(*this);
}

void ComplexInstrumentDefinitionExpandedMessage::print(std::ostream& out) const {
    out << "ComplexInstrumentDefinitionExpandedMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", complex_instrument_id=";
    print::text(out, complex_instrument_id_);
    out << ", complex_instrument_underlying=";
    print::text(out, complex_instrument_underlying_);
    out << ", complex_instrument_type=";
    print::text(out, complex_instrument_type_);
    out << ", leg_count=";
    out << static_cast<int>(leg_count_);
    out << ", complex_instrument_leg=";
    print::sequence(out, complex_instrument_leg_);
    out << '}';
}

bool ComplexInstrumentDefinitionExpandedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ComplexInstrumentDefinitionExpandedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexInstrumentDefinitionExpandedMessage::operator==(const ComplexInstrumentDefinitionExpandedMessage& other) const {
    return time_offset_ == other.time_offset_
        && complex_instrument_id_ == other.complex_instrument_id_
        && complex_instrument_underlying_ == other.complex_instrument_underlying_
        && complex_instrument_type_ == other.complex_instrument_type_
        && leg_count_ == other.leg_count_
        && complex_instrument_leg_ == other.complex_instrument_leg_;
}

bool ComplexInstrumentDefinitionExpandedMessage::operator!=(const ComplexInstrumentDefinitionExpandedMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
