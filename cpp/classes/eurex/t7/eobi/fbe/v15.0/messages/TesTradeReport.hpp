#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/MultiLegPriceModel.hpp"
#include "../enums/MultiLegReportingType.hpp"
#include "../enums/TradeCondition.hpp"
#include "../enums/TrdType.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class Visitor;

// Tes Trade Report
class TesTradeReport : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::TesTradeReport;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 72;

    TesTradeReport() = default;
    TesTradeReport(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, std::optional<Decimal> last_qty, std::optional<Decimal> last_px, std::optional<std::uint32_t> trd_match_id, std::optional<TrdType> trd_type, std::optional<TradeCondition> trade_condition, std::optional<MultiLegReportingType> multi_leg_reporting_type, std::optional<MultiLegPriceModel> multi_leg_price_model, const std::array<std::byte, 6>& pad6, std::optional<Decimal> non_disclosed_trade_volume, std::optional<std::chrono::nanoseconds> trans_bkd_time, std::optional<std::uint16_t> number_of_buy_sides, std::optional<std::uint16_t> number_of_sell_sides, const std::array<std::byte, 4>& pad4);

    // Security Id: Unique instrument identifier
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Last Qty: Total executed matched quantity of this match event
    std::optional<Decimal> last_qty() const;
    void set_last_qty(std::optional<Decimal> value);

    // Last Px:
    std::optional<Decimal> last_px() const;
    void set_last_px(std::optional<Decimal> value);

    // Trd Match Id:
    std::optional<std::uint32_t> trd_match_id() const;
    void set_trd_match_id(std::optional<std::uint32_t> value);

    // Trd Type:
    std::optional<TrdType> trd_type() const;
    void set_trd_type(std::optional<TrdType> value);

    // Trade Condition:
    std::optional<TradeCondition> trade_condition() const;
    void set_trade_condition(std::optional<TradeCondition> value);

    // Multi Leg Reporting Type:
    std::optional<MultiLegReportingType> multi_leg_reporting_type() const;
    void set_multi_leg_reporting_type(std::optional<MultiLegReportingType> value);

    // Multi Leg Price Model:
    std::optional<MultiLegPriceModel> multi_leg_price_model() const;
    void set_multi_leg_price_model(std::optional<MultiLegPriceModel> value);

    // Pad6:
    const std::array<std::byte, 6>& pad6() const;
    std::array<std::byte, 6>& pad6();
    void set_pad6(const std::array<std::byte, 6>& value);

    // Non Disclosed Trade Volume:
    std::optional<Decimal> non_disclosed_trade_volume() const;
    void set_non_disclosed_trade_volume(std::optional<Decimal> value);

    // Trans Bkd Time:
    std::optional<std::chrono::nanoseconds> trans_bkd_time() const;
    void set_trans_bkd_time(std::optional<std::chrono::nanoseconds> value);

    // Number Of Buy Sides:
    std::optional<std::uint16_t> number_of_buy_sides() const;
    void set_number_of_buy_sides(std::optional<std::uint16_t> value);

    // Number Of Sell Sides:
    std::optional<std::uint16_t> number_of_sell_sides() const;
    void set_number_of_sell_sides(std::optional<std::uint16_t> value);

    // Pad4:
    const std::array<std::byte, 4>& pad4() const;
    std::array<std::byte, 4>& pad4();
    void set_pad4(const std::array<std::byte, 4>& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const TesTradeReport& other) const;
    bool operator!=(const TesTradeReport& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::optional<Decimal> last_qty_{};
    std::optional<Decimal> last_px_{};
    std::optional<std::uint32_t> trd_match_id_{};
    std::optional<TrdType> trd_type_{};
    std::optional<TradeCondition> trade_condition_{};
    std::optional<MultiLegReportingType> multi_leg_reporting_type_{};
    std::optional<MultiLegPriceModel> multi_leg_price_model_{};
    std::array<std::byte, 6> pad6_{};
    std::optional<Decimal> non_disclosed_trade_volume_{};
    std::optional<std::chrono::nanoseconds> trans_bkd_time_{};
    std::optional<std::uint16_t> number_of_buy_sides_{};
    std::optional<std::uint16_t> number_of_sell_sides_{};
    std::array<std::byte, 4> pad4_{};
};

} // namespace eurex::t7::eobi::fbe::v15_0
