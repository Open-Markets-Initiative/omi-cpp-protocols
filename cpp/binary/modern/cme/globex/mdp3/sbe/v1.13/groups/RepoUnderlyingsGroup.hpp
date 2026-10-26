#pragma once

#include "../types/UnderlyingSymbol.hpp"
#include "../types/UnderlyingSecurityIdOptional.hpp"
#include "../types/UnderlyingSecurityAltId.hpp"
#include "../types/UnderlyingSecurityAltIdSource.hpp"
#include "../types/UnderlyingFinancialInstrumentFullName.hpp"
#include "../types/UnderlyingSecurityType.hpp"
#include "../types/UnderlyingCountryOfIssue.hpp"
#include "../types/UnderlyingIssuer.hpp"
#include "../types/UnderlyingMaxLifeTime.hpp"
#include "../types/UnderlyingMinDaysToMaturity.hpp"
#include "../types/UnderlyingInstrumentGuidOptional.hpp"
#include "../types/UnderlyingMaturityDate.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct RepoUnderlyingsGroup {

    UnderlyingSymbol underlying_symbol;
    UnderlyingSecurityIdOptional underlying_security_id_optional;
    UnderlyingSecurityAltId underlying_security_alt_id;
    UnderlyingSecurityAltIdSource underlying_security_alt_id_source;
    UnderlyingFinancialInstrumentFullName underlying_financial_instrument_full_name;
    UnderlyingSecurityType underlying_security_type;
    UnderlyingCountryOfIssue underlying_country_of_issue;
    UnderlyingIssuer underlying_issuer;
    UnderlyingMaxLifeTime underlying_max_life_time;
    UnderlyingMinDaysToMaturity underlying_min_days_to_maturity;
    UnderlyingInstrumentGuidOptional underlying_instrument_guid_optional;
    UnderlyingMaturityDate underlying_maturity_date;

    // parse method
    static RepoUnderlyingsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<RepoUnderlyingsGroup*>(buffer);
    }

    // parse method const
    static const RepoUnderlyingsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const RepoUnderlyingsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
