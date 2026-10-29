#include "ComplexStrategyDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

ComplexStrategyDirectoryMessage::ComplexStrategyDirectoryMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, StrategyType strategy_type, std::uint8_t source, const std::string& underlying_symbol, std::uint8_t number_of_legs, const std::vector<LegInformation>& leg_information)
  : timestamp_(timestamp), strategy_id_(strategy_id), strategy_type_(strategy_type), source_(source), underlying_symbol_(underlying_symbol), number_of_legs_(number_of_legs), leg_information_(leg_information) {}

std::chrono::nanoseconds ComplexStrategyDirectoryMessage::timestamp() const { return timestamp_; }
void ComplexStrategyDirectoryMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t ComplexStrategyDirectoryMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t ComplexStrategyDirectoryMessage::strategy_id() const { return strategy_id_; }
void ComplexStrategyDirectoryMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

StrategyType ComplexStrategyDirectoryMessage::strategy_type() const { return strategy_type_; }
void ComplexStrategyDirectoryMessage::set_strategy_type(StrategyType value) { strategy_type_ = value; }

std::uint8_t ComplexStrategyDirectoryMessage::source() const { return source_; }
void ComplexStrategyDirectoryMessage::set_source(std::uint8_t value) { source_ = value; }

const std::string& ComplexStrategyDirectoryMessage::underlying_symbol() const { return underlying_symbol_; }
std::string& ComplexStrategyDirectoryMessage::underlying_symbol() { return underlying_symbol_; }
void ComplexStrategyDirectoryMessage::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

std::uint8_t ComplexStrategyDirectoryMessage::number_of_legs() const { return number_of_legs_; }
void ComplexStrategyDirectoryMessage::set_number_of_legs(std::uint8_t value) { number_of_legs_ = value; }

const std::vector<LegInformation>& ComplexStrategyDirectoryMessage::leg_information() const { return leg_information_; }
std::vector<LegInformation>& ComplexStrategyDirectoryMessage::leg_information() { return leg_information_; }
void ComplexStrategyDirectoryMessage::set_leg_information(const std::vector<LegInformation>& value) { leg_information_ = value; }

MessageCode ComplexStrategyDirectoryMessage::type() const { return message_type; }

std::string_view ComplexStrategyDirectoryMessage::name() const { return "Complex Strategy Directory Message"; }

std::size_t ComplexStrategyDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ComplexStrategyDirectoryMessage", offset + 6, length);
    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    wire::require("ComplexStrategyDirectoryMessage", offset + 4, length);
    strategy_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("ComplexStrategyDirectoryMessage", offset + 1, length);
    strategy_type_ = static_cast<StrategyType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexStrategyDirectoryMessage", offset + 1, length);
    source_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ComplexStrategyDirectoryMessage", offset + 13, length);
    underlying_symbol_ = wire::read_text(data + offset, 13, ' ');
    offset += 13;

    wire::require("ComplexStrategyDirectoryMessage", offset + 1, length);
    number_of_legs_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(number_of_legs_);
        leg_information_.clear();
        leg_information_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            LegInformation entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            leg_information_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t ComplexStrategyDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexStrategyDirectoryMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto number_of_legs = number_of_legs_;
    number_of_legs = static_cast<std::uint8_t>(leg_information_.size());

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(strategy_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(source_));
    offset += 1;

    wire::write_text(data + offset, 13, ' ', underlying_symbol_);
    offset += 13;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_legs));
    offset += 1;

    for (const auto& entry : leg_information_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t ComplexStrategyDirectoryMessage::encoded_size() const {
    return 6 + 4 + 1 + 1 + 13 + 1 + wire::encoded_size_of(leg_information_);
}

void ComplexStrategyDirectoryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ComplexStrategyDirectoryMessage::clone() const {
    return std::make_unique<ComplexStrategyDirectoryMessage>(*this);
}

void ComplexStrategyDirectoryMessage::print(std::ostream& out) const {
    out << "ComplexStrategyDirectoryMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", strategy_type=";
    out << strategy_type_;
    out << ", source=";
    out << static_cast<int>(source_);
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", number_of_legs=";
    out << static_cast<int>(number_of_legs_);
    out << ", leg_information=";
    print::sequence(out, leg_information_);
    out << '}';
}

bool ComplexStrategyDirectoryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ComplexStrategyDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexStrategyDirectoryMessage::operator==(const ComplexStrategyDirectoryMessage& other) const {
    return timestamp_ == other.timestamp_
        && strategy_id_ == other.strategy_id_
        && strategy_type_ == other.strategy_type_
        && source_ == other.source_
        && underlying_symbol_ == other.underlying_symbol_
        && number_of_legs_ == other.number_of_legs_
        && leg_information_ == other.leg_information_;
}

bool ComplexStrategyDirectoryMessage::operator!=(const ComplexStrategyDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
