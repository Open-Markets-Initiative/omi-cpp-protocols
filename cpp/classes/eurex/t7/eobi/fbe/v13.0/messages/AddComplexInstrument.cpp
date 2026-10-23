#include "AddComplexInstrument.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

AddComplexInstrument::AddComplexInstrument(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, const std::string& security_desc, std::optional<std::int32_t> security_sub_type, std::optional<ProductComplex> product_complex, std::optional<ImpliedMarketIndicator> implied_market_indicator, std::optional<std::uint16_t> quantity_scaling_factor, std::optional<std::uint32_t> leg_ratio_multiplier, std::optional<std::uint8_t> no_legs, const std::array<std::byte, 2>& pad2, std::optional<LastFragment> last_fragment, const std::array<InstrmtLegGrpComp, 20>& instrmt_leg_grp_comp)
  : security_id_(security_id), transact_time_(transact_time), security_desc_(security_desc), security_sub_type_(security_sub_type), product_complex_(product_complex), implied_market_indicator_(implied_market_indicator), quantity_scaling_factor_(quantity_scaling_factor), leg_ratio_multiplier_(leg_ratio_multiplier), no_legs_(no_legs), pad2_(pad2), last_fragment_(last_fragment), instrmt_leg_grp_comp_(instrmt_leg_grp_comp) {}

std::optional<std::int64_t> AddComplexInstrument::security_id() const { return security_id_; }
void AddComplexInstrument::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::chrono::nanoseconds> AddComplexInstrument::transact_time() const { return transact_time_; }
void AddComplexInstrument::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

const std::string& AddComplexInstrument::security_desc() const { return security_desc_; }
std::string& AddComplexInstrument::security_desc() { return security_desc_; }
void AddComplexInstrument::set_security_desc(const std::string& value) { security_desc_ = value; }

std::optional<std::int32_t> AddComplexInstrument::security_sub_type() const { return security_sub_type_; }
void AddComplexInstrument::set_security_sub_type(std::optional<std::int32_t> value) { security_sub_type_ = value; }

std::optional<ProductComplex> AddComplexInstrument::product_complex() const { return product_complex_; }
void AddComplexInstrument::set_product_complex(std::optional<ProductComplex> value) { product_complex_ = value; }

std::optional<ImpliedMarketIndicator> AddComplexInstrument::implied_market_indicator() const { return implied_market_indicator_; }
void AddComplexInstrument::set_implied_market_indicator(std::optional<ImpliedMarketIndicator> value) { implied_market_indicator_ = value; }

std::optional<std::uint16_t> AddComplexInstrument::quantity_scaling_factor() const { return quantity_scaling_factor_; }
void AddComplexInstrument::set_quantity_scaling_factor(std::optional<std::uint16_t> value) { quantity_scaling_factor_ = value; }

std::optional<std::uint32_t> AddComplexInstrument::leg_ratio_multiplier() const { return leg_ratio_multiplier_; }
void AddComplexInstrument::set_leg_ratio_multiplier(std::optional<std::uint32_t> value) { leg_ratio_multiplier_ = value; }

std::optional<std::uint8_t> AddComplexInstrument::no_legs() const { return no_legs_; }
void AddComplexInstrument::set_no_legs(std::optional<std::uint8_t> value) { no_legs_ = value; }

const std::array<std::byte, 2>& AddComplexInstrument::pad2() const { return pad2_; }
std::array<std::byte, 2>& AddComplexInstrument::pad2() { return pad2_; }
void AddComplexInstrument::set_pad2(const std::array<std::byte, 2>& value) { pad2_ = value; }

std::optional<LastFragment> AddComplexInstrument::last_fragment() const { return last_fragment_; }
void AddComplexInstrument::set_last_fragment(std::optional<LastFragment> value) { last_fragment_ = value; }

const std::array<InstrmtLegGrpComp, 20>& AddComplexInstrument::instrmt_leg_grp_comp() const { return instrmt_leg_grp_comp_; }
std::array<InstrmtLegGrpComp, 20>& AddComplexInstrument::instrmt_leg_grp_comp() { return instrmt_leg_grp_comp_; }
void AddComplexInstrument::set_instrmt_leg_grp_comp(const std::array<InstrmtLegGrpComp, 20>& value) { instrmt_leg_grp_comp_ = value; }

