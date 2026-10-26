#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdSecurityTradingStatus.hpp"
#include "../enums/MoneyOrPar.hpp"
#include "../enums/RepoSubType.hpp"
#include "../enums/SecurityUpdateAction.hpp"
#include "../messages/ServerTcpMessage.hpp"
#include "../structs/BrokenDatesGroups.hpp"
#include "../structs/EventsGroups.hpp"
#include "../structs/FeedTypesGroups.hpp"
#include "../structs/InstAttribGroups.hpp"
#include "../structs/LotTypeRulesGroups.hpp"
#include "../structs/RepoRelatedInstrumentsGroups.hpp"
#include "../structs/RepoUnderlyingsGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class ServerTcpMessageVisitor;

// MDInstrumentDefinitionRepo
class ServerPayloadMdInstrumentDefinitionRepo : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::MdInstrumentDefinitionRepo;

    ServerPayloadMdInstrumentDefinitionRepo() = default;
    ServerPayloadMdInstrumentDefinitionRepo(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::uint8_t underlying_product, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, const std::string& currency, const std::string& settl_currency, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, Decimal min_price_increment_ex, Decimal display_factor, const std::string& unit_of_measure, std::optional<Decimal> unit_of_measure_qty, std::optional<Decimal> trading_reference_price, std::optional<std::uint16_t> trading_reference_date, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, const std::string& financial_instrument_full_name, const std::string& party_role_clearing_org, std::optional<std::uint16_t> start_date, std::optional<std::uint16_t> end_date, const std::string& termination_type, RepoSubType repo_sub_type, std::optional<MoneyOrPar> money_or_par, std::uint8_t max_no_of_substitutions, const std::string& price_quote_method, char user_defined_instrument, const std::string& risk_set, const std::string& market_set, std::optional<std::uint64_t> instrument_guid, const std::string& term_code, std::optional<std::uint8_t> broken_date_term_type, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const LotTypeRulesGroups& lot_type_rules_groups, const RepoUnderlyingsGroups& repo_underlyings_groups, const RepoRelatedInstrumentsGroups& repo_related_instruments_groups, const BrokenDatesGroups& broken_dates_groups);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Tot Num Reports Optional: Total number of instruments in the Replay loop. Used on Replay
    // Feed only
    std::optional<std::uint32_t> tot_num_reports_optional() const;
    void set_tot_num_reports_optional(std::optional<std::uint32_t> value);

    // Security Update Action: Last Security update action on Incremental feed, 'D' or 'M' is
    // used when a mid-week deletion or modification (i.e. extension) occurs
    SecurityUpdateAction security_update_action() const;
    void set_security_update_action(SecurityUpdateAction value);

    // Last Update Time: UTC Date and time of last Security Definition add, update or delete on
    // a given Market Data channel
    std::chrono::nanoseconds last_update_time() const;
    void set_last_update_time(std::chrono::nanoseconds value);

    // Md Security Trading Status: Identifies the current trading state of the instrument
    std::optional<MdSecurityTradingStatus> md_security_trading_status() const;
    void set_md_security_trading_status(std::optional<MdSecurityTradingStatus> value);

    // Appl Id: The channel ID as defined in the XML Configuration file
    std::int16_t appl_id() const;
    void set_appl_id(std::int16_t value);

    // Market Segment Id: Identifies the market segment, populated for all CME Globex
    // instruments
    std::uint8_t market_segment_id() const;
    void set_market_segment_id(std::uint8_t value);

    // Underlying Product: Product complex
    std::uint8_t underlying_product() const;
    void set_underlying_product(std::uint8_t value);

    // Security Exchange: Exchange used to identify a security
    const std::string& security_exchange() const;
    std::string& security_exchange();
    void set_security_exchange(const std::string& value);

    // Security Group: Security Group
    const std::string& security_group() const;
    std::string& security_group();
    void set_security_group(const std::string& value);

    // Asset: Product Code within Security Group specified
    const std::string& asset() const;
    std::string& asset();
    void set_asset(const std::string& value);

    // Symbol: Instrument Name or Symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Security Type: Security Type
    const std::string& security_type() const;
    std::string& security_type();
    void set_security_type(const std::string& value);

    // Cfi Code: ISO standard instrument categorization code
    const std::string& cfi_code() const;
    std::string& cfi_code();
    void set_cfi_code(const std::string& value);

    // Currency: Identifies currency used for price
    const std::string& currency() const;
    std::string& currency();
    void set_currency(const std::string& value);

    // Settl Currency: Identifies currency used for settlement, if different from trading
    // currency
    const std::string& settl_currency() const;
    std::string& settl_currency();
    void set_settl_currency(const std::string& value);

    // Match Algorithm: Matching algorithm
    char match_algorithm() const;
    void set_match_algorithm(char value);

    // Min Trade Vol: The minimum trading volume for a security
    std::uint32_t min_trade_vol() const;
    void set_min_trade_vol(std::uint32_t value);

    // Max Trade Vol: The maximum trading volume for a security
    std::uint32_t max_trade_vol() const;
    void set_max_trade_vol(std::uint32_t value);

    // Min Price Increment Ex: Minimum constant tick for the instrument, sent only if
    // instrument is non-VTT (Variable Tick table) eligible
    Decimal min_price_increment_ex() const;
    void set_min_price_increment_ex(Decimal value);

    // Display Factor: Contains the multiplier to convert the CME Globex display price to the
    // conventional price
    Decimal display_factor() const;
    void set_display_factor(Decimal value);

    // Unit Of Measure: Unit of measure for the products' original contract size. This will be
    // populated for all products listed on CME Globex
    const std::string& unit_of_measure() const;
    std::string& unit_of_measure();
    void set_unit_of_measure(const std::string& value);

    // Unit Of Measure Qty: This field contains the contract size for each instrument. Used in
    // combination with tag 996-UnitofMeasure
    std::optional<Decimal> unit_of_measure_qty() const;
    void set_unit_of_measure_qty(std::optional<Decimal> value);

    // Trading Reference Price: Reference price for prelisted instruments or the last
    // calculated Settlement whether it be Theoretical, Preliminary or a Final Settle of the
    // session.
    std::optional<Decimal> trading_reference_price() const;
    void set_trading_reference_price(std::optional<Decimal> value);

    // Trading Reference Date: Indicates session date corresponding to the settlement price in
    // tag 1150-TradingReferencePrice
    std::optional<std::uint16_t> trading_reference_date() const;
    void set_trading_reference_date(std::optional<std::uint16_t> value);

    // High Limit Price: Upper price threshold for the instrument
    std::optional<Decimal> high_limit_price() const;
    void set_high_limit_price(std::optional<Decimal> value);

    // Low Limit Price: Lower price threshold for the instrument
    std::optional<Decimal> low_limit_price() const;
    void set_low_limit_price(std::optional<Decimal> value);

    // Max Price Variation: Differential value for price banding
    std::optional<Decimal> max_price_variation() const;
    void set_max_price_variation(std::optional<Decimal> value);

    // Financial Instrument Full Name: Long name of the instrument
    const std::string& financial_instrument_full_name() const;
    std::string& financial_instrument_full_name();
    void set_financial_instrument_full_name(const std::string& value);

    // Party Role Clearing Org: Clearing organization
    const std::string& party_role_clearing_org() const;
    std::string& party_role_clearing_org();
    void set_party_role_clearing_org(const std::string& value);

    // Start Date: Start date of a financing deal, i.e. the date the buyer pays the seller cash
    // and takes control of the collateral
    std::optional<std::uint16_t> start_date() const;
    void set_start_date(std::optional<std::uint16_t> value);

    // End Date: End date of a financing deal, i.e. the date the seller reimburses the buyer
    // and takes back control of the collateral
    std::optional<std::uint16_t> end_date() const;
    void set_end_date(std::optional<std::uint16_t> value);

    // Termination Type: For Repos the timing or method for terminating the agreement. Term
    // code
    const std::string& termination_type() const;
    std::string& termination_type();
    void set_termination_type(const std::string& value);

    // Repo Sub Type: Repo Sub Security Type
    RepoSubType repo_sub_type() const;
    void set_repo_sub_type(RepoSubType value);

    // Money Or Par: Money or Par indicates if the GC is filled by par amount or by money
    // amount
    std::optional<MoneyOrPar> money_or_par() const;
    void set_money_or_par(std::optional<MoneyOrPar> value);

    // Max No Of Substitutions: Max number of substitutions allowed. The value of 0 indicates
    // that substitutions are not allowed
    std::uint8_t max_no_of_substitutions() const;
    void set_max_no_of_substitutions(std::uint8_t value);

    // Price Quote Method: Price quotation method
    const std::string& price_quote_method() const;
    std::string& price_quote_method();
    void set_price_quote_method(const std::string& value);

    // User Defined Instrument: User-defined instruments flag
    char user_defined_instrument() const;
    void set_user_defined_instrument(char value);

    // Risk Set: Risk Set identifies the list of instruments sharing credit limits set up
    const std::string& risk_set() const;
    std::string& risk_set();
    void set_risk_set(const std::string& value);

    // Market Set: Market Set defines the bilateral relationship and Self Match Prevention
    // configuration for eligible markets
    const std::string& market_set() const;
    std::string& market_set();
    void set_market_set(const std::string& value);

    // Instrument Guid: External unique instrument ID
    std::optional<std::uint64_t> instrument_guid() const;
    void set_instrument_guid(std::optional<std::uint64_t> value);

    // Term Code: Full Repo Term Code
    const std::string& term_code() const;
    std::string& term_code();
    void set_term_code(const std::string& value);

    // Broken Date Term Type: Optionally used in tailor made repo contracts and defines the
    // type of broken dates as requested by trader. Null = Not applicable, 0 = Custom, 1 =
    // Quarterly, 2 = Monthly
    std::optional<std::uint8_t> broken_date_term_type() const;
    void set_broken_date_term_type(std::optional<std::uint8_t> value);

    // Events Groups: NoEvents Block
    const EventsGroups& events_groups() const;
    EventsGroups& events_groups();
    void set_events_groups(const EventsGroups& value);

    // Feed Types Groups: NoMDFeedTypes Block
    const FeedTypesGroups& feed_types_groups() const;
    FeedTypesGroups& feed_types_groups();
    void set_feed_types_groups(const FeedTypesGroups& value);

    // Inst Attrib Groups: NoInstAttrib Block
    const InstAttribGroups& inst_attrib_groups() const;
    InstAttribGroups& inst_attrib_groups();
    void set_inst_attrib_groups(const InstAttribGroups& value);

    // Lot Type Rules Groups: NoLotTypeRules Block
    const LotTypeRulesGroups& lot_type_rules_groups() const;
    LotTypeRulesGroups& lot_type_rules_groups();
    void set_lot_type_rules_groups(const LotTypeRulesGroups& value);

    // Repo Underlyings Groups: NoUnderlyings Block
    const RepoUnderlyingsGroups& repo_underlyings_groups() const;
    RepoUnderlyingsGroups& repo_underlyings_groups();
    void set_repo_underlyings_groups(const RepoUnderlyingsGroups& value);

    // Repo Related Instruments Groups: NoRelatedInstruments Block
    const RepoRelatedInstrumentsGroups& repo_related_instruments_groups() const;
    RepoRelatedInstrumentsGroups& repo_related_instruments_groups();
    void set_repo_related_instruments_groups(const RepoRelatedInstrumentsGroups& value);

    // Broken Dates Groups: NoBrokenDates Block
    const BrokenDatesGroups& broken_dates_groups() const;
    BrokenDatesGroups& broken_dates_groups();
    void set_broken_dates_groups(const BrokenDatesGroups& value);

    // ServerTcpMessage
    ServerTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ServerTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ServerTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ServerTcpMessage& other) const override;

    bool operator==(const ServerPayloadMdInstrumentDefinitionRepo& other) const;
    bool operator!=(const ServerPayloadMdInstrumentDefinitionRepo& other) const;

  private:
    MatchEventIndicator match_event_indicator_{};
    std::optional<std::uint32_t> tot_num_reports_optional_{};
    SecurityUpdateAction security_update_action_{};
    std::chrono::nanoseconds last_update_time_{};
    std::optional<MdSecurityTradingStatus> md_security_trading_status_{};
    std::int16_t appl_id_{};
    std::uint8_t market_segment_id_{};
    std::uint8_t underlying_product_{};
    std::string security_exchange_{};
    std::string security_group_{};
    std::string asset_{};
    std::string symbol_{};
    std::int32_t security_id_{};
    std::string security_type_{};
    std::string cfi_code_{};
    std::string currency_{};
    std::string settl_currency_{};
    char match_algorithm_{};
    std::uint32_t min_trade_vol_{};
    std::uint32_t max_trade_vol_{};
    Decimal min_price_increment_ex_{ 0, -9 };
    Decimal display_factor_{ 0, -9 };
    std::string unit_of_measure_{};
    std::optional<Decimal> unit_of_measure_qty_{};
    std::optional<Decimal> trading_reference_price_{};
    std::optional<std::uint16_t> trading_reference_date_{};
    std::optional<Decimal> high_limit_price_{};
    std::optional<Decimal> low_limit_price_{};
    std::optional<Decimal> max_price_variation_{};
    std::string financial_instrument_full_name_{};
    std::string party_role_clearing_org_{};
    std::optional<std::uint16_t> start_date_{};
    std::optional<std::uint16_t> end_date_{};
    std::string termination_type_{};
    RepoSubType repo_sub_type_{};
    std::optional<MoneyOrPar> money_or_par_{};
    std::uint8_t max_no_of_substitutions_{};
    std::string price_quote_method_{};
    char user_defined_instrument_{};
    std::string risk_set_{};
    std::string market_set_{};
    std::optional<std::uint64_t> instrument_guid_{};
    std::string term_code_{};
    std::optional<std::uint8_t> broken_date_term_type_{};
    EventsGroups events_groups_{};
    FeedTypesGroups feed_types_groups_{};
    InstAttribGroups inst_attrib_groups_{};
    LotTypeRulesGroups lot_type_rules_groups_{};
    RepoUnderlyingsGroups repo_underlyings_groups_{};
    RepoRelatedInstrumentsGroups repo_related_instruments_groups_{};
    BrokenDatesGroups broken_dates_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
