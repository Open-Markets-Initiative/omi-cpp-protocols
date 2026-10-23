#include "InstAttribValue.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

InstAttribValue::InstAttribValue(std::uint32_t raw) : raw_(raw) {}

bool InstAttribValue::electronic_match_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x1)) != 0; }
void InstAttribValue::set_electronic_match_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x1)) : (raw_ & ~static_cast<std::uint32_t>(0x1))); }

bool InstAttribValue::order_cross_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x2)) != 0; }
void InstAttribValue::set_order_cross_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x2)) : (raw_ & ~static_cast<std::uint32_t>(0x2))); }

bool InstAttribValue::block_trade_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x4)) != 0; }
void InstAttribValue::set_block_trade_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x4)) : (raw_ & ~static_cast<std::uint32_t>(0x4))); }

bool InstAttribValue::efp_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x8)) != 0; }
void InstAttribValue::set_efp_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x8)) : (raw_ & ~static_cast<std::uint32_t>(0x8))); }

bool InstAttribValue::ebf_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x10)) != 0; }
void InstAttribValue::set_ebf_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x10)) : (raw_ & ~static_cast<std::uint32_t>(0x10))); }

bool InstAttribValue::efs_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x20)) != 0; }
void InstAttribValue::set_efs_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x20)) : (raw_ & ~static_cast<std::uint32_t>(0x20))); }

bool InstAttribValue::efr_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x40)) != 0; }
void InstAttribValue::set_efr_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x40)) : (raw_ & ~static_cast<std::uint32_t>(0x40))); }

bool InstAttribValue::otc_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x80)) != 0; }
void InstAttribValue::set_otc_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x80)) : (raw_ & ~static_cast<std::uint32_t>(0x80))); }

bool InstAttribValue::ilink_indicative_mass_quoting_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x100)) != 0; }
void InstAttribValue::set_ilink_indicative_mass_quoting_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x100)) : (raw_ & ~static_cast<std::uint32_t>(0x100))); }

bool InstAttribValue::negative_strike_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x200)) != 0; }
void InstAttribValue::set_negative_strike_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x200)) : (raw_ & ~static_cast<std::uint32_t>(0x200))); }

bool InstAttribValue::negative_price_outright_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x400)) != 0; }
void InstAttribValue::set_negative_price_outright_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x400)) : (raw_ & ~static_cast<std::uint32_t>(0x400))); }

bool InstAttribValue::is_fractional() const { return (raw_ & static_cast<std::uint32_t>(0x800)) != 0; }
void InstAttribValue::set_is_fractional(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x800)) : (raw_ & ~static_cast<std::uint32_t>(0x800))); }

bool InstAttribValue::volatility_quoted_option() const { return (raw_ & static_cast<std::uint32_t>(0x1000)) != 0; }
void InstAttribValue::set_volatility_quoted_option(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x1000)) : (raw_ & ~static_cast<std::uint32_t>(0x1000))); }

bool InstAttribValue::rfq_cross_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x2000)) != 0; }
void InstAttribValue::set_rfq_cross_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x2000)) : (raw_ & ~static_cast<std::uint32_t>(0x2000))); }

bool InstAttribValue::zero_price_outright_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x4000)) != 0; }
void InstAttribValue::set_zero_price_outright_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x4000)) : (raw_ & ~static_cast<std::uint32_t>(0x4000))); }

bool InstAttribValue::decaying_product_eligibility() const { return (raw_ & static_cast<std::uint32_t>(0x8000)) != 0; }
void InstAttribValue::set_decaying_product_eligibility(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x8000)) : (raw_ & ~static_cast<std::uint32_t>(0x8000))); }

bool InstAttribValue::variable_product_eligibility() const { return (raw_ & static_cast<std::uint32_t>(0x10000)) != 0; }
void InstAttribValue::set_variable_product_eligibility(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x10000)) : (raw_ & ~static_cast<std::uint32_t>(0x10000))); }

bool InstAttribValue::daily_product_eligibility() const { return (raw_ & static_cast<std::uint32_t>(0x20000)) != 0; }
void InstAttribValue::set_daily_product_eligibility(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x20000)) : (raw_ & ~static_cast<std::uint32_t>(0x20000))); }

bool InstAttribValue::gt_orders_eligibility() const { return (raw_ & static_cast<std::uint32_t>(0x40000)) != 0; }
void InstAttribValue::set_gt_orders_eligibility(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x40000)) : (raw_ & ~static_cast<std::uint32_t>(0x40000))); }

