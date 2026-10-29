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
#include "../enums/AlgorithmicTradeIndicator.hpp"
#include "../enums/OrdType.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

class Visitor;

// Partial Order Execution
class PartialOrderExecution : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::PartialOrderExecution;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 48;

    PartialOrderExecution() = default;
    PartialOrderExecution(std::optional<Side> side, std::optional<OrdType> ord_type, std::optional<AlgorithmicTradeIndicator> algorithmic_trade_indicator, const std::array<std::byte, 5>& pad5, std::optional<Decimal> price, std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority, std::optional<std::int64_t> security_id, std::optional<std::uint32_t> trd_match_id, std::optional<std::int32_t> last_qty, std::optional<Decimal> last_px);

    // Side:
    std::optional<Side> side() const;
    void set_side(std::optional<Side> value);

    // Ord Type:
    std::optional<OrdType> ord_type() const;
    void set_ord_type(std::optional<OrdType> value);

    // Algorithmic Trade Indicator:
    std::optional<AlgorithmicTradeIndicator> algorithmic_trade_indicator() const;
    void set_algorithmic_trade_indicator(std::optional<AlgorithmicTradeIndicator> value);

    // Pad5:
    const std::array<std::byte, 5>& pad5() const;
    std::array<std::byte, 5>& pad5();
    void set_pad5(const std::array<std::byte, 5>& value);

    // Price:
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Trd Reg Ts Time Priority:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority() const;
    void set_trd_reg_ts_time_priority(std::optional<std::chrono::nanoseconds> value);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Trd Match Id:
    std::optional<std::uint32_t> trd_match_id() const;
    void set_trd_match_id(std::optional<std::uint32_t> value);

    // Last Qty:
    std::optional<std::int32_t> last_qty() const;
    void set_last_qty(std::optional<std::int32_t> value);

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

    bool operator==(const PartialOrderExecution& other) const;
    bool operator!=(const PartialOrderExecution& other) const;

  private:
    std::optional<Side> side_{};
    std::optional<OrdType> ord_type_{};
    std::optional<AlgorithmicTradeIndicator> algorithmic_trade_indicator_{};
    std::array<std::byte, 5> pad5_{};
    std::optional<Decimal> price_{};
    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority_{};
    std::optional<std::int64_t> security_id_{};
    std::optional<std::uint32_t> trd_match_id_{};
    std::optional<std::int32_t> last_qty_{};
    std::optional<Decimal> last_px_{};
};

} // namespace eurex::t7::eobi::fbe::v6_0
