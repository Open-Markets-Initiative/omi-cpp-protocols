#include "AddScaledSimpleInstrument.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

AddScaledSimpleInstrument::AddScaledSimpleInstrument(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, const std::string& security_desc, std::optional<SecurityType> security_type, const std::array<std::byte, 1>& pad1, std::optional<std::uint16_t> quantity_scaling_factor, const std::array<std::byte, 4>& pad4, const RelatedInstrumentGrpComp& related_instrument_grp_comp)
  : security_id_(security_id), transact_time_(transact_time), security_desc_(security_desc), security_type_(security_type), pad1_(pad1), quantity_scaling_factor_(quantity_scaling_factor), pad4_(pad4), related_instrument_grp_comp_(related_instrument_grp_comp) {}

std::optional<std::int64_t> AddScaledSimpleInstrument::security_id() const { return security_id_; }
void AddScaledSimpleInstrument::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::chrono::nanoseconds> AddScaledSimpleInstrument::transact_time() const { return transact_time_; }
void AddScaledSimpleInstrument::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

const std::string& AddScaledSimpleInstrument::security_desc() const { return security_desc_; }
std::string& AddScaledSimpleInstrument::security_desc() { return security_desc_; }
void AddScaledSimpleInstrument::set_security_desc(const std::string& value) { security_desc_ = value; }

std::optional<SecurityType> AddScaledSimpleInstrument::security_type() const { return security_type_; }
void AddScaledSimpleInstrument::set_security_type(std::optional<SecurityType> value) { security_type_ = value; }

const std::array<std::byte, 1>& AddScaledSimpleInstrument::pad1() const { return pad1_; }
std::array<std::byte, 1>& AddScaledSimpleInstrument::pad1() { return pad1_; }
void AddScaledSimpleInstrument::set_pad1(const std::array<std::byte, 1>& value) { pad1_ = value; }

std::optional<std::uint16_t> AddScaledSimpleInstrument::quantity_scaling_factor() const { return quantity_scaling_factor_; }
void AddScaledSimpleInstrument::set_quantity_scaling_factor(std::optional<std::uint16_t> value) { quantity_scaling_factor_ = value; }

const std::array<std::byte, 4>& AddScaledSimpleInstrument::pad4() const { return pad4_; }
std::array<std::byte, 4>& AddScaledSimpleInstrument::pad4() { return pad4_; }
void AddScaledSimpleInstrument::set_pad4(const std::array<std::byte, 4>& value) { pad4_ = value; }

const RelatedInstrumentGrpComp& AddScaledSimpleInstrument::related_instrument_grp_comp() const { return related_instrument_grp_comp_; }
RelatedInstrumentGrpComp& AddScaledSimpleInstrument::related_instrument_grp_comp() { return related_instrument_grp_comp_; }
void AddScaledSimpleInstrument::set_related_instrument_grp_comp(const RelatedInstrumentGrpComp& value) { related_instrument_grp_comp_ = value; }

MessageCode AddScaledSimpleInstrument::type() const { return message_type; }

std::string_view AddScaledSimpleInstrument::name() const { return "Add Scaled Simple Instrument"; }

std::size_t AddScaledSimpleInstrument::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddScaledSimpleInstrument", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_desc_ = wire::read_text(data + offset, 40, ' ');
    offset += 40;

    security_type_ = wire::nullable_enum<SecurityType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad1_.data(), 1);
    offset += 1;

    quantity_scaling_factor_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    wire::read_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    offset += related_instrument_grp_comp_.decode(data + offset, length - offset);

    return offset;
}

std::size_t AddScaledSimpleInstrument::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddScaledSimpleInstrument", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_text(data + offset, 40, ' ', security_desc_);
    offset += 40;

    wire::write_u8(data + offset, security_type_ ? static_cast<std::uint8_t>(*security_type_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad1_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, quantity_scaling_factor_.value_or(static_cast<std::uint16_t>(0xFFFFULL)));
    offset += 2;

    wire::write_bytes(data + offset, pad4_.data(), 4);
    offset += 4;

    offset += related_instrument_grp_comp_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t AddScaledSimpleInstrument::encoded_size() const {
    return wire_size;
}

void AddScaledSimpleInstrument::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddScaledSimpleInstrument::clone() const {
    return std::make_unique<AddScaledSimpleInstrument>(*this);
}

void AddScaledSimpleInstrument::print(std::ostream& out) const {
    out << "AddScaledSimpleInstrument{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", security_desc=";
    print::text(out, security_desc_);
    out << ", security_type=";
    print::optional(out, security_type_);
    out << ", pad1=";
    print::hex(out, pad1_.data(), pad1_.size());
    out << ", quantity_scaling_factor=";
    print::optional(out, quantity_scaling_factor_);
    out << ", pad4=";
    print::hex(out, pad4_.data(), pad4_.size());
    out << ", related_instrument_grp_comp=";
    related_instrument_grp_comp_.print(out);
    out << '}';
}

bool AddScaledSimpleInstrument::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddScaledSimpleInstrument*>(&other);
    return that != nullptr && *this == *that;
}

bool AddScaledSimpleInstrument::operator==(const AddScaledSimpleInstrument& other) const {
    return security_id_ == other.security_id_
        && transact_time_ == other.transact_time_
        && security_desc_ == other.security_desc_
        && security_type_ == other.security_type_
        && pad1_ == other.pad1_
        && quantity_scaling_factor_ == other.quantity_scaling_factor_
        && pad4_ == other.pad4_
        && related_instrument_grp_comp_ == other.related_instrument_grp_comp_;
}

bool AddScaledSimpleInstrument::operator!=(const AddScaledSimpleInstrument& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v15_0
