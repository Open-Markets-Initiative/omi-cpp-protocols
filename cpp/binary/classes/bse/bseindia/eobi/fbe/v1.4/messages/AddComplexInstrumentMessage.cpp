#include "AddComplexInstrumentMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

AddComplexInstrumentMessage::AddComplexInstrumentMessage(std::int64_t security_id, std::chrono::nanoseconds transact_time, std::optional<std::int32_t> security_sub_type, ProductComplex product_complex, ImpliedMarketIndicator implied_market_indicator, std::uint8_t no_legs, const std::array<std::byte, 1>& pad_1, const std::array<InstrmtLegGrp, 5>& instrmt_leg_grp)
  : security_id_(security_id), transact_time_(transact_time), security_sub_type_(security_sub_type), product_complex_(product_complex), implied_market_indicator_(implied_market_indicator), no_legs_(no_legs), pad_1_(pad_1), instrmt_leg_grp_(instrmt_leg_grp) {}

std::int64_t AddComplexInstrumentMessage::security_id() const { return security_id_; }
void AddComplexInstrumentMessage::set_security_id(std::int64_t value) { security_id_ = value; }

std::chrono::nanoseconds AddComplexInstrumentMessage::transact_time() const { return transact_time_; }
void AddComplexInstrumentMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::optional<std::int32_t> AddComplexInstrumentMessage::security_sub_type() const { return security_sub_type_; }
void AddComplexInstrumentMessage::set_security_sub_type(std::optional<std::int32_t> value) { security_sub_type_ = value; }

ProductComplex AddComplexInstrumentMessage::product_complex() const { return product_complex_; }
void AddComplexInstrumentMessage::set_product_complex(ProductComplex value) { product_complex_ = value; }

ImpliedMarketIndicator AddComplexInstrumentMessage::implied_market_indicator() const { return implied_market_indicator_; }
void AddComplexInstrumentMessage::set_implied_market_indicator(ImpliedMarketIndicator value) { implied_market_indicator_ = value; }

std::uint8_t AddComplexInstrumentMessage::no_legs() const { return no_legs_; }
void AddComplexInstrumentMessage::set_no_legs(std::uint8_t value) { no_legs_ = value; }

const std::array<std::byte, 1>& AddComplexInstrumentMessage::pad_1() const { return pad_1_; }
std::array<std::byte, 1>& AddComplexInstrumentMessage::pad_1() { return pad_1_; }
void AddComplexInstrumentMessage::set_pad_1(const std::array<std::byte, 1>& value) { pad_1_ = value; }

const std::array<InstrmtLegGrp, 5>& AddComplexInstrumentMessage::instrmt_leg_grp() const { return instrmt_leg_grp_; }
std::array<InstrmtLegGrp, 5>& AddComplexInstrumentMessage::instrmt_leg_grp() { return instrmt_leg_grp_; }
void AddComplexInstrumentMessage::set_instrmt_leg_grp(const std::array<InstrmtLegGrp, 5>& value) { instrmt_leg_grp_ = value; }

MessageCode AddComplexInstrumentMessage::type() const { return message_type; }

std::string_view AddComplexInstrumentMessage::name() const { return "Add Complex Instrument Message"; }

std::size_t AddComplexInstrumentMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddComplexInstrumentMessage", wire_size, length);

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    security_sub_type_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(-2147483648LL));
    offset += 4;

    product_complex_ = static_cast<ProductComplex>(wire::read_u8(data + offset));
    offset += 1;

    implied_market_indicator_ = static_cast<ImpliedMarketIndicator>(wire::read_u8(data + offset));
    offset += 1;

    no_legs_ = wire::read_u8(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, pad_1_.data(), 1);
    offset += 1;

    for (std::size_t index = 0; index < instrmt_leg_grp_.size(); ++index) {
        offset += instrmt_leg_grp_[index].decode(data + offset, length - offset);
    }

    return offset;
}

std::size_t AddComplexInstrumentMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddComplexInstrumentMessage", wire_size, capacity);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_i32_le(data + offset, security_sub_type_.value_or(static_cast<std::int32_t>(-2147483648LL)));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(product_complex_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(implied_market_indicator_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(no_legs_));
    offset += 1;

    wire::write_bytes(data + offset, pad_1_.data(), 1);
    offset += 1;

    for (const auto& entry : instrmt_leg_grp_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t AddComplexInstrumentMessage::encoded_size() const {
    return wire_size;
}

void AddComplexInstrumentMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddComplexInstrumentMessage::clone() const {
    return std::make_unique<AddComplexInstrumentMessage>(*this);
}

void AddComplexInstrumentMessage::print(std::ostream& out) const {
    out << "AddComplexInstrumentMessage{";
    out << "security_id=";
    out << security_id_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", security_sub_type=";
    print::optional(out, security_sub_type_);
    out << ", product_complex=";
    out << product_complex_;
    out << ", implied_market_indicator=";
    out << implied_market_indicator_;
    out << ", no_legs=";
    out << static_cast<int>(no_legs_);
    out << ", pad_1=";
    print::hex(out, pad_1_.data(), pad_1_.size());
    out << ", instrmt_leg_grp=";
    print::sequence(out, instrmt_leg_grp_);
    out << '}';
}

bool AddComplexInstrumentMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddComplexInstrumentMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddComplexInstrumentMessage::operator==(const AddComplexInstrumentMessage& other) const {
    return security_id_ == other.security_id_
        && transact_time_ == other.transact_time_
        && security_sub_type_ == other.security_sub_type_
        && product_complex_ == other.product_complex_
        && implied_market_indicator_ == other.implied_market_indicator_
        && no_legs_ == other.no_legs_
        && pad_1_ == other.pad_1_
        && instrmt_leg_grp_ == other.instrmt_leg_grp_;
}

bool AddComplexInstrumentMessage::operator!=(const AddComplexInstrumentMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
