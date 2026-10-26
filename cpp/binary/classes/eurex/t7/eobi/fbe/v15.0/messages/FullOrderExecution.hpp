#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/AlgorithmicTradeIndicator.hpp"
#include "../enums/HhiIndicator.hpp"
#include "../enums/OrdType.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class Visitor;

// Full Order Execution
class FullOrderExecution : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::FullOrderExecution;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 48;

    FullOrderExecution() = default;
    FullOrderExecution(std::optional<Side> side, std::optional<OrdType> ord_type, std::optional<AlgorithmicTradeIndicator> algorithmic_trade_indicator, std::optional<HhiIndicator> hhi_indicator, std::optional<std::uint32_t> trd_match_id, std::optional<Decimal> price, std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority, std::optional<std::int64_t> security_id, std::optional<Decimal> last_qty, std::optional<Decimal> last_px);

    // Side:
    std::optional<Side> side() const;
    void set_side(std::optional<Side> value);

    // Ord Type:
    std::optional<OrdType> ord_type() const;
    void set_ord_type(std::optional<OrdType> value);

    // Algorithmic Trade Indicator:
    std::optional<AlgorithmicTradeIndicator> algorithmic_trade_indicator() const;
    void set_algorithmic_trade_indicator(std::optional<AlgorithmicTradeIndicator> value);

    // Hhi Indicator:
    std::optional<HhiIndicator> hhi_indicator() const;
    void set_hhi_indicator(std::optional<HhiIndicator> value);

    // Trd Match Id:
    std::optional<std::uint32_t> trd_match_id() const;
    void set_trd_match_id(std::optional<std::uint32_t> value);

    // Price:
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Trd Reg Ts Time Priority:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority() const;
    void set_trd_reg_ts_time_priority(std::optional<std::chrono::nanoseconds> value);

    // Security Id: Unique instrument identifier
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Last Qty: Total executed matched quantity of this match event
    std::optional<Decimal> last_qty() const;
    void set_last_qty(std::optional<Decimal> value);

    // Last Px:
    std::optional<Decimal> last_px() const;
    void set_last_px(std::optional<Decimal> value);

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

    bool operator==(const FullOrderExecution& other) const;
    bool operator!=(const FullOrderExecution& other) const;

  private:
    std::optional<Side> side_{};
    std::optional<OrdType> ord_type_{};
    std::optional<AlgorithmicTradeIndicator> algorithmic_trade_indicator_{};
    std::optional<HhiIndicator> hhi_indicator_{};
    std::optional<std::uint32_t> trd_match_id_{};
    std::optional<Decimal> price_{};
    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority_{};
    std::optional<std::int64_t> security_id_{};
    std::optional<Decimal> last_qty_{};
    std::optional<Decimal> last_px_{};
};

} // namespace eurex::t7::eobi::fbe::v15_0
