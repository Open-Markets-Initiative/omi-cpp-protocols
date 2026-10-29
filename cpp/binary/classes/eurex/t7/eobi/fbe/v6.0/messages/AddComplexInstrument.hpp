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
#include "../groups/InstrmtLegGrpComp.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

class Visitor;

// Add Complex Instrument
class AddComplexInstrument : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::AddComplexInstrument;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 504;

    AddComplexInstrument() = default;
    AddComplexInstrument(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::int32_t> security_sub_type, std::optional<ProductComplex> product_complex, std::optional<ImpliedMarketIndicator> implied_market_indicator, std::optional<std::uint8_t> no_legs, const std::array<std::byte, 1>& pad1, const std::array<InstrmtLegGrpComp, 20>& instrmt_leg_grp_comp);

    // Security Id:
    std::optional<std::int64_t> security_id() const;
    void set_security_id(std::optional<std::int64_t> value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Security Sub Type:
    std::optional<std::int32_t> security_sub_type() const;
    void set_security_sub_type(std::optional<std::int32_t> value);

    // Product Complex:
    std::optional<ProductComplex> product_complex() const;
    void set_product_complex(std::optional<ProductComplex> value);

    // Implied Market Indicator:
    std::optional<ImpliedMarketIndicator> implied_market_indicator() const;
    void set_implied_market_indicator(std::optional<ImpliedMarketIndicator> value);

    // No Legs:
    std::optional<std::uint8_t> no_legs() const;
    void set_no_legs(std::optional<std::uint8_t> value);

    // Pad1:
    const std::array<std::byte, 1>& pad1() const;
    std::array<std::byte, 1>& pad1();
    void set_pad1(const std::array<std::byte, 1>& value);

    // Instrmt Leg Grp Comp:
    const std::array<InstrmtLegGrpComp, 20>& instrmt_leg_grp_comp() const;
    std::array<InstrmtLegGrpComp, 20>& instrmt_leg_grp_comp();
    void set_instrmt_leg_grp_comp(const std::array<InstrmtLegGrpComp, 20>& value);

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

    bool operator==(const AddComplexInstrument& other) const;
    bool operator!=(const AddComplexInstrument& other) const;

  private:
    std::optional<std::int64_t> security_id_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::optional<std::int32_t> security_sub_type_{};
    std::optional<ProductComplex> product_complex_{};
    std::optional<ImpliedMarketIndicator> implied_market_indicator_{};
    std::optional<std::uint8_t> no_legs_{};
    std::array<std::byte, 1> pad1_{};
    std::array<InstrmtLegGrpComp, 20> instrmt_leg_grp_comp_{};
};

} // namespace eurex::t7::eobi::fbe::v6_0
