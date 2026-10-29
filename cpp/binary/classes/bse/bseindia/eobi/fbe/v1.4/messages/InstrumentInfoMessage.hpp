#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published whenever there is a change in the daily price range of the instrument.
class InstrumentInfoMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::InstrumentInfoMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    InstrumentInfoMessage() = default;
    InstrumentInfoMessage(std::int64_t security_id, std::optional<Decimal> close_price, std::optional<Decimal> prev_close_price, std::optional<Decimal> upper_ckt_limit, std::optional<Decimal> lower_ckt_limit);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Close Price: Close Price
    std::optional<Decimal> close_price() const;
    void set_close_price(std::optional<Decimal> value);

    // Prev Close Price: Previous Close Price
    std::optional<Decimal> prev_close_price() const;
    void set_prev_close_price(std::optional<Decimal> value);

    // Upper Ckt Limit: Upper Circuit Limit Price
    std::optional<Decimal> upper_ckt_limit() const;
    void set_upper_ckt_limit(std::optional<Decimal> value);

    // Lower Ckt Limit: Lower Circuit Limit Price
    std::optional<Decimal> lower_ckt_limit() const;
    void set_lower_ckt_limit(std::optional<Decimal> value);

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

    bool operator==(const InstrumentInfoMessage& other) const;
    bool operator!=(const InstrumentInfoMessage& other) const;

  private:
    std::int64_t security_id_{};
    std::optional<Decimal> close_price_{};
    std::optional<Decimal> prev_close_price_{};
    std::optional<Decimal> upper_ckt_limit_{};
    std::optional<Decimal> lower_ckt_limit_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
