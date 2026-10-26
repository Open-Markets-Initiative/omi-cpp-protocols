#pragma once

#include <cstddef>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/MdEntryType.hpp"
#include "../enums/MdOriginType.hpp"
#include "../enums/MultiLegPriceModel.hpp"
#include "../enums/MultiLegReportingType.hpp"
#include "../enums/TradeCondition.hpp"
#include "../enums/TrdType.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// Md Instrument Entry Grp Comp
class MdInstrumentEntryGrpComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    MdInstrumentEntryGrpComp() = default;
    MdInstrumentEntryGrpComp(std::optional<Decimal> md_entry_px, std::optional<Decimal> md_entry_size, std::optional<MdOriginType> md_origin_type, std::optional<MdEntryType> md_entry_type, std::optional<TradeCondition> trade_condition, std::optional<TrdType> trd_type, std::optional<MultiLegReportingType> multi_leg_reporting_type, std::optional<MultiLegPriceModel> multi_leg_price_model, std::optional<Decimal> non_disclosed_trade_volume);

    // Md Entry Px:
    std::optional<Decimal> md_entry_px() const;
    void set_md_entry_px(std::optional<Decimal> value);

    // Md Entry Size:
    std::optional<Decimal> md_entry_size() const;
    void set_md_entry_size(std::optional<Decimal> value);

    // Md Origin Type:
    std::optional<MdOriginType> md_origin_type() const;
    void set_md_origin_type(std::optional<MdOriginType> value);

    // Md Entry Type:
    std::optional<MdEntryType> md_entry_type() const;
    void set_md_entry_type(std::optional<MdEntryType> value);

    // Trade Condition:
    std::optional<TradeCondition> trade_condition() const;
    void set_trade_condition(std::optional<TradeCondition> value);

    // Trd Type:
    std::optional<TrdType> trd_type() const;
    void set_trd_type(std::optional<TrdType> value);

    // Multi Leg Reporting Type:
    std::optional<MultiLegReportingType> multi_leg_reporting_type() const;
    void set_multi_leg_reporting_type(std::optional<MultiLegReportingType> value);

    // Multi Leg Price Model:
    std::optional<MultiLegPriceModel> multi_leg_price_model() const;
    void set_multi_leg_price_model(std::optional<MultiLegPriceModel> value);

    // Non Disclosed Trade Volume:
    std::optional<Decimal> non_disclosed_trade_volume() const;
    void set_non_disclosed_trade_volume(std::optional<Decimal> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MdInstrumentEntryGrpComp& other) const;
    bool operator!=(const MdInstrumentEntryGrpComp& other) const;

  private:
    std::optional<Decimal> md_entry_px_{};
    std::optional<Decimal> md_entry_size_{};
    std::optional<MdOriginType> md_origin_type_{};
    std::optional<MdEntryType> md_entry_type_{};
    std::optional<TradeCondition> trade_condition_{};
    std::optional<TrdType> trd_type_{};
    std::optional<MultiLegReportingType> multi_leg_reporting_type_{};
    std::optional<MultiLegPriceModel> multi_leg_price_model_{};
    std::optional<Decimal> non_disclosed_trade_volume_{};
};

std::ostream& operator<<(std::ostream& out, const MdInstrumentEntryGrpComp& value);

} // namespace eurex::t7::eobi::fbe::v13_0
