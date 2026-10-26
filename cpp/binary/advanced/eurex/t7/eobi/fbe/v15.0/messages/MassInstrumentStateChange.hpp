#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/InstrumentScopeProductComplex.hpp"
#include "../types/SecurityMassStatus.hpp"
#include "../types/SecurityMassTradingStatus.hpp"
#include "../types/MassMarketCondition.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/SecurityMassTradingEvent.hpp"
#include "../types/MassSoldOutIndicator.hpp"
#include "../types/TesSecurityMassStatus.hpp"
#include "../types/TransactTime.hpp"
#include "../types/LastFragment.hpp"
#include "../types/NoRelatedSym.hpp"
#include "../types/Pad6.hpp"
#include "../structs/SecMassStatGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

// Mass Instrument State Change
struct mass_instrument_state_change {

    struct fields_type {
        fbe_eobi::instrument_scope_product_complex instrument_scope_product_complex;
        fbe_eobi::security_mass_status security_mass_status;
        fbe_eobi::security_mass_trading_status security_mass_trading_status;
        fbe_eobi::mass_market_condition mass_market_condition;
        fbe_eobi::fast_market_indicator fast_market_indicator;
        fbe_eobi::security_mass_trading_event security_mass_trading_event;
        fbe_eobi::mass_sold_out_indicator mass_sold_out_indicator;
        fbe_eobi::tes_security_mass_status tes_security_mass_status;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::last_fragment last_fragment;
        fbe_eobi::no_related_sym no_related_sym;
        fbe_eobi::pad6 pad6;
        fbe_eobi::sec_mass_stat_grp_comp sec_mass_stat_grp_comp;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::mass_instrument_state_change, {}};

    fields_type fields;

    // parse method
    static mass_instrument_state_change* parse(std::byte* buffer) {
        return reinterpret_cast<mass_instrument_state_change*>(buffer);
    }

    // parse method const
    static const mass_instrument_state_change* parse(const std::byte* buffer) {
        return reinterpret_cast<const mass_instrument_state_change*>(buffer);
    }

};

// layout verification
static_assert(offsetof(mass_instrument_state_change::fields_type, instrument_scope_product_complex) == 0, "unexpected offset of mass_instrument_state_change::fields_type::instrument_scope_product_complex");
static_assert(offsetof(mass_instrument_state_change::fields_type, security_mass_status) == 1, "unexpected offset of mass_instrument_state_change::fields_type::security_mass_status");
static_assert(offsetof(mass_instrument_state_change::fields_type, security_mass_trading_status) == 2, "unexpected offset of mass_instrument_state_change::fields_type::security_mass_trading_status");
static_assert(offsetof(mass_instrument_state_change::fields_type, mass_market_condition) == 3, "unexpected offset of mass_instrument_state_change::fields_type::mass_market_condition");
static_assert(offsetof(mass_instrument_state_change::fields_type, fast_market_indicator) == 4, "unexpected offset of mass_instrument_state_change::fields_type::fast_market_indicator");
static_assert(offsetof(mass_instrument_state_change::fields_type, security_mass_trading_event) == 5, "unexpected offset of mass_instrument_state_change::fields_type::security_mass_trading_event");
static_assert(offsetof(mass_instrument_state_change::fields_type, mass_sold_out_indicator) == 6, "unexpected offset of mass_instrument_state_change::fields_type::mass_sold_out_indicator");
static_assert(offsetof(mass_instrument_state_change::fields_type, tes_security_mass_status) == 7, "unexpected offset of mass_instrument_state_change::fields_type::tes_security_mass_status");
static_assert(offsetof(mass_instrument_state_change::fields_type, transact_time) == 8, "unexpected offset of mass_instrument_state_change::fields_type::transact_time");
static_assert(offsetof(mass_instrument_state_change::fields_type, last_fragment) == 16, "unexpected offset of mass_instrument_state_change::fields_type::last_fragment");
static_assert(offsetof(mass_instrument_state_change::fields_type, no_related_sym) == 17, "unexpected offset of mass_instrument_state_change::fields_type::no_related_sym");
static_assert(offsetof(mass_instrument_state_change::fields_type, pad6) == 18, "unexpected offset of mass_instrument_state_change::fields_type::pad6");
static_assert(offsetof(mass_instrument_state_change::fields_type, sec_mass_stat_grp_comp) == 24, "unexpected offset of mass_instrument_state_change::fields_type::sec_mass_stat_grp_comp");
static_assert(sizeof(mass_instrument_state_change::fields_type) == 56, "unexpected sizeof mass_instrument_state_change::fields_type");
static_assert(sizeof(mass_instrument_state_change) == sizeof(fbe_eobi::message_header_comp) + 56, "unexpected sizeof mass_instrument_state_change");

#pragma pack(pop)
}
