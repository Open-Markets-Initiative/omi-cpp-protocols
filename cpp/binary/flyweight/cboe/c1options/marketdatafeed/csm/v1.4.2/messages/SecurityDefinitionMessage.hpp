#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/SecurityType.hpp"
#include "../enums/SecurityExchange.hpp"
#include "../structs/Symbol.hpp"
#include "../structs/TargetLocationId.hpp"
#include "../structs/StrikePrice.hpp"
#include "../enums/PutOrCall.hpp"
#include "../structs/MinimumStrikePriceFraction.hpp"
#include "../structs/MaxStrikePrice.hpp"
#include "../structs/PremiumBreakPoint.hpp"
#include "../structs/MinimumAbovePremiumFraction.hpp"
#include "../structs/MinimumBelowPremiumFraction.hpp"
#include "../enums/ExerciseStyle.hpp"
#include "../structs/CurrencyCode.hpp"
#include "../structs/UnderlyingSymbol.hpp"
#include "../structs/UnderlyingType.hpp"
#include "../groups/SecurityDefinitionLeg.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Security definitions describe an exchange’s products by name and trading parameters and
// associates those products with a product security ID.
class SecurityDefinitionMessage {
  public:
    static constexpr const char* name = "SecurityDefinitionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityDefinitionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityDefinitionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 55;
    std::size_t encoded_size() const { return security_definition_leg_end(); }

    SecurityType security_type() const { return SecurityType{ bytes_.subspan(0) }; }

    SecurityExchange security_exchange() const {
        wire::require("SecurityDefinitionMessage", security_type_end() + 1, bytes_.size());
        return static_cast<SecurityExchange>(wire::read_char(at(security_type_end())));
    }

    Symbol symbol() const {
        wire::require("SecurityDefinitionMessage", security_exchange_end() + Symbol::minimum_size, bytes_.size());
        return Symbol{ bytes_.subspan(security_exchange_end()) };
    }

    TargetLocationId target_location_id() const {
        wire::require("SecurityDefinitionMessage", symbol_end() + TargetLocationId::minimum_size, bytes_.size());
        return TargetLocationId{ bytes_.subspan(symbol_end()) };
    }

    std::uint32_t class_key() const {
        wire::require("SecurityDefinitionMessage", target_location_id_end() + 4, bytes_.size());
        return wire::read_u32_be(at(target_location_id_end()));
    }

    std::uint32_t security_id() const {
        wire::require("SecurityDefinitionMessage", class_key_end() + 4, bytes_.size());
        return wire::read_u32_be(at(class_key_end()));
    }

    std::uint64_t maturity_date() const {
        wire::require("SecurityDefinitionMessage", security_id_end() + 8, bytes_.size());
        return wire::read_u64_be(at(security_id_end()));
    }

    std::uint8_t price_type() const {
        wire::require("SecurityDefinitionMessage", maturity_date_end() + 1, bytes_.size());
        return wire::read_u8(at(maturity_date_end()));
    }

    StrikePrice strike_price() const {
        wire::require("SecurityDefinitionMessage", price_type_end() + StrikePrice::minimum_size, bytes_.size());
        return StrikePrice{ bytes_.subspan(price_type_end()) };
    }

    PutOrCall put_or_call() const {
        wire::require("SecurityDefinitionMessage", strike_price_end() + 1, bytes_.size());
        return static_cast<PutOrCall>(wire::read_u8(at(strike_price_end())));
    }

    MinimumStrikePriceFraction minimum_strike_price_fraction() const {
        wire::require("SecurityDefinitionMessage", put_or_call_end() + MinimumStrikePriceFraction::minimum_size, bytes_.size());
        return MinimumStrikePriceFraction{ bytes_.subspan(put_or_call_end()) };
    }

    MaxStrikePrice max_strike_price() const {
        wire::require("SecurityDefinitionMessage", minimum_strike_price_fraction_end() + MaxStrikePrice::minimum_size, bytes_.size());
        return MaxStrikePrice{ bytes_.subspan(minimum_strike_price_fraction_end()) };
    }

    PremiumBreakPoint premium_break_point() const {
        wire::require("SecurityDefinitionMessage", max_strike_price_end() + PremiumBreakPoint::minimum_size, bytes_.size());
        return PremiumBreakPoint{ bytes_.subspan(max_strike_price_end()) };
    }

    MinimumAbovePremiumFraction minimum_above_premium_fraction() const {
        wire::require("SecurityDefinitionMessage", premium_break_point_end() + MinimumAbovePremiumFraction::minimum_size, bytes_.size());
        return MinimumAbovePremiumFraction{ bytes_.subspan(premium_break_point_end()) };
    }

    MinimumBelowPremiumFraction minimum_below_premium_fraction() const {
        wire::require("SecurityDefinitionMessage", minimum_above_premium_fraction_end() + MinimumBelowPremiumFraction::minimum_size, bytes_.size());
        return MinimumBelowPremiumFraction{ bytes_.subspan(minimum_above_premium_fraction_end()) };
    }

