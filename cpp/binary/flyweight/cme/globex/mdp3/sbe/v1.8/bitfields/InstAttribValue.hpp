#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// InstAttribValue bit set
class InstAttribValue {
  public:
    static constexpr const char* name = "InstAttribValue";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstAttribValue(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    std::uint32_t raw() const { return wire::read_u32_le(bytes_.data()); }

    bool electronic_match_eligible() const { return (raw() & static_cast<std::uint32_t>(0x1)) != 0; }

    bool order_cross_eligible() const { return (raw() & static_cast<std::uint32_t>(0x2)) != 0; }

    bool block_trade_eligible() const { return (raw() & static_cast<std::uint32_t>(0x4)) != 0; }

    bool efp_eligible() const { return (raw() & static_cast<std::uint32_t>(0x8)) != 0; }

    bool ebf_eligible() const { return (raw() & static_cast<std::uint32_t>(0x10)) != 0; }

    bool efs_eligible() const { return (raw() & static_cast<std::uint32_t>(0x20)) != 0; }

    bool efr_eligible() const { return (raw() & static_cast<std::uint32_t>(0x40)) != 0; }

    bool otc_eligible() const { return (raw() & static_cast<std::uint32_t>(0x80)) != 0; }

    bool ilink_indicative_mass_quoting_eligible() const { return (raw() & static_cast<std::uint32_t>(0x100)) != 0; }

    bool negative_strike_eligible() const { return (raw() & static_cast<std::uint32_t>(0x200)) != 0; }

    bool negative_price_outright_eligible() const { return (raw() & static_cast<std::uint32_t>(0x400)) != 0; }

    bool is_fractional() const { return (raw() & static_cast<std::uint32_t>(0x800)) != 0; }

    bool volatility_quoted_option() const { return (raw() & static_cast<std::uint32_t>(0x1000)) != 0; }

    bool rfq_cross_eligible() const { return (raw() & static_cast<std::uint32_t>(0x2000)) != 0; }

    bool zero_price_outright_eligible() const { return (raw() & static_cast<std::uint32_t>(0x4000)) != 0; }

    bool decaying_product_eligibility() const { return (raw() & static_cast<std::uint32_t>(0x8000)) != 0; }

    bool variable_product_eligibility() const { return (raw() & static_cast<std::uint32_t>(0x10000)) != 0; }

    bool daily_product_eligibility() const { return (raw() & static_cast<std::uint32_t>(0x20000)) != 0; }

    bool gt_orders_eligibility() const { return (raw() & static_cast<std::uint32_t>(0x40000)) != 0; }

    bool implied_matching_eligibility() const { return (raw() & static_cast<std::uint32_t>(0x80000)) != 0; }

    std::uint16_t reserved_12() const { return static_cast<std::uint16_t>((raw() & static_cast<std::uint32_t>(0xFFF00000)) >> 20); }

    void print(std::ostream& out) const {
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
        out << ", reserved_12=";
        out << static_cast<unsigned long long>(reserved_12());
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstAttribValue& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
