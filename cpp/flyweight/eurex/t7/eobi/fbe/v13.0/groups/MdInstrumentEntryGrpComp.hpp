#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdOriginType.hpp"
#include "../enums/MdEntryType.hpp"
#include "../enums/TradeCondition.hpp"
#include "../enums/TrdType.hpp"
#include "../enums/MultiLegReportingType.hpp"
#include "../enums/MultiLegPriceModel.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class MdInstrumentEntryGrpComp {
  public:
    static constexpr const char* name = "MdInstrumentEntryGrpComp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MdInstrumentEntryGrpComp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MdInstrumentEntryGrpComp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::optional<Decimal> md_entry_px() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<Decimal> md_entry_size() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<MdOriginType> md_origin_type() const { return wire::nullable_enum<MdOriginType>(wire::read_u8(at(16)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<MdEntryType> md_entry_type() const { return wire::nullable_enum<MdEntryType>(wire::read_u8(at(17)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<TradeCondition> trade_condition() const { return wire::nullable_enum<TradeCondition>(wire::read_u16_le(at(18)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<TrdType> trd_type() const { return wire::nullable_enum<TrdType>(wire::read_u16_le(at(20)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<MultiLegReportingType> multi_leg_reporting_type() const { return wire::nullable_enum<MultiLegReportingType>(wire::read_u8(at(22)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<MultiLegPriceModel> multi_leg_price_model() const { return wire::nullable_enum<MultiLegPriceModel>(wire::read_u8(at(23)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<Decimal> non_disclosed_trade_volume() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    void print(std::ostream& out) const {
        out << "MdInstrumentEntryGrpComp{";
        out << "md_entry_px=";
        print::optional(out, md_entry_px());
        out << ", md_entry_size=";
        print::optional(out, md_entry_size());
        out << ", md_origin_type=";
        print::optional(out, md_origin_type());
        out << ", md_entry_type=";
        print::optional(out, md_entry_type());
        out << ", trade_condition=";
        print::optional(out, trade_condition());
        out << ", trd_type=";
        print::optional(out, trd_type());
        out << ", multi_leg_reporting_type=";
        print::optional(out, multi_leg_reporting_type());
        out << ", multi_leg_price_model=";
        print::optional(out, multi_leg_price_model());
        out << ", non_disclosed_trade_volume=";
        print::optional(out, non_disclosed_trade_volume());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MdInstrumentEntryGrpComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
