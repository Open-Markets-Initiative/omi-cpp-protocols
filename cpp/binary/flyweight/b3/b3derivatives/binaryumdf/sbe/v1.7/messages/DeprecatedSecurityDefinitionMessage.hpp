#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityIdSource.hpp"
#include "../enums/SecurityUpdateAction.hpp"
#include "../enums/SecurityType.hpp"
#include "../common/Decimal.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../structs/ContractSettlMonth.hpp"
#include "../enums/LotType.hpp"
#include "../enums/Product.hpp"
#include "../enums/ExerciseStyle.hpp"
#include "../enums/PutOrCall.hpp"
#include "../enums/PriceType.hpp"
#include "../enums/GovernanceIndicator.hpp"
#include "../enums/SecurityMatchType.hpp"
#include "../enums/LastFragment.hpp"
#include "../enums/MultiLegModel.hpp"
#include "../enums/MultiLegPriceMethod.hpp"
#include "../structs/DeprecatedUnderlyingsGroups.hpp"
#include "../structs/DeprecatedLegsGroups.hpp"
#include "../structs/DeprecatedInstrAttribsGroups.hpp"
#include "../structs/SecurityDesc.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// SecurityDefinition_4Message
class DeprecatedSecurityDefinitionMessage {
  public:
    static constexpr const char* name = "DeprecatedSecurityDefinitionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit DeprecatedSecurityDefinitionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every DeprecatedSecurityDefinitionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 230;
    std::size_t encoded_size() const { return security_desc_end(); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    std::string_view security_exchange() const { return view::text(at(8), 4, '\0'); }

    SecurityIdSource security_id_source() const { return static_cast<SecurityIdSource>(wire::read_char(at(12))); }

    std::string_view security_group() const { return view::text(at(13), 3, '\0'); }

    std::string_view symbol() const { return view::text(at(16), 20, '\0'); }

    SecurityUpdateAction security_update_action() const { return static_cast<SecurityUpdateAction>(wire::read_char(at(36))); }

    SecurityType security_type() const { return static_cast<SecurityType>(wire::read_u8(at(37))); }

    std::uint16_t security_sub_type() const { return wire::read_u16_le(at(38)); }

    std::uint32_t tot_no_related_sym() const { return wire::read_u32_le(at(40)); }

    std::optional<Decimal> min_price_increment_legacy() const { return wire::nullable_decimal(wire::read_i64_le(at(44)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<Decimal> strike_price() const { return wire::nullable_decimal(wire::read_i64_le(at(52)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::optional<Decimal> contract_multiplier() const { return wire::nullable_decimal(wire::read_i64_le(at(60)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8); }

    std::optional<Decimal> price_divisor() const { return wire::nullable_decimal(wire::read_i64_le(at(68)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8); }

    std::optional<std::int64_t> security_validity_timestamp() const { return wire::nullable(wire::read_i64_le(at(76)), static_cast<std::int64_t>(-9223372036854775807LL - 1)); }

    std::optional<std::uint64_t> no_shares_issued() const { return wire::nullable(wire::read_u64_le(at(84)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint64_t> clearing_house_id() const { return wire::nullable(wire::read_u64_le(at(92)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::int64_t> min_order_qty() const { return wire::nullable(wire::read_i64_le(at(100)), static_cast<std::int64_t>(-9223372036854775807LL - 1)); }

    std::optional<std::int64_t> max_order_qty() const { return wire::nullable(wire::read_i64_le(at(108)), static_cast<std::int64_t>(-9223372036854775807LL - 1)); }

    std::optional<std::int64_t> min_lot_size() const { return wire::nullable(wire::read_i64_le(at(116)), static_cast<std::int64_t>(-9223372036854775807LL - 1)); }

    std::optional<std::int64_t> min_trade_vol() const { return wire::nullable(wire::read_i64_le(at(124)), static_cast<std::int64_t>(-9223372036854775807LL - 1)); }

    std::optional<std::uint32_t> corporate_action_event_id() const { return wire::nullable(wire::read_u32_le(at(132)), static_cast<std::uint32_t>(0ULL)); }

    std::int32_t issue_date() const { return wire::read_i32_le(at(136)); }

    std::optional<std::int32_t> maturity_date() const { return wire::nullable(wire::read_i32_le(at(140)), static_cast<std::int32_t>(0LL)); }

    std::string_view country_of_issue() const { return view::text(at(144), 2, '\0'); }

    std::optional<std::int32_t> start_date() const { return wire::nullable(wire::read_i32_le(at(146)), static_cast<std::int32_t>(0LL)); }

    std::optional<std::int32_t> end_date() const { return wire::nullable(wire::read_i32_le(at(150)), static_cast<std::int32_t>(0LL)); }

    std::optional<std::uint16_t> settl_type() const { return wire::nullable(wire::read_u16_le(at(154)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<std::int32_t> settl_date() const { return wire::nullable(wire::read_i32_le(at(156)), static_cast<std::int32_t>(0LL)); }

    std::optional<std::int32_t> dated_date() const { return wire::nullable(wire::read_i32_le(at(160)), static_cast<std::int32_t>(0LL)); }

    std::string_view isin_number() const { return view::text(at(164), 12, '\0'); }

    std::string_view asset() const { return view::text(at(176), 6, '\0'); }

    std::string_view cfi_code() const { return view::text(at(182), 6, '\0'); }

    MaturityMonthYear maturity_month_year() const { return MaturityMonthYear{ bytes_.subspan(188) }; }

    ContractSettlMonth contract_settl_month() const { return ContractSettlMonth{ bytes_.subspan(193) }; }

    std::string_view currency() const { return view::text(at(198), 3, '\0'); }

    std::string_view strike_currency() const { return view::text(at(201), 3, '\0'); }

    std::string_view settl_currency() const { return view::text(at(204), 3, '\0'); }

    std::string_view security_strategy_type() const { return view::text(at(207), 3, '\0'); }

    std::optional<LotType> lot_type() const { return wire::nullable_enum<LotType>(wire::read_u8(at(210)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> tick_size_denominator() const { return wire::nullable(wire::read_u8(at(211)), static_cast<std::uint8_t>(255ULL)); }

    Product product() const { return static_cast<Product>(wire::read_u8(at(212))); }

    std::optional<ExerciseStyle> exercise_style() const { return wire::nullable_enum<ExerciseStyle>(wire::read_u8(at(213)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<PutOrCall> put_or_call() const { return wire::nullable_enum<PutOrCall>(wire::read_u8(at(214)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<PriceType> price_type() const { return wire::nullable_enum<PriceType>(wire::read_u8(at(215)), static_cast<std::uint8_t>(0ULL)); }

    std::optional<std::uint8_t> market_segment_id() const { return wire::nullable(wire::read_u8(at(216)), static_cast<std::uint8_t>(0ULL)); }

    std::optional<GovernanceIndicator> governance_indicator() const { return wire::nullable_enum<GovernanceIndicator>(wire::read_u8(at(217)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<SecurityMatchType> security_match_type() const { return wire::nullable_enum<SecurityMatchType>(wire::read_u8(at(218)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<LastFragment> last_fragment() const { return wire::nullable_enum<LastFragment>(wire::read_u8(at(219)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<MultiLegModel> multi_leg_model() const { return wire::nullable_enum<MultiLegModel>(wire::read_u8(at(220)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<MultiLegPriceMethod> multi_leg_price_method() const { return wire::nullable_enum<MultiLegPriceMethod>(wire::read_u8(at(221)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::int64_t> min_cross_qty() const { return wire::nullable(wire::read_i64_le(at(222)), static_cast<std::int64_t>(-9223372036854775807LL - 1)); }

    DeprecatedUnderlyingsGroups deprecated_underlyings_groups() const { return DeprecatedUnderlyingsGroups{ bytes_.subspan(230) }; }

    DeprecatedLegsGroups deprecated_legs_groups() const {
        wire::require("DeprecatedSecurityDefinitionMessage", deprecated_underlyings_groups_end() + DeprecatedLegsGroups::minimum_size, bytes_.size());
        return DeprecatedLegsGroups{ bytes_.subspan(deprecated_underlyings_groups_end()) };
    }

    DeprecatedInstrAttribsGroups deprecated_instr_attribs_groups() const {
        wire::require("DeprecatedSecurityDefinitionMessage", deprecated_legs_groups_end() + DeprecatedInstrAttribsGroups::minimum_size, bytes_.size());
        return DeprecatedInstrAttribsGroups{ bytes_.subspan(deprecated_legs_groups_end()) };
    }

    SecurityDesc security_desc() const {
        wire::require("DeprecatedSecurityDefinitionMessage", deprecated_instr_attribs_groups_end() + SecurityDesc::minimum_size, bytes_.size());
        return SecurityDesc{ bytes_.subspan(deprecated_instr_attribs_groups_end()) };
    }

    void print(std::ostream& out) const {
        out << "DeprecatedSecurityDefinitionMessage{";
        out << "security_id=";
        out << security_id();
        out << ", security_exchange=";
        print::text(out, security_exchange());
        out << ", security_id_source=";
        out << security_id_source();
        out << ", security_group=";
        print::text(out, security_group());
        out << ", symbol=";
        print::text(out, symbol());
        out << ", security_update_action=";
        out << security_update_action();
        out << ", security_type=";
        out << security_type();
        out << ", security_sub_type=";
        out << security_sub_type();
        out << ", tot_no_related_sym=";
        out << tot_no_related_sym();
        out << ", min_price_increment_legacy=";
        print::optional(out, min_price_increment_legacy());
        out << ", strike_price=";
        print::optional(out, strike_price());
        out << ", contract_multiplier=";
        print::optional(out, contract_multiplier());
        out << ", price_divisor=";
        print::optional(out, price_divisor());
        out << ", security_validity_timestamp=";
        print::optional(out, security_validity_timestamp());
        out << ", no_shares_issued=";
        print::optional(out, no_shares_issued());
        out << ", clearing_house_id=";
        print::optional(out, clearing_house_id());
        out << ", min_order_qty=";
        print::optional(out, min_order_qty());
        out << ", max_order_qty=";
        print::optional(out, max_order_qty());
        out << ", min_lot_size=";
        print::optional(out, min_lot_size());
        out << ", min_trade_vol=";
        print::optional(out, min_trade_vol());
        out << ", corporate_action_event_id=";
        print::optional(out, corporate_action_event_id());
        out << ", issue_date=";
        out << issue_date();
        out << ", maturity_date=";
        print::optional(out, maturity_date());
        out << ", country_of_issue=";
        print::text(out, country_of_issue());
        out << ", start_date=";
        print::optional(out, start_date());
        out << ", end_date=";
        print::optional(out, end_date());
        out << ", settl_type=";
        print::optional(out, settl_type());
        out << ", settl_date=";
        print::optional(out, settl_date());
        out << ", dated_date=";
        print::optional(out, dated_date());
        out << ", isin_number=";
        print::text(out, isin_number());
        out << ", asset=";
        print::text(out, asset());
        out << ", cfi_code=";
        print::text(out, cfi_code());
        out << ", maturity_month_year=";
        maturity_month_year().print(out);
        out << ", contract_settl_month=";
        contract_settl_month().print(out);
        out << ", currency=";
        print::text(out, currency());
        out << ", strike_currency=";
        print::text(out, strike_currency());
        out << ", settl_currency=";
        print::text(out, settl_currency());
        out << ", security_strategy_type=";
        print::text(out, security_strategy_type());
        out << ", lot_type=";
        print::optional(out, lot_type());
        out << ", tick_size_denominator=";
        print::optional(out, tick_size_denominator());
        out << ", product=";
        out << product();
        out << ", exercise_style=";
        print::optional(out, exercise_style());
        out << ", put_or_call=";
        print::optional(out, put_or_call());
        out << ", price_type=";
        print::optional(out, price_type());
        out << ", market_segment_id=";
        print::optional(out, market_segment_id());
        out << ", governance_indicator=";
        print::optional(out, governance_indicator());
        out << ", security_match_type=";
        print::optional(out, security_match_type());
        out << ", last_fragment=";
        print::optional(out, last_fragment());
        out << ", multi_leg_model=";
        print::optional(out, multi_leg_model());
        out << ", multi_leg_price_method=";
        print::optional(out, multi_leg_price_method());
        out << ", min_cross_qty=";
        print::optional(out, min_cross_qty());
        out << ", deprecated_underlyings_groups=";
        deprecated_underlyings_groups().print(out);
        out << ", deprecated_legs_groups=";
        deprecated_legs_groups().print(out);
        out << ", deprecated_instr_attribs_groups=";
        deprecated_instr_attribs_groups().print(out);
        out << ", security_desc=";
        security_desc().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t deprecated_underlyings_groups_end() const { return 230 + deprecated_underlyings_groups().encoded_size(); }
    std::size_t deprecated_legs_groups_end() const { return deprecated_underlyings_groups_end() + deprecated_legs_groups().encoded_size(); }
    std::size_t deprecated_instr_attribs_groups_end() const { return deprecated_legs_groups_end() + deprecated_instr_attribs_groups().encoded_size(); }
    std::size_t security_desc_end() const { return deprecated_instr_attribs_groups_end() + security_desc().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const DeprecatedSecurityDefinitionMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