MessageCode AddComplexInstrument::type() const { return message_type; }

std::string_view AddComplexInstrument::name() const { return "Add Complex Instrument"; }

std::size_t AddComplexInstrument::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddComplexInstrument", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_desc_ = wire::read_text(data + offset, 40, ' ');
    offset += 40;

    security_sub_type_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    product_complex_ = wire::nullable_enum<ProductComplex>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    implied_market_indicator_ = wire::nullable_enum<ImpliedMarketIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    quantity_scaling_factor_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    leg_ratio_multiplier_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0xFFFFFFFFULL));
    offset += 4;

    no_legs_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    last_fragment_ = wire::nullable_enum<LastFragment>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    for (std::size_t index = 0; index < instrmt_leg_grp_comp_.size(); ++index) {
        offset += instrmt_leg_grp_comp_[index].decode(data + offset, length - offset);
    }

    return offset;
}

std::size_t AddComplexInstrument::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddComplexInstrument", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_text(data + offset, 40, ' ', security_desc_);
    offset += 40;

    wire::write_i32_le(data + offset, security_sub_type_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_u8(data + offset, product_complex_ ? static_cast<std::uint8_t>(*product_complex_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, implied_market_indicator_ ? static_cast<std::uint8_t>(*implied_market_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u16_le(data + offset, quantity_scaling_factor_.value_or(static_cast<std::uint16_t>(0xFFFFULL)));
    offset += 2;

    wire::write_u32_le(data + offset, leg_ratio_multiplier_.value_or(static_cast<std::uint32_t>(0xFFFFFFFFULL)));
    offset += 4;

    wire::write_u8(data + offset, no_legs_.value_or(static_cast<std::uint8_t>(0xFFULL)));
    offset += 1;

    wire::write_bytes(data + offset, pad2_.data(), 2);
    offset += 2;

    wire::write_u8(data + offset, last_fragment_ ? static_cast<std::uint8_t>(*last_fragment_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    for (const auto& entry : instrmt_leg_grp_comp_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t AddComplexInstrument::encoded_size() const {
    return wire_size;
}

void AddComplexInstrument::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddComplexInstrument::clone() const {
    return std::make_unique<AddComplexInstrument>(*this);
}

void AddComplexInstrument::print(std::ostream& out) const {
    out << "AddComplexInstrument{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", security_desc=";
    print::text(out, security_desc_);
    out << ", security_sub_type=";
    print::optional(out, security_sub_type_);
    out << ", product_complex=";
    print::optional(out, product_complex_);
    out << ", implied_market_indicator=";
    print::optional(out, implied_market_indicator_);
    out << ", quantity_scaling_factor=";
    print::optional(out, quantity_scaling_factor_);
    out << ", leg_ratio_multiplier=";
    print::optional(out, leg_ratio_multiplier_);
    out << ", no_legs=";
    print::optional(out, no_legs_);
    out << ", pad2=";
    print::hex(out, pad2_.data(), pad2_.size());
    out << ", last_fragment=";
    print::optional(out, last_fragment_);
    out << ", instrmt_leg_grp_comp=";
    print::sequence(out, instrmt_leg_grp_comp_);
    out << '}';
}

bool AddComplexInstrument::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddComplexInstrument*>(&other);
    return that != nullptr && *this == *that;
}

bool AddComplexInstrument::operator==(const AddComplexInstrument& other) const {
    return security_id_ == other.security_id_
        && transact_time_ == other.transact_time_
        && security_desc_ == other.security_desc_
        && security_sub_type_ == other.security_sub_type_
        && product_complex_ == other.product_complex_
        && implied_market_indicator_ == other.implied_market_indicator_
        && quantity_scaling_factor_ == other.quantity_scaling_factor_
        && leg_ratio_multiplier_ == other.leg_ratio_multiplier_
        && no_legs_ == other.no_legs_
        && pad2_ == other.pad2_
        && last_fragment_ == other.last_fragment_
        && instrmt_leg_grp_comp_ == other.instrmt_leg_grp_comp_;
}

bool AddComplexInstrument::operator!=(const AddComplexInstrument& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v13_0
