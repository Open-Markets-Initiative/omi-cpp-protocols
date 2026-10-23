#include "AddFlexibleInstrument.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

AddFlexibleInstrument::AddFlexibleInstrument(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, const std::string& security_desc, std::optional<SecurityType> security_type, std::optional<PutOrCall> put_or_call, std::optional<ExerciseStyle> exercise_style, std::optional<SettlMethod> settl_method, std::optional<std::uint32_t> maturity_date, std::optional<Decimal> strike_price, std::optional<std::uint32_t> opt_attribute, std::optional<std::uint32_t> contract_date, std::optional<std::uint32_t> security_reference_data_supplement, const std::array<std::byte, 4>& pad4)
  : security_id_(security_id), transact_time_(transact_time), security_desc_(security_desc), security_type_(security_type), put_or_call_(put_or_call), exercise_style_(exercise_style), settl_method_(settl_method), maturity_date_(maturity_date), strike_price_(strike_price), opt_attribute_(opt_attribute), contract_date_(contract_date), security_reference_data_supplement_(security_reference_data_supplement), pad4_(pad4) {}

std::optional<std::int64_t> AddFlexibleInstrument::security_id() const { return security_id_; }
void AddFlexibleInstrument::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::chrono::nanoseconds> AddFlexibleInstrument::transact_time() const { return transact_time_; }
void AddFlexibleInstrument::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

const std::string& AddFlexibleInstrument::security_desc() const { return security_desc_; }
std::string& AddFlexibleInstrument::security_desc() { return security_desc_; }
void AddFlexibleInstrument::set_security_desc(const std::string& value) { security_desc_ = value; }

std::optional<SecurityType> AddFlexibleInstrument::security_type() const { return security_type_; }
void AddFlexibleInstrument::set_security_type(std::optional<SecurityType> value) { security_type_ = value; }

std::optional<PutOrCall> AddFlexibleInstrument::put_or_call() const { return put_or_call_; }
void AddFlexibleInstrument::set_put_or_call(std::optional<PutOrCall> value) { put_or_call_ = value; }

std::optional<ExerciseStyle> AddFlexibleInstrument::exercise_style() const { return exercise_style_; }
void AddFlexibleInstrument::set_exercise_style(std::optional<ExerciseStyle> value) { exercise_style_ = value; }

std::optional<SettlMethod> AddFlexibleInstrument::settl_method() const { return settl_method_; }
void AddFlexibleInstrument::set_settl_method(std::optional<SettlMethod> value) { settl_method_ = value; }

std::optional<std::uint32_t> AddFlexibleInstrument::maturity_date() const { return maturity_date_; }
void AddFlexibleInstrument::set_maturity_date(std::optional<std::uint32_t> value) { maturity_date_ = value; }

std::optional<Decimal> AddFlexibleInstrument::strike_price() const { return strike_price_; }
void AddFlexibleInstrument::set_strike_price(std::optional<Decimal> value) { strike_price_ = value; }

std::optional<std::uint32_t> AddFlexibleInstrument::opt_attribute() const { return opt_attribute_; }
void AddFlexibleInstrument::set_opt_attribute(std::optional<std::uint32_t> value) { opt_attribute_ = value; }

std::optional<std::uint32_t> AddFlexibleInstrument::contract_date() const { return contract_date_; }
void AddFlexibleInstrument::set_contract_date(std::optional<std::uint32_t> value) { contract_date_ = value; }

std::optional<std::uint32_t> AddFlexibleInstrument::security_reference_data_supplement() const { return security_reference_data_supplement_; }
void AddFlexibleInstrument::set_security_reference_data_supplement(std::optional<std::uint32_t> value) { security_reference_data_supplement_ = value; }

const std::array<std::byte, 4>& AddFlexibleInstrument::pad4() const { return pad4_; }
std::array<std::byte, 4>& AddFlexibleInstrument::pad4() { return pad4_; }
void AddFlexibleInstrument::set_pad4(const std::array<std::byte, 4>& value) { pad4_ = value; }

MessageCode AddFlexibleInstrument::type() const { return message_type; }

std::string_view AddFlexibleInstrument::name() const { return "Add Flexible Instrument"; }

std::size_t AddFlexibleInstrument::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddFlexibleInstrument", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_desc_ = wire::read_text(data + offset, 40, ' ');
    offset += 40;

    security_type_ = wire::nullable_enum<SecurityType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    put_or_call_ = wire::nullable_enum<PutOrCall>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    exercise_style_ = wire::nullable_enum<ExerciseStyle>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    settl_method_ = wire::nullable_enum<SettlMethod>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    maturity_date_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    strike_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    opt_attribute_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    contract_date_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    security_reference_data_supplement_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    wire::read_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t AddFlexibleInstrument::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddFlexibleInstrument", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_text(data + offset, 40, ' ', security_desc_);
    offset += 40;

    wire::write_u8(data + offset, security_type_ ? static_cast<std::uint8_t>(*security_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, put_or_call_ ? static_cast<std::uint8_t>(*put_or_call_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, exercise_style_ ? static_cast<std::uint8_t>(*exercise_style_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, settl_method_ ? static_cast<std::uint8_t>(*settl_method_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u32_le(data + offset, maturity_date_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_i64_le(data + offset, strike_price_ ? static_cast<std::int64_t>(strike_price_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u32_le(data + offset, opt_attribute_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_u32_le(data + offset, contract_date_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_u32_le(data + offset, security_reference_data_supplement_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t AddFlexibleInstrument::encoded_size() const {
    return wire_size;
}

void AddFlexibleInstrument::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddFlexibleInstrument::clone() const {
    return std::make_unique<AddFlexibleInstrument>(*this);
}

void AddFlexibleInstrument::print(std::ostream& out) const {
    out << "AddFlexibleInstrument{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", security_desc=";
    print::text(out, security_desc_);
    out << ", security_type=";
    print::optional(out, security_type_);
    out << ", put_or_call=";
    print::optional(out, put_or_call_);
    out << ", exercise_style=";
    print::optional(out, exercise_style_);
    out << ", settl_method=";
    print::optional(out, settl_method_);
    out << ", maturity_date=";
    print::optional(out, maturity_date_);
    out << ", strike_price=";
    print::optional(out, strike_price_);
    out << ", opt_attribute=";
    print::optional(out, opt_attribute_);
    out << ", contract_date=";
    print::optional(out, contract_date_);
    out << ", security_reference_data_supplement=";
    print::optional(out, security_reference_data_supplement_);
    out << ", pad4=";
    print::hex(out, pad4_.data(), pad4_.size());
    out << '}';
}

bool AddFlexibleInstrument::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddFlexibleInstrument*>(&other);
    return that != nullptr && *this == *that;
}

bool AddFlexibleInstrument::operator==(const AddFlexibleInstrument& other) const {
    return security_id_ == other.security_id_
        && transact_time_ == other.transact_time_
        && security_desc_ == other.security_desc_
        && security_type_ == other.security_type_
        && put_or_call_ == other.put_or_call_
        && exercise_style_ == other.exercise_style_
        && settl_method_ == other.settl_method_
        && maturity_date_ == other.maturity_date_
        && strike_price_ == other.strike_price_
        && opt_attribute_ == other.opt_attribute_
        && contract_date_ == other.contract_date_
        && security_reference_data_supplement_ == other.security_reference_data_supplement_
        && pad4_ == other.pad4_;
}

bool AddFlexibleInstrument::operator!=(const AddFlexibleInstrument& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v13_0
