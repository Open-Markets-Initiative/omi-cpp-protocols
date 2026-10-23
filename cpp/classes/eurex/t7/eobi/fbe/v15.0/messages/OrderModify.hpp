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
#include "../enums/PrevPriceHhiIndicator.hpp"
#include "../messages/Message.hpp"
#include "../structs/OrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class Visitor;

// Order Modify
class OrderModify : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::OrderModify;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 80;

    OrderModify() = default;
    OrderModify(std::optional<std::chrono::nanoseconds> request_time, std::optional<std::chrono::nanoseconds> trd_reg_ts_prev_time_priority, std::optional<Decimal> prev_price, std::optional<Decimal> prev_display_qty, std::optional<std::int64_t> security_id, const OrderDetailsComp& order_details_comp, std::optional<PrevPriceHhiIndicator> prev_price_hhi_indicator, const std::array<std::byte, 7>& pad7);

    // Request Time:
    std::optional<std::chrono::nanoseconds> request_time() const;
    void set_request_time(std::optional<std::chrono::nanoseconds> value);

    // Trd Reg Ts Prev Time Priority:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_prev_time_priority() const;
    void set_trd_reg_ts_prev_time_priority(std::optional<std::chrono::nanoseconds> value);

    // Prev Price:
    std::optional<Decimal> prev_price() const;
    void set_prev_price(std::optional<Decimal> value);

    // Prev Display Qty:
    std::optional<Decimal> prev_display_qty() const;
    void set_prev_display_qty(std::optional<Decimal> value);

    // Security Id: Unique instrument identifier
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Order Details Comp:
    const OrderDetailsComp& order_details_comp() const;
    OrderDetailsComp& order_details_comp();
    void set_order_details_comp(const OrderDetailsComp& value);

    // Prev Price Hhi Indicator:
    std::optional<PrevPriceHhiIndicator> prev_price_hhi_indicator() const;
    void set_prev_price_hhi_indicator(std::optional<PrevPriceHhiIndicator> value);

    // Pad7:
    const std::array<std::byte, 7>& pad7() const;
    std::array<std::byte, 7>& pad7();
    void set_pad7(const std::array<std::byte, 7>& value);

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

    bool operator==(const OrderModify& other) const;
    bool operator!=(const OrderModify& other) const;

  private:
    std::optional<std::chrono::nanoseconds> request_time_{};
    std::optional<std::chrono::nanoseconds> trd_reg_ts_prev_time_priority_{};
    std::optional<Decimal> prev_price_{};
    std::optional<Decimal> prev_display_qty_{};
    std::optional<std::int64_t> security_id_{};
    OrderDetailsComp order_details_comp_{};
    std::optional<PrevPriceHhiIndicator> prev_price_hhi_indicator_{};
    std::array<std::byte, 7> pad7_{};
};

} // namespace eurex::t7::eobi::fbe::v15_0
