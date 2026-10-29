#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/ImpliedMarketIndicator.hpp"
#include "../enums/ProductComplex.hpp"
#include "../groups/InstrmtLegGrp.hpp"
#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published whenever a new complex instrument is created intraday or an existing complex
// instrument is modified.
class AddComplexInstrumentMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::AddComplexInstrumentMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 104;

    AddComplexInstrumentMessage() = default;
    AddComplexInstrumentMessage(std::int64_t security_id, std::chrono::nanoseconds transact_time, std::optional<std::int32_t> security_sub_type, ProductComplex product_complex, ImpliedMarketIndicator implied_market_indicator, std::uint8_t no_legs, const std::array<std::byte, 1>& pad_1, const std::array<InstrmtLegGrp, 5>& instrmt_leg_grp);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Transact Time: Transaction timestamp.
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Security Sub Type: Strategy Type.
    std::optional<std::int32_t> security_sub_type() const;
    void set_security_sub_type(std::optional<std::int32_t> value);

    // Product Complex: This field qualifies an instrument type on BSE.
    ProductComplex product_complex() const;
    void set_product_complex(ProductComplex value);

    // Implied Market Indicator: Indicates that an implied market to be created for either the
    // legs of a multi-leg instrument or for the multi-leg instrument based on the existence of
    // the legs.
    ImpliedMarketIndicator implied_market_indicator() const;
    void set_implied_market_indicator(ImpliedMarketIndicator value);

    // No Legs: Number of Legs repeating group instances.
    std::uint8_t no_legs() const;
    void set_no_legs(std::uint8_t value);

    // Pad 1: not used
    const std::array<std::byte, 1>& pad_1() const;
    std::array<std::byte, 1>& pad_1();
    void set_pad_1(const std::array<std::byte, 1>& value);

    // Instrmt Leg Grp: Leg definitions repeated NoLegs times in the Add Complex Instrument
    // Message.
    const std::array<InstrmtLegGrp, 5>& instrmt_leg_grp() const;
    std::array<InstrmtLegGrp, 5>& instrmt_leg_grp();
    void set_instrmt_leg_grp(const std::array<InstrmtLegGrp, 5>& value);

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

    bool operator==(const AddComplexInstrumentMessage& other) const;
    bool operator!=(const AddComplexInstrumentMessage& other) const;

  private:
    std::int64_t security_id_{};
    std::chrono::nanoseconds transact_time_{};
    std::optional<std::int32_t> security_sub_type_{};
    ProductComplex product_complex_{};
    ImpliedMarketIndicator implied_market_indicator_{};
    std::uint8_t no_legs_{};
    std::array<std::byte, 1> pad_1_{};
    std::array<InstrmtLegGrp, 5> instrmt_leg_grp_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