    ExerciseStyle exercise_style() const {
        wire::require("SecurityDefinitionMessage", minimum_below_premium_fraction_end() + 1, bytes_.size());
        return static_cast<ExerciseStyle>(wire::read_u8(at(minimum_below_premium_fraction_end())));
    }

    CurrencyCode currency_code() const {
        wire::require("SecurityDefinitionMessage", exercise_style_end() + CurrencyCode::minimum_size, bytes_.size());
        return CurrencyCode{ bytes_.subspan(exercise_style_end()) };
    }

    UnderlyingSymbol underlying_symbol() const {
        wire::require("SecurityDefinitionMessage", currency_code_end() + UnderlyingSymbol::minimum_size, bytes_.size());
        return UnderlyingSymbol{ bytes_.subspan(currency_code_end()) };
    }

    UnderlyingType underlying_type() const {
        wire::require("SecurityDefinitionMessage", underlying_symbol_end() + UnderlyingType::minimum_size, bytes_.size());
        return UnderlyingType{ bytes_.subspan(underlying_symbol_end()) };
    }

    std::uint32_t contract_size() const {
        wire::require("SecurityDefinitionMessage", underlying_type_end() + 4, bytes_.size());
        return wire::read_u32_be(at(underlying_type_end()));
    }

    std::uint8_t no_legs() const {
        wire::require("SecurityDefinitionMessage", contract_size_end() + 1, bytes_.size());
        return wire::read_u8(at(contract_size_end()));
    }

    view::entries<SecurityDefinitionLeg> security_definition_leg() const { return view::entries<SecurityDefinitionLeg>{ bytes_.subspan(no_legs_end()), wire::count(no_legs()) }; }

    void print(std::ostream& out) const {
        out << "SecurityDefinitionMessage{";
        out << "security_type=";
        security_type().print(out);
        out << ", security_exchange=";
        out << security_exchange();
        out << ", symbol=";
        symbol().print(out);
        out << ", target_location_id=";
        target_location_id().print(out);
        out << ", class_key=";
        out << class_key();
        out << ", security_id=";
        out << security_id();
        out << ", maturity_date=";
        out << maturity_date();
        out << ", price_type=";
        out << static_cast<int>(price_type());
        out << ", strike_price=";
        strike_price().print(out);
        out << ", put_or_call=";
        out << put_or_call();
        out << ", minimum_strike_price_fraction=";
        minimum_strike_price_fraction().print(out);
        out << ", max_strike_price=";
        max_strike_price().print(out);
        out << ", premium_break_point=";
        premium_break_point().print(out);
        out << ", minimum_above_premium_fraction=";
        minimum_above_premium_fraction().print(out);
        out << ", minimum_below_premium_fraction=";
        minimum_below_premium_fraction().print(out);
        out << ", exercise_style=";
        out << exercise_style();
        out << ", currency_code=";
        currency_code().print(out);
        out << ", underlying_symbol=";
        underlying_symbol().print(out);
        out << ", underlying_type=";
        underlying_type().print(out);
        out << ", contract_size=";
        out << contract_size();
        out << ", no_legs=";
        out << static_cast<int>(no_legs());
        out << ", security_definition_leg=";
        print::sequence(out, security_definition_leg());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t security_type_end() const { return 0 + security_type().encoded_size(); }
    std::size_t security_exchange_end() const { return security_type_end() + 1; }
    std::size_t symbol_end() const { return security_exchange_end() + symbol().encoded_size(); }
    std::size_t target_location_id_end() const { return symbol_end() + target_location_id().encoded_size(); }
    std::size_t class_key_end() const { return target_location_id_end() + 4; }
    std::size_t security_id_end() const { return class_key_end() + 4; }
    std::size_t maturity_date_end() const { return security_id_end() + 8; }
    std::size_t price_type_end() const { return maturity_date_end() + 1; }
    std::size_t strike_price_end() const { return price_type_end() + 5; }
    std::size_t put_or_call_end() const { return strike_price_end() + 1; }
    std::size_t minimum_strike_price_fraction_end() const { return put_or_call_end() + 5; }
    std::size_t max_strike_price_end() const { return minimum_strike_price_fraction_end() + 5; }
    std::size_t premium_break_point_end() const { return max_strike_price_end() + 5; }
    std::size_t minimum_above_premium_fraction_end() const { return premium_break_point_end() + 5; }
    std::size_t minimum_below_premium_fraction_end() const { return minimum_above_premium_fraction_end() + 5; }
    std::size_t exercise_style_end() const { return minimum_below_premium_fraction_end() + 1; }
    std::size_t currency_code_end() const { return exercise_style_end() + currency_code().encoded_size(); }
    std::size_t underlying_symbol_end() const { return currency_code_end() + underlying_symbol().encoded_size(); }
    std::size_t underlying_type_end() const { return underlying_symbol_end() + underlying_type().encoded_size(); }
    std::size_t contract_size_end() const { return underlying_type_end() + 4; }
    std::size_t no_legs_end() const { return contract_size_end() + 1; }
    std::size_t security_definition_leg_end() const { return no_legs_end() + security_definition_leg().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityDefinitionMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