bool InstAttribValue::implied_matching_eligibility() const { return (raw_ & static_cast<std::uint32_t>(0x80000)) != 0; }
void InstAttribValue::set_implied_matching_eligibility(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x80000)) : (raw_ & ~static_cast<std::uint32_t>(0x80000))); }

bool InstAttribValue::triangulation_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x100000)) != 0; }
void InstAttribValue::set_triangulation_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x100000)) : (raw_ & ~static_cast<std::uint32_t>(0x100000))); }

bool InstAttribValue::variable_cab_eligible() const { return (raw_ & static_cast<std::uint32_t>(0x200000)) != 0; }
void InstAttribValue::set_variable_cab_eligible(bool value) { raw_ = static_cast<std::uint32_t>(value ? (raw_ | static_cast<std::uint32_t>(0x200000)) : (raw_ & ~static_cast<std::uint32_t>(0x200000))); }

std::uint16_t InstAttribValue::reserved_10() const { return static_cast<std::uint16_t>((raw_ & static_cast<std::uint32_t>(0xFFC00000)) >> 22); }
void InstAttribValue::set_reserved_10(std::uint16_t value) { raw_ = static_cast<std::uint32_t>((raw_ & ~static_cast<std::uint32_t>(0xFFC00000)) | ((static_cast<std::uint32_t>(value) << 22) & static_cast<std::uint32_t>(0xFFC00000))); }

std::uint32_t InstAttribValue::raw() const { return raw_; }
void InstAttribValue::set_raw(std::uint32_t value) { raw_ = value; }

std::size_t InstAttribValue::decode(const std::byte* data, std::size_t length) {
    wire::require("InstAttribValue", wire_size, length);
    raw_ = wire::read_u32_le(data);
    return wire_size;
}

std::size_t InstAttribValue::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("InstAttribValue", wire_size, capacity);
    wire::write_u32_le(data, raw_);
    return wire_size;
}

std::size_t InstAttribValue::encoded_size() const {
    return wire_size;
}

void InstAttribValue::print(std::ostream& out) const {
    out << "InstAttribValue{";
    out << "electronic_match_eligible=";
    out << (electronic_match_eligible() ? "true" : "false");
    out << ", order_cross_eligible=";
    out << (order_cross_eligible() ? "true" : "false");
    out << ", block_trade_eligible=";
    out << (block_trade_eligible() ? "true" : "false");
    out << ", efp_eligible=";
    out << (efp_eligible() ? "true" : "false");
    out << ", ebf_eligible=";
    out << (ebf_eligible() ? "true" : "false");
    out << ", efs_eligible=";
    out << (efs_eligible() ? "true" : "false");
    out << ", efr_eligible=";
    out << (efr_eligible() ? "true" : "false");
    out << ", otc_eligible=";
    out << (otc_eligible() ? "true" : "false");
    out << ", ilink_indicative_mass_quoting_eligible=";
    out << (ilink_indicative_mass_quoting_eligible() ? "true" : "false");
    out << ", negative_strike_eligible=";
    out << (negative_strike_eligible() ? "true" : "false");
    out << ", negative_price_outright_eligible=";
    out << (negative_price_outright_eligible() ? "true" : "false");
    out << ", is_fractional=";
    out << (is_fractional() ? "true" : "false");
    out << ", volatility_quoted_option=";
    out << (volatility_quoted_option() ? "true" : "false");
    out << ", rfq_cross_eligible=";
    out << (rfq_cross_eligible() ? "true" : "false");
    out << ", zero_price_outright_eligible=";
    out << (zero_price_outright_eligible() ? "true" : "false");
    out << ", decaying_product_eligibility=";
    out << (decaying_product_eligibility() ? "true" : "false");
    out << ", variable_product_eligibility=";
    out << (variable_product_eligibility() ? "true" : "false");
    out << ", daily_product_eligibility=";
    out << (daily_product_eligibility() ? "true" : "false");
    out << ", gt_orders_eligibility=";
    out << (gt_orders_eligibility() ? "true" : "false");
    out << ", implied_matching_eligibility=";
    out << (implied_matching_eligibility() ? "true" : "false");
    out << ", triangulation_eligible=";
    out << (triangulation_eligible() ? "true" : "false");
    out << ", variable_cab_eligible=";
    out << (variable_cab_eligible() ? "true" : "false");
    out << ", reserved_10=";
    out << static_cast<unsigned long long>(reserved_10());
    out << '}';
}

bool InstAttribValue::operator==(const InstAttribValue& other) const {
    return raw_ == other.raw_;
}

bool InstAttribValue::operator!=(const InstAttribValue& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const InstAttribValue& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
