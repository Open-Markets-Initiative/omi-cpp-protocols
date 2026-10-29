#include "ComplexStrategyDefinitionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

ComplexStrategyDefinitionMessage::ComplexStrategyDefinitionMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, const std::string& underlying_symbol, ActiveOnMiax active_on_miax, const std::array<std::byte, 1>& reserved_1, UpdateReason update_reason, const std::array<std::byte, 10>& reserved_10, std::uint8_t number_of_legs, const std::vector<LegDefinition>& leg_definition)
  : nanoseconds_(nanoseconds), strategy_id_(strategy_id), underlying_symbol_(underlying_symbol), active_on_miax_(active_on_miax), reserved_1_(reserved_1), update_reason_(update_reason), reserved_10_(reserved_10), number_of_legs_(number_of_legs), leg_definition_(leg_definition) {}

std::chrono::nanoseconds ComplexStrategyDefinitionMessage::nanoseconds() const { return nanoseconds_; }
void ComplexStrategyDefinitionMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t ComplexStrategyDefinitionMessage::strategy_id() const { return strategy_id_; }
void ComplexStrategyDefinitionMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

const std::string& ComplexStrategyDefinitionMessage::underlying_symbol() const { return underlying_symbol_; }
std::string& ComplexStrategyDefinitionMessage::underlying_symbol() { return underlying_symbol_; }
void ComplexStrategyDefinitionMessage::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

ActiveOnMiax ComplexStrategyDefinitionMessage::active_on_miax() const { return active_on_miax_; }
void ComplexStrategyDefinitionMessage::set_active_on_miax(ActiveOnMiax value) { active_on_miax_ = value; }

const std::array<std::byte, 1>& ComplexStrategyDefinitionMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& ComplexStrategyDefinitionMessage::reserved_1() { return reserved_1_; }
void ComplexStrategyDefinitionMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

UpdateReason ComplexStrategyDefinitionMessage::update_reason() const { return update_reason_; }
void ComplexStrategyDefinitionMessage::set_update_reason(UpdateReason value) { update_reason_ = value; }

const std::array<std::byte, 10>& ComplexStrategyDefinitionMessage::reserved_10() const { return reserved_10_; }
std::array<std::byte, 10>& ComplexStrategyDefinitionMessage::reserved_10() { return reserved_10_; }
void ComplexStrategyDefinitionMessage::set_reserved_10(const std::array<std::byte, 10>& value) { reserved_10_ = value; }

std::uint8_t ComplexStrategyDefinitionMessage::number_of_legs() const { return number_of_legs_; }
void ComplexStrategyDefinitionMessage::set_number_of_legs(std::uint8_t value) { number_of_legs_ = value; }

const std::vector<LegDefinition>& ComplexStrategyDefinitionMessage::leg_definition() const { return leg_definition_; }
std::vector<LegDefinition>& ComplexStrategyDefinitionMessage::leg_definition() { return leg_definition_; }
void ComplexStrategyDefinitionMessage::set_leg_definition(const std::vector<LegDefinition>& value) { leg_definition_ = value; }

DataCode ComplexStrategyDefinitionMessage::type() const { return message_type; }

std::string_view ComplexStrategyDefinitionMessage::name() const { return "Complex Strategy Definition Message"; }

std::size_t ComplexStrategyDefinitionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ComplexStrategyDefinitionMessage", offset + 4, length);
    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    wire::require("ComplexStrategyDefinitionMessage", offset + 4, length);
    strategy_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ComplexStrategyDefinitionMessage", offset + 11, length);
    underlying_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    wire::require("ComplexStrategyDefinitionMessage", offset + 1, length);
    active_on_miax_ = static_cast<ActiveOnMiax>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexStrategyDefinitionMessage", offset + 1, length);
    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::require("ComplexStrategyDefinitionMessage", offset + 1, length);
    update_reason_ = static_cast<UpdateReason>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ComplexStrategyDefinitionMessage", offset + 10, length);
    wire::read_bytes(data + offset, reserved_10_.data(), 10);
    offset += 10;

    wire::require("ComplexStrategyDefinitionMessage", offset + 1, length);
    number_of_legs_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(number_of_legs_);
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

std::size_t ComplexStrategyDefinitionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexStrategyDefinitionMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto number_of_legs = number_of_legs_;
    number_of_legs = static_cast<std::uint8_t>(leg_definition_.size());

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_text(data + offset, 11, ' ', underlying_symbol_);
    offset += 11;

    wire::write_char(data + offset, static_cast<char>(active_on_miax_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(update_reason_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_10_.data(), 10);
    offset += 10;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_legs));
    offset += 1;

    for (const auto& entry : leg_definition_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t ComplexStrategyDefinitionMessage::encoded_size() const {
    return 4 + 4 + 11 + 1 + 1 + 1 + 10 + 1 + wire::encoded_size_of(leg_definition_);
}

void ComplexStrategyDefinitionMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> ComplexStrategyDefinitionMessage::clone() const {
    return std::make_unique<ComplexStrategyDefinitionMessage>(*this);
}

void ComplexStrategyDefinitionMessage::print(std::ostream& out) const {
    out << "ComplexStrategyDefinitionMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", active_on_miax=";
    out << active_on_miax_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", update_reason=";
    out << update_reason_;
    out << ", reserved_10=";
    print::hex(out, reserved_10_.data(), reserved_10_.size());
    out << ", number_of_legs=";
    out << static_cast<int>(number_of_legs_);
    out << ", leg_definition=";
    print::sequence(out, leg_definition_);
    out << '}';
}

bool ComplexStrategyDefinitionMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const ComplexStrategyDefinitionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexStrategyDefinitionMessage::operator==(const ComplexStrategyDefinitionMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && strategy_id_ == other.strategy_id_
        && underlying_symbol_ == other.underlying_symbol_
        && active_on_miax_ == other.active_on_miax_
        && reserved_1_ == other.reserved_1_
        && update_reason_ == other.update_reason_
        && reserved_10_ == other.reserved_10_
        && number_of_legs_ == other.number_of_legs_
        && leg_definition_ == other.leg_definition_;
}

bool ComplexStrategyDefinitionMessage::operator!=(const ComplexStrategyDefinitionMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
