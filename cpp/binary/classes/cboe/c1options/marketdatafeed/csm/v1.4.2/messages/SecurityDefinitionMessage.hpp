#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../enums/ExerciseStyle.hpp"
#include "../enums/PutOrCall.hpp"
#include "../enums/SecurityExchange.hpp"
#include "../groups/SecurityDefinitionLeg.hpp"
#include "../messages/Message.hpp"
#include "../structs/CurrencyCode.hpp"
#include "../structs/MaxStrikePrice.hpp"
#include "../structs/MinimumAbovePremiumFraction.hpp"
#include "../structs/MinimumBelowPremiumFraction.hpp"
#include "../structs/MinimumStrikePriceFraction.hpp"
#include "../structs/PremiumBreakPoint.hpp"
#include "../structs/SecurityType.hpp"
#include "../structs/StrikePrice.hpp"
#include "../structs/Symbol.hpp"
#include "../structs/TargetLocationId.hpp"
#include "../structs/UnderlyingSymbol.hpp"
#include "../structs/UnderlyingType.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class Visitor;

// Security definitions describe an exchange’s products by name and trading parameters and
// associates those products with a product security ID.
class SecurityDefinitionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SecurityDefinitionMessage;

    SecurityDefinitionMessage() = default;
    SecurityDefinitionMessage(const SecurityType& security_type, SecurityExchange security_exchange, const Symbol& symbol, const TargetLocationId& target_location_id, std::uint32_t class_key, std::uint32_t security_id, std::uint64_t maturity_date, std::uint8_t price_type, const StrikePrice& strike_price, PutOrCall put_or_call, const MinimumStrikePriceFraction& minimum_strike_price_fraction, const MaxStrikePrice& max_strike_price, const PremiumBreakPoint& premium_break_point, const MinimumAbovePremiumFraction& minimum_above_premium_fraction, const MinimumBelowPremiumFraction& minimum_below_premium_fraction, ExerciseStyle exercise_style, const CurrencyCode& currency_code, const UnderlyingSymbol& underlying_symbol, const UnderlyingType& underlying_type, std::uint32_t contract_size, std::uint8_t no_legs, const std::vector<SecurityDefinitionLeg>& security_definition_leg);

    // Security Type:
    const SecurityType& security_type() const;
    SecurityType& security_type();
    void set_security_type(const SecurityType& value);

    // Security Exchange:
    SecurityExchange security_exchange() const;
    void set_security_exchange(SecurityExchange value);

    // Symbol:
    const Symbol& symbol() const;
    Symbol& symbol();
    void set_symbol(const Symbol& value);

    // Target Location Id:
    const TargetLocationId& target_location_id() const;
    TargetLocationId& target_location_id();
    void set_target_location_id(const TargetLocationId& value);

    // Class Key: Class key
    std::uint32_t class_key() const;
    void set_class_key(std::uint32_t value);

    // Security Id: Product key
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Maturity Date: Expiration date: Format is “YYYYMMDD”. This field is required for options
    // and futures
    std::uint64_t maturity_date() const;
    void set_maturity_date(std::uint64_t value);

    // Price Type: Specifies how to interpret the value in the StrikePrice field.
    std::uint8_t price_type() const;
    void set_price_type(std::uint8_t value);

    // Strike Price:
    const StrikePrice& strike_price() const;
    StrikePrice& strike_price();
    void set_strike_price(const StrikePrice& value);

    // Put Or Call: This field is required for options.
    PutOrCall put_or_call() const;
    void set_put_or_call(PutOrCall value);

    // Minimum Strike Price Fraction:
    const MinimumStrikePriceFraction& minimum_strike_price_fraction() const;
    MinimumStrikePriceFraction& minimum_strike_price_fraction();
    void set_minimum_strike_price_fraction(const MinimumStrikePriceFraction& value);

    // Max Strike Price:
    const MaxStrikePrice& max_strike_price() const;
    MaxStrikePrice& max_strike_price();
    void set_max_strike_price(const MaxStrikePrice& value);

    // Premium Break Point:
    const PremiumBreakPoint& premium_break_point() const;
    PremiumBreakPoint& premium_break_point();
    void set_premium_break_point(const PremiumBreakPoint& value);

    // Minimum Above Premium Fraction:
    const MinimumAbovePremiumFraction& minimum_above_premium_fraction() const;
    MinimumAbovePremiumFraction& minimum_above_premium_fraction();
    void set_minimum_above_premium_fraction(const MinimumAbovePremiumFraction& value);

    // Minimum Below Premium Fraction:
    const MinimumBelowPremiumFraction& minimum_below_premium_fraction() const;
    MinimumBelowPremiumFraction& minimum_below_premium_fraction();
    void set_minimum_below_premium_fraction(const MinimumBelowPremiumFraction& value);

    // Exercise Style:
    ExerciseStyle exercise_style() const;
    void set_exercise_style(ExerciseStyle value);

    // Currency Code:
    const CurrencyCode& currency_code() const;
    CurrencyCode& currency_code();
    void set_currency_code(const CurrencyCode& value);

    // Underlying Symbol:
    const UnderlyingSymbol& underlying_symbol() const;
    UnderlyingSymbol& underlying_symbol();
    void set_underlying_symbol(const UnderlyingSymbol& value);

    // Underlying Type:
    const UnderlyingType& underlying_type() const;
    UnderlyingType& underlying_type();
    void set_underlying_type(const UnderlyingType& value);

    // Contract Size: The number of contracts per unit of size
    std::uint32_t contract_size() const;
    void set_contract_size(std::uint32_t value);

    // No Legs: Num. of Legs in a strategy product. Only used for products that contain legs
    // such as strategies. Will not exceed 255.
    std::uint8_t no_legs() const;
    void set_no_legs(std::uint8_t value);

    // Security Definition Leg: Security Definition Leg
    const std::vector<SecurityDefinitionLeg>& security_definition_leg() const;
    std::vector<SecurityDefinitionLeg>& security_definition_leg();
    void set_security_definition_leg(const std::vector<SecurityDefinitionLeg>& value);

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

    bool operator==(const SecurityDefinitionMessage& other) const;
    bool operator!=(const SecurityDefinitionMessage& other) const;

  private:
    SecurityType security_type_{};
    SecurityExchange security_exchange_{};
    Symbol symbol_{};
    TargetLocationId target_location_id_{};
    std::uint32_t class_key_{};
    std::uint32_t security_id_{};
    std::uint64_t maturity_date_{};
    std::uint8_t price_type_{};
    StrikePrice strike_price_{};
    PutOrCall put_or_call_{};
    MinimumStrikePriceFraction minimum_strike_price_fraction_{};
    MaxStrikePrice max_strike_price_{};
    PremiumBreakPoint premium_break_point_{};
    MinimumAbovePremiumFraction minimum_above_premium_fraction_{};
    MinimumBelowPremiumFraction minimum_below_premium_fraction_{};
    ExerciseStyle exercise_style_{};
    CurrencyCode currency_code_{};
    UnderlyingSymbol underlying_symbol_{};
    UnderlyingType underlying_type_{};
    std::uint32_t contract_size_{};
    std::uint8_t no_legs_{};
    std::vector<SecurityDefinitionLeg> security_definition_leg_{};
};

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
