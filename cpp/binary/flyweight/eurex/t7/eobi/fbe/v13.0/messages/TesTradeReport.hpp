#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TrdType.hpp"
#include "../enums/TradeCondition.hpp"
#include "../enums/MultiLegReportingType.hpp"
#include "../enums/MultiLegPriceModel.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class TesTradeReport {
  public:
    static constexpr const char* name = "TesTradeReport";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TesTradeReport(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TesTradeReport has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 72;
    static constexpr std::size_t fixed_size = 72;
    std::size_t encoded_size() const { return 72; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<Decimal> last_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<Decimal> last_px() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<std::uint32_t> trd_match_id() const { return wire::nullable(wire::read_u32_le(at(32)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    std::optional<TrdType> trd_type() const { return wire::nullable_enum<TrdType>(wire::read_u16_le(at(36)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<TradeCondition> trade_condition() const { return wire::nullable_enum<TradeCondition>(wire::read_u16_le(at(38)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<MultiLegReportingType> multi_leg_reporting_type() const { return wire::nullable_enum<MultiLegReportingType>(wire::read_u8(at(40)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<MultiLegPriceModel> multi_leg_price_model() const { return wire::nullable_enum<MultiLegPriceModel>(wire::read_u8(at(41)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 6> pad6() const { return bytes_.subspan(42).template first<6>(); }

    std::optional<Decimal> non_disclosed_trade_volume() const { return wire::nullable_decimal(wire::read_i64_le(at(48)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<std::chrono::nanoseconds> trans_bkd_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(56)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::uint16_t> number_of_buy_sides() const { return wire::nullable(wire::read_u16_le(at(64)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<std::uint16_t> number_of_sell_sides() const { return wire::nullable(wire::read_u16_le(at(66)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::span<const std::byte, 4> pad4() const { return bytes_.subspan(68).template first<4>(); }

    void print(std::ostream& out) const {
        out << "TesTradeReport{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << ", last_qty=";
        print::optional(out, last_qty());
        out << ", last_px=";
        print::optional(out, last_px());
        out << ", trd_match_id=";
        print::optional(out, trd_match_id());
        out << ", trd_type=";
        print::optional(out, trd_type());
        out << ", trade_condition=";
        print::optional(out, trade_condition());
        out << ", multi_leg_reporting_type=";
        print::optional(out, multi_leg_reporting_type());
        out << ", multi_leg_price_model=";
        print::optional(out, multi_leg_price_model());
        out << ", pad6=";
        print::hex(out, pad6().data(), pad6().size());
        out << ", non_disclosed_trade_volume=";
        print::optional(out, non_disclosed_trade_volume());
        out << ", trans_bkd_time=";
        print::optional_duration(out, trans_bkd_time());
        out << ", number_of_buy_sides=";
        print::optional(out, number_of_buy_sides());
        out << ", number_of_sell_sides=";
        print::optional(out, number_of_sell_sides());
        out << ", pad4=";
        print::hex(out, pad4().data(), pad4().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TesTradeReport& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
