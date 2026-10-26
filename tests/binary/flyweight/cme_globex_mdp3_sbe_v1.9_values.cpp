// Cme.Globex.Mdp3.Sbe.v1.9 canonical values, through the Flyweight reader: every value Flyweight reads
// from each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/flyweight/cme/globex/mdp3/sbe/v1.9/definitions.hpp"

namespace protocol = ::cme::globex::mdp3::sbe::v1_9;

namespace {

// The messages Mktdata Payload selects, their values set in the entry of the message holding it
struct MktdataPayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::ChannelReset& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.channelreset";
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.channelreset.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::AdminLogin& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.adminlogin";
        values[entry + ".payload.mktdatamessage.mktdatapayload.adminlogin.heartbtint"] = canonical::number(message.heart_bt_int());
    }

    void on(const protocol::AdminLogout& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.adminlogout";
        values[entry + ".payload.mktdatamessage.mktdatapayload.adminlogout.text"] = canonical::text(std::string(message.text()), '\0', false);
    }

    void on(const protocol::MdInstrumentDefinitionFutureLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.totnumreportsoptional"] = (message.tot_num_reports_optional().has_value() ? canonical::number((*message.tot_num_reports_optional())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.securityupdateaction"] = canonical::text(canonical::character(message.security_update_action()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.lastupdatetime"] = canonical::number(message.last_update_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.mdsecuritytradingstatus"] = (message.md_security_trading_status().has_value() ? canonical::number((*message.md_security_trading_status())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.applid"] = canonical::number(message.appl_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.marketsegmentid"] = canonical::number(message.market_segment_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.underlyingproduct"] = canonical::number(message.underlying_product());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.securityexchange"] = canonical::text(std::string(message.security_exchange()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.securitygroup"] = canonical::text(std::string(message.security_group()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.asset"] = canonical::text(std::string(message.asset()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.securitytype"] = canonical::text(std::string(message.security_type()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.cficode"] = canonical::text(std::string(message.cfi_code()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maturitymonthyear.year"] = (message.maturity_month_year().year().has_value() ? canonical::number((*message.maturity_month_year().year())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maturitymonthyear.month"] = (message.maturity_month_year().month().has_value() ? canonical::number((*message.maturity_month_year().month())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maturitymonthyear.day"] = (message.maturity_month_year().day().has_value() ? canonical::number((*message.maturity_month_year().day())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maturitymonthyear.week"] = (message.maturity_month_year().week().has_value() ? canonical::number((*message.maturity_month_year().week())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.currency"] = canonical::text(std::string(message.currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlcurrency"] = canonical::text(std::string(message.settl_currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.matchalgorithm"] = canonical::text(canonical::character(message.match_algorithm()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.mintradevol"] = canonical::number(message.min_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maxtradevol"] = canonical::number(message.max_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.minpriceincrement"] = canonical::scaled(message.min_price_increment().mantissa(), message.min_price_increment().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.displayfactor"] = canonical::scaled(message.display_factor().mantissa(), message.display_factor().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.mainfraction"] = (message.main_fraction().has_value() ? canonical::number((*message.main_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.subfraction"] = (message.sub_fraction().has_value() ? canonical::number((*message.sub_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.pricedisplayformat"] = (message.price_display_format().has_value() ? canonical::number((*message.price_display_format())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.unitofmeasureqty"] = (message.unit_of_measure_qty().has_value() ? canonical::scaled((*message.unit_of_measure_qty()).mantissa(), (*message.unit_of_measure_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.tradingreferenceprice"] = (message.trading_reference_price().has_value() ? canonical::scaled((*message.trading_reference_price()).mantissa(), (*message.trading_reference_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().reserved_bits()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_5()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_6()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.openinterestqty"] = (message.open_interest_qty().has_value() ? canonical::number((*message.open_interest_qty())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.clearedvolume"] = (message.cleared_volume().has_value() ? canonical::number((*message.cleared_volume())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.highlimitprice"] = (message.high_limit_price().has_value() ? canonical::scaled((*message.high_limit_price()).mantissa(), (*message.high_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.lowlimitprice"] = (message.low_limit_price().has_value() ? canonical::scaled((*message.low_limit_price()).mantissa(), (*message.low_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.maxpricevariation"] = (message.max_price_variation().has_value() ? canonical::scaled((*message.max_price_variation()).mantissa(), (*message.max_price_variation()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.decayquantity"] = (message.decay_quantity().has_value() ? canonical::number((*message.decay_quantity())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.decaystartdate"] = (message.decay_start_date().has_value() ? canonical::number((*message.decay_start_date())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.originalcontractsize"] = (message.original_contract_size().has_value() ? canonical::number((*message.original_contract_size())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.contractmultiplier"] = (message.contract_multiplier().has_value() ? canonical::number((*message.contract_multiplier())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.contractmultiplierunit"] = (message.contract_multiplier_unit().has_value() ? canonical::number((*message.contract_multiplier_unit())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.flowscheduletype"] = (message.flow_schedule_type().has_value() ? canonical::number((*message.flow_schedule_type())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.minpriceincrementamount"] = (message.min_price_increment_amount().has_value() ? canonical::scaled((*message.min_price_increment_amount()).mantissa(), (*message.min_price_increment_amount()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.userdefinedinstrument"] = canonical::text(canonical::character(message.user_defined_instrument()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuturelegacy.tradingreferencedate"] = (message.trading_reference_date().has_value() ? canonical::number((*message.trading_reference_date())) : canonical::absent());
    }

    void on(const protocol::MdInstrumentDefinitionSpreadLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.totnumreportsoptional"] = (message.tot_num_reports_optional().has_value() ? canonical::number((*message.tot_num_reports_optional())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securityupdateaction"] = canonical::text(canonical::character(message.security_update_action()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.lastupdatetime"] = canonical::number(message.last_update_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.mdsecuritytradingstatus"] = (message.md_security_trading_status().has_value() ? canonical::number((*message.md_security_trading_status())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.applid"] = canonical::number(message.appl_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.marketsegmentid"] = canonical::number(message.market_segment_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.underlyingproductoptional"] = (message.underlying_product_optional().has_value() ? canonical::number((*message.underlying_product_optional())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securityexchange"] = canonical::text(std::string(message.security_exchange()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securitygroup"] = canonical::text(std::string(message.security_group()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.asset"] = canonical::text(std::string(message.asset()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securitytype"] = canonical::text(std::string(message.security_type()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.cficode"] = canonical::text(std::string(message.cfi_code()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maturitymonthyear.year"] = (message.maturity_month_year().year().has_value() ? canonical::number((*message.maturity_month_year().year())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maturitymonthyear.month"] = (message.maturity_month_year().month().has_value() ? canonical::number((*message.maturity_month_year().month())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maturitymonthyear.day"] = (message.maturity_month_year().day().has_value() ? canonical::number((*message.maturity_month_year().day())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maturitymonthyear.week"] = (message.maturity_month_year().week().has_value() ? canonical::number((*message.maturity_month_year().week())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.currency"] = canonical::text(std::string(message.currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.securitysubtype"] = canonical::text(std::string(message.security_sub_type()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.userdefinedinstrument"] = canonical::text(canonical::character(message.user_defined_instrument()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.matchalgorithm"] = canonical::text(canonical::character(message.match_algorithm()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.mintradevol"] = canonical::number(message.min_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maxtradevol"] = canonical::number(message.max_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.minpriceincrement"] = canonical::scaled(message.min_price_increment().mantissa(), message.min_price_increment().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.displayfactor"] = canonical::scaled(message.display_factor().mantissa(), message.display_factor().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.pricedisplayformat"] = (message.price_display_format().has_value() ? canonical::number((*message.price_display_format())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.priceratio"] = (message.price_ratio().has_value() ? canonical::scaled((*message.price_ratio()).mantissa(), (*message.price_ratio()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.tickrule"] = (message.tick_rule().has_value() ? canonical::number((*message.tick_rule())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.tradingreferenceprice"] = (message.trading_reference_price().has_value() ? canonical::scaled((*message.trading_reference_price()).mantissa(), (*message.trading_reference_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().reserved_bits()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_5()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_6()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.openinterestqty"] = (message.open_interest_qty().has_value() ? canonical::number((*message.open_interest_qty())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.clearedvolume"] = (message.cleared_volume().has_value() ? canonical::number((*message.cleared_volume())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.highlimitprice"] = (message.high_limit_price().has_value() ? canonical::scaled((*message.high_limit_price()).mantissa(), (*message.high_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.lowlimitprice"] = (message.low_limit_price().has_value() ? canonical::scaled((*message.low_limit_price()).mantissa(), (*message.low_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.maxpricevariation"] = (message.max_price_variation().has_value() ? canonical::scaled((*message.max_price_variation()).mantissa(), (*message.max_price_variation()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.mainfraction"] = (message.main_fraction().has_value() ? canonical::number((*message.main_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.subfraction"] = (message.sub_fraction().has_value() ? canonical::number((*message.sub_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspreadlegacy.tradingreferencedate"] = (message.trading_reference_date().has_value() ? canonical::number((*message.trading_reference_date())) : canonical::absent());
    }

    void on(const protocol::SecurityStatus& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.securitystatus";
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securitygroup"] = canonical::text(std::string(message.security_group()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.asset"] = canonical::text(std::string(message.asset()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securityidoptional"] = (message.security_id_optional().has_value() ? canonical::number((*message.security_id_optional())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.tradedate"] = (message.trade_date().has_value() ? canonical::number((*message.trade_date())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securitytradingstatus"] = (message.security_trading_status().has_value() ? canonical::number((*message.security_trading_status())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.haltreason"] = canonical::number(message.halt_reason());
        values[entry + ".payload.mktdatamessage.mktdatapayload.securitystatus.securitytradingevent"] = canonical::number(message.security_trading_event());
    }

    void on(const protocol::MdIncrementalRefreshBookLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbooklegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdIncrementalRefreshDailyStatisticsLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatisticslegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdIncrementalRefreshLimitsBandingLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbandinglegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdIncrementalRefreshSessionStatisticsLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatisticslegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdIncrementalRefreshVolume& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshvolume.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::SnapshotFullRefreshLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.lastmsgseqnumprocessed"] = canonical::number(message.last_msg_seq_num_processed());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.totnumreports"] = canonical::number(message.tot_num_reports());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.rptseq"] = canonical::number(message.rpt_seq());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.lastupdatetime"] = canonical::number(message.last_update_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.tradedate"] = (message.trade_date().has_value() ? canonical::number((*message.trade_date())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.mdsecuritytradingstatus"] = (message.md_security_trading_status().has_value() ? canonical::number((*message.md_security_trading_status())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.highlimitprice"] = (message.high_limit_price().has_value() ? canonical::scaled((*message.high_limit_price()).mantissa(), (*message.high_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.lowlimitprice"] = (message.low_limit_price().has_value() ? canonical::scaled((*message.low_limit_price()).mantissa(), (*message.low_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshlegacy.maxpricevariation"] = (message.max_price_variation().has_value() ? canonical::scaled((*message.max_price_variation()).mantissa(), (*message.max_price_variation()).exponent()) : canonical::absent());
    }

    void on(const protocol::QuoteRequest& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.quoterequest";
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.quotereqid"] = canonical::text(std::string(message.quote_req_id()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.quoterequest.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdInstrumentDefinitionOptionLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.totnumreportsoptional"] = (message.tot_num_reports_optional().has_value() ? canonical::number((*message.tot_num_reports_optional())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.securityupdateaction"] = canonical::text(canonical::character(message.security_update_action()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.lastupdatetime"] = canonical::number(message.last_update_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.mdsecuritytradingstatus"] = (message.md_security_trading_status().has_value() ? canonical::number((*message.md_security_trading_status())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.applid"] = canonical::number(message.appl_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.marketsegmentid"] = canonical::number(message.market_segment_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.underlyingproduct"] = canonical::number(message.underlying_product());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.securityexchange"] = canonical::text(std::string(message.security_exchange()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.securitygroup"] = canonical::text(std::string(message.security_group()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.asset"] = canonical::text(std::string(message.asset()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.securitytype"] = canonical::text(std::string(message.security_type()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.cficode"] = canonical::text(std::string(message.cfi_code()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.putorcall"] = canonical::number(message.put_or_call());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.maturitymonthyear.year"] = (message.maturity_month_year().year().has_value() ? canonical::number((*message.maturity_month_year().year())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.maturitymonthyear.month"] = (message.maturity_month_year().month().has_value() ? canonical::number((*message.maturity_month_year().month())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.maturitymonthyear.day"] = (message.maturity_month_year().day().has_value() ? canonical::number((*message.maturity_month_year().day())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.maturitymonthyear.week"] = (message.maturity_month_year().week().has_value() ? canonical::number((*message.maturity_month_year().week())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.currency"] = canonical::text(std::string(message.currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.strikeprice"] = (message.strike_price().has_value() ? canonical::scaled((*message.strike_price()).mantissa(), (*message.strike_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.strikecurrency"] = canonical::text(std::string(message.strike_currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlcurrency"] = canonical::text(std::string(message.settl_currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.mincabprice"] = (message.min_cab_price().has_value() ? canonical::scaled((*message.min_cab_price()).mantissa(), (*message.min_cab_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.matchalgorithm"] = canonical::text(canonical::character(message.match_algorithm()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.mintradevol"] = canonical::number(message.min_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.maxtradevol"] = canonical::number(message.max_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.minpriceincrementoptional"] = (message.min_price_increment_optional().has_value() ? canonical::scaled((*message.min_price_increment_optional()).mantissa(), (*message.min_price_increment_optional()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.minpriceincrementamount"] = (message.min_price_increment_amount().has_value() ? canonical::scaled((*message.min_price_increment_amount()).mantissa(), (*message.min_price_increment_amount()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.displayfactor"] = canonical::scaled(message.display_factor().mantissa(), message.display_factor().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.tickrule"] = (message.tick_rule().has_value() ? canonical::number((*message.tick_rule())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.mainfraction"] = (message.main_fraction().has_value() ? canonical::number((*message.main_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.subfraction"] = (message.sub_fraction().has_value() ? canonical::number((*message.sub_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.pricedisplayformat"] = (message.price_display_format().has_value() ? canonical::number((*message.price_display_format())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.unitofmeasureqty"] = (message.unit_of_measure_qty().has_value() ? canonical::scaled((*message.unit_of_measure_qty()).mantissa(), (*message.unit_of_measure_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.tradingreferenceprice"] = (message.trading_reference_price().has_value() ? canonical::scaled((*message.trading_reference_price()).mantissa(), (*message.trading_reference_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().reserved_bits()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_5()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_6()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.clearedvolume"] = (message.cleared_volume().has_value() ? canonical::number((*message.cleared_volume())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.openinterestqty"] = (message.open_interest_qty().has_value() ? canonical::number((*message.open_interest_qty())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.lowlimitprice"] = (message.low_limit_price().has_value() ? canonical::scaled((*message.low_limit_price()).mantissa(), (*message.low_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.highlimitprice"] = (message.high_limit_price().has_value() ? canonical::scaled((*message.high_limit_price()).mantissa(), (*message.high_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.userdefinedinstrument"] = canonical::text(canonical::character(message.user_defined_instrument()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoptionlegacy.tradingreferencedate"] = (message.trading_reference_date().has_value() ? canonical::number((*message.trading_reference_date())) : canonical::absent());
    }

    void on(const protocol::MdIncrementalRefreshTradeSummaryLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummarylegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdIncrementalRefreshOrderBookLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbooklegacy.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::SnapshotFullRefreshOrderBookLegacy& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy";
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.lastmsgseqnumprocessed"] = canonical::number(message.last_msg_seq_num_processed());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.totnumreports"] = canonical::number(message.tot_num_reports());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.nochunks"] = canonical::number(message.no_chunks());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.currentchunk"] = canonical::number(message.current_chunk());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbooklegacy.transacttime"] = canonical::number(message.transact_time());
    }

    void on(const protocol::MdIncrementalRefreshBook& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshbook.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdIncrementalRefreshOrderBook& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshorderbook.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdIncrementalRefreshTradeSummary& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtradesummary.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdIncrementalRefreshDailyStatistics& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshdailystatistics.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdIncrementalRefreshLimitsBanding& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshlimitsbanding.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::MdIncrementalRefreshSessionStatistics& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshsessionstatistics.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
    }

    void on(const protocol::SnapshotFullRefresh& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.snapshotfullrefresh";
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lastmsgseqnumprocessed"] = canonical::number(message.last_msg_seq_num_processed());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.totnumreports"] = canonical::number(message.tot_num_reports());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.rptseq"] = canonical::number(message.rpt_seq());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lastupdatetime"] = canonical::number(message.last_update_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.tradedate"] = (message.trade_date().has_value() ? canonical::number((*message.trade_date())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.mdsecuritytradingstatus"] = (message.md_security_trading_status().has_value() ? canonical::number((*message.md_security_trading_status())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.highlimitpriceex"] = (message.high_limit_price_ex().has_value() ? canonical::scaled((*message.high_limit_price_ex()).mantissa(), (*message.high_limit_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lowlimitpriceex"] = (message.low_limit_price_ex().has_value() ? canonical::scaled((*message.low_limit_price_ex()).mantissa(), (*message.low_limit_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.maxpricevariationex"] = (message.max_price_variation_ex().has_value() ? canonical::scaled((*message.max_price_variation_ex()).mantissa(), (*message.max_price_variation_ex()).exponent()) : canonical::absent());
    }

    void on(const protocol::SnapshotFullRefreshOrderBook& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook";
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.lastmsgseqnumprocessed"] = canonical::number(message.last_msg_seq_num_processed());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.totnumreports"] = canonical::number(message.tot_num_reports());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.nochunks"] = canonical::number(message.no_chunks());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.currentchunk"] = canonical::number(message.current_chunk());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.transacttime"] = canonical::number(message.transact_time());
    }

    void on(const protocol::MdInstrumentDefinitionFuture& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.totnumreportsoptional"] = (message.tot_num_reports_optional().has_value() ? canonical::number((*message.tot_num_reports_optional())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securityupdateaction"] = canonical::text(canonical::character(message.security_update_action()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.lastupdatetime"] = canonical::number(message.last_update_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mdsecuritytradingstatus"] = (message.md_security_trading_status().has_value() ? canonical::number((*message.md_security_trading_status())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.applid"] = canonical::number(message.appl_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.marketsegmentid"] = canonical::number(message.market_segment_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.underlyingproduct"] = canonical::number(message.underlying_product());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securityexchange"] = canonical::text(std::string(message.security_exchange()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securitygroup"] = canonical::text(std::string(message.security_group()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.asset"] = canonical::text(std::string(message.asset()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.securitytype"] = canonical::text(std::string(message.security_type()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.cficode"] = canonical::text(std::string(message.cfi_code()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.year"] = (message.maturity_month_year().year().has_value() ? canonical::number((*message.maturity_month_year().year())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.month"] = (message.maturity_month_year().month().has_value() ? canonical::number((*message.maturity_month_year().month())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.day"] = (message.maturity_month_year().day().has_value() ? canonical::number((*message.maturity_month_year().day())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maturitymonthyear.week"] = (message.maturity_month_year().week().has_value() ? canonical::number((*message.maturity_month_year().week())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.currency"] = canonical::text(std::string(message.currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlcurrency"] = canonical::text(std::string(message.settl_currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.matchalgorithm"] = canonical::text(canonical::character(message.match_algorithm()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mintradevol"] = canonical::number(message.min_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maxtradevol"] = canonical::number(message.max_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.minpriceincrementex"] = canonical::scaled(message.min_price_increment_ex().mantissa(), message.min_price_increment_ex().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.displayfactorex"] = canonical::scaled(message.display_factor_ex().mantissa(), message.display_factor_ex().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mainfraction"] = (message.main_fraction().has_value() ? canonical::number((*message.main_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.subfraction"] = (message.sub_fraction().has_value() ? canonical::number((*message.sub_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.pricedisplayformat"] = (message.price_display_format().has_value() ? canonical::number((*message.price_display_format())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.unitofmeasureqtyex"] = (message.unit_of_measure_qty_ex().has_value() ? canonical::scaled((*message.unit_of_measure_qty_ex()).mantissa(), (*message.unit_of_measure_qty_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.tradingreferencepriceex"] = (message.trading_reference_price_ex().has_value() ? canonical::scaled((*message.trading_reference_price_ex()).mantissa(), (*message.trading_reference_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().reserved_bits()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_5()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_6()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.openinterestqty"] = (message.open_interest_qty().has_value() ? canonical::number((*message.open_interest_qty())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.clearedvolume"] = (message.cleared_volume().has_value() ? canonical::number((*message.cleared_volume())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.highlimitpriceex"] = (message.high_limit_price_ex().has_value() ? canonical::scaled((*message.high_limit_price_ex()).mantissa(), (*message.high_limit_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.lowlimitpriceex"] = (message.low_limit_price_ex().has_value() ? canonical::scaled((*message.low_limit_price_ex()).mantissa(), (*message.low_limit_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maxpricevariationex"] = (message.max_price_variation_ex().has_value() ? canonical::scaled((*message.max_price_variation_ex()).mantissa(), (*message.max_price_variation_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.decayquantity"] = (message.decay_quantity().has_value() ? canonical::number((*message.decay_quantity())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.decaystartdate"] = (message.decay_start_date().has_value() ? canonical::number((*message.decay_start_date())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.originalcontractsize"] = (message.original_contract_size().has_value() ? canonical::number((*message.original_contract_size())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.contractmultiplier"] = (message.contract_multiplier().has_value() ? canonical::number((*message.contract_multiplier())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.contractmultiplierunit"] = (message.contract_multiplier_unit().has_value() ? canonical::number((*message.contract_multiplier_unit())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.flowscheduletype"] = (message.flow_schedule_type().has_value() ? canonical::number((*message.flow_schedule_type())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.minpriceincrementamountex"] = (message.min_price_increment_amount_ex().has_value() ? canonical::scaled((*message.min_price_increment_amount_ex()).mantissa(), (*message.min_price_increment_amount_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.userdefinedinstrument"] = canonical::text(canonical::character(message.user_defined_instrument()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.tradingreferencedate"] = (message.trading_reference_date().has_value() ? canonical::number((*message.trading_reference_date())) : canonical::absent());
    }

    void on(const protocol::MdInstrumentDefinitionOption& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.totnumreportsoptional"] = (message.tot_num_reports_optional().has_value() ? canonical::number((*message.tot_num_reports_optional())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securityupdateaction"] = canonical::text(canonical::character(message.security_update_action()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.lastupdatetime"] = canonical::number(message.last_update_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mdsecuritytradingstatus"] = (message.md_security_trading_status().has_value() ? canonical::number((*message.md_security_trading_status())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.applid"] = canonical::number(message.appl_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.marketsegmentid"] = canonical::number(message.market_segment_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.underlyingproduct"] = canonical::number(message.underlying_product());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securityexchange"] = canonical::text(std::string(message.security_exchange()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securitygroup"] = canonical::text(std::string(message.security_group()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.asset"] = canonical::text(std::string(message.asset()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.securitytype"] = canonical::text(std::string(message.security_type()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.cficode"] = canonical::text(std::string(message.cfi_code()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.putorcall"] = canonical::number(message.put_or_call());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.year"] = (message.maturity_month_year().year().has_value() ? canonical::number((*message.maturity_month_year().year())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.month"] = (message.maturity_month_year().month().has_value() ? canonical::number((*message.maturity_month_year().month())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.day"] = (message.maturity_month_year().day().has_value() ? canonical::number((*message.maturity_month_year().day())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maturitymonthyear.week"] = (message.maturity_month_year().week().has_value() ? canonical::number((*message.maturity_month_year().week())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.currency"] = canonical::text(std::string(message.currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.strikepriceex"] = (message.strike_price_ex().has_value() ? canonical::scaled((*message.strike_price_ex()).mantissa(), (*message.strike_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.strikecurrency"] = canonical::text(std::string(message.strike_currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlcurrency"] = canonical::text(std::string(message.settl_currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mincabpriceex"] = (message.min_cab_price_ex().has_value() ? canonical::scaled((*message.min_cab_price_ex()).mantissa(), (*message.min_cab_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matchalgorithm"] = canonical::text(canonical::character(message.match_algorithm()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mintradevol"] = canonical::number(message.min_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maxtradevol"] = canonical::number(message.max_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.minpriceincrementoptionalex"] = (message.min_price_increment_optional_ex().has_value() ? canonical::scaled((*message.min_price_increment_optional_ex()).mantissa(), (*message.min_price_increment_optional_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.minpriceincrementamountex"] = (message.min_price_increment_amount_ex().has_value() ? canonical::scaled((*message.min_price_increment_amount_ex()).mantissa(), (*message.min_price_increment_amount_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.displayfactorex"] = canonical::scaled(message.display_factor_ex().mantissa(), message.display_factor_ex().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tickrule"] = (message.tick_rule().has_value() ? canonical::number((*message.tick_rule())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mainfraction"] = (message.main_fraction().has_value() ? canonical::number((*message.main_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.subfraction"] = (message.sub_fraction().has_value() ? canonical::number((*message.sub_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.pricedisplayformat"] = (message.price_display_format().has_value() ? canonical::number((*message.price_display_format())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.unitofmeasureqtyex"] = (message.unit_of_measure_qty_ex().has_value() ? canonical::scaled((*message.unit_of_measure_qty_ex()).mantissa(), (*message.unit_of_measure_qty_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tradingreferencepriceex"] = (message.trading_reference_price_ex().has_value() ? canonical::scaled((*message.trading_reference_price_ex()).mantissa(), (*message.trading_reference_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().reserved_bits()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_5()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_6()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.clearedvolume"] = (message.cleared_volume().has_value() ? canonical::number((*message.cleared_volume())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.openinterestqty"] = (message.open_interest_qty().has_value() ? canonical::number((*message.open_interest_qty())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.lowlimitpriceex"] = (message.low_limit_price_ex().has_value() ? canonical::scaled((*message.low_limit_price_ex()).mantissa(), (*message.low_limit_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.highlimitpriceex"] = (message.high_limit_price_ex().has_value() ? canonical::scaled((*message.high_limit_price_ex()).mantissa(), (*message.high_limit_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.userdefinedinstrument"] = canonical::text(canonical::character(message.user_defined_instrument()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tradingreferencedate"] = (message.trading_reference_date().has_value() ? canonical::number((*message.trading_reference_date())) : canonical::absent());
    }

    void on(const protocol::MdInstrumentDefinitionSpread& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.totnumreportsoptional"] = (message.tot_num_reports_optional().has_value() ? canonical::number((*message.tot_num_reports_optional())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securityupdateaction"] = canonical::text(canonical::character(message.security_update_action()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.lastupdatetime"] = canonical::number(message.last_update_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mdsecuritytradingstatus"] = (message.md_security_trading_status().has_value() ? canonical::number((*message.md_security_trading_status())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.applid"] = canonical::number(message.appl_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.marketsegmentid"] = canonical::number(message.market_segment_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.underlyingproductoptional"] = (message.underlying_product_optional().has_value() ? canonical::number((*message.underlying_product_optional())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securityexchange"] = canonical::text(std::string(message.security_exchange()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securitygroup"] = canonical::text(std::string(message.security_group()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.asset"] = canonical::text(std::string(message.asset()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securitytype"] = canonical::text(std::string(message.security_type()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.cficode"] = canonical::text(std::string(message.cfi_code()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.year"] = (message.maturity_month_year().year().has_value() ? canonical::number((*message.maturity_month_year().year())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.month"] = (message.maturity_month_year().month().has_value() ? canonical::number((*message.maturity_month_year().month())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.day"] = (message.maturity_month_year().day().has_value() ? canonical::number((*message.maturity_month_year().day())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maturitymonthyear.week"] = (message.maturity_month_year().week().has_value() ? canonical::number((*message.maturity_month_year().week())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.currency"] = canonical::text(std::string(message.currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.securitysubtype"] = canonical::text(std::string(message.security_sub_type()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.userdefinedinstrument"] = canonical::text(canonical::character(message.user_defined_instrument()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.matchalgorithm"] = canonical::text(canonical::character(message.match_algorithm()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mintradevol"] = canonical::number(message.min_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maxtradevol"] = canonical::number(message.max_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.minpriceincrementoptionalex"] = (message.min_price_increment_optional_ex().has_value() ? canonical::scaled((*message.min_price_increment_optional_ex()).mantissa(), (*message.min_price_increment_optional_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.displayfactorex"] = canonical::scaled(message.display_factor_ex().mantissa(), message.display_factor_ex().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.pricedisplayformat"] = (message.price_display_format().has_value() ? canonical::number((*message.price_display_format())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.priceratioex"] = (message.price_ratio_ex().has_value() ? canonical::scaled((*message.price_ratio_ex()).mantissa(), (*message.price_ratio_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tickrule"] = (message.tick_rule().has_value() ? canonical::number((*message.tick_rule())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tradingreferencepriceex"] = (message.trading_reference_price_ex().has_value() ? canonical::scaled((*message.trading_reference_price_ex()).mantissa(), (*message.trading_reference_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.finaldaily"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().final_daily()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().reserved_bits()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_5()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_6()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.openinterestqty"] = (message.open_interest_qty().has_value() ? canonical::number((*message.open_interest_qty())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.clearedvolume"] = (message.cleared_volume().has_value() ? canonical::number((*message.cleared_volume())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.highlimitpriceex"] = (message.high_limit_price_ex().has_value() ? canonical::scaled((*message.high_limit_price_ex()).mantissa(), (*message.high_limit_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.lowlimitpriceex"] = (message.low_limit_price_ex().has_value() ? canonical::scaled((*message.low_limit_price_ex()).mantissa(), (*message.low_limit_price_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maxpricevariationex"] = (message.max_price_variation_ex().has_value() ? canonical::scaled((*message.max_price_variation_ex()).mantissa(), (*message.max_price_variation_ex()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mainfraction"] = (message.main_fraction().has_value() ? canonical::number((*message.main_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.subfraction"] = (message.sub_fraction().has_value() ? canonical::number((*message.sub_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tradingreferencedate"] = (message.trading_reference_date().has_value() ? canonical::number((*message.trading_reference_date())) : canonical::absent());
    }
};

// The messages Mdpsessionmgmt Payload selects, their values set in the entry of the message holding it
struct MdpsessionmgmtPayloadHandler {
    canonical::Listing& values;
    const std::string& entry;

    void on(const protocol::Negotiate& message) {
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.hmacsignature"] = canonical::text(std::string(message.hmac_signature()), '\0', false);
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.accesskeyid"] = canonical::text(std::string(message.access_key_id()), '\0', false);
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.uuid"] = canonical::number(message.uuid());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.requesttimestamp"] = canonical::number(message.request_timestamp());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.session"] = canonical::text(std::string(message.session()), '\0', false);
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiate.firm"] = canonical::text(std::string(message.firm()), '\0', false);
    }

    void on(const protocol::NegotiationReject& message) {
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.reason"] = canonical::text(std::string(message.reason()), '\0', false);
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.uuid"] = canonical::number(message.uuid());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.requesttimestamp"] = canonical::number(message.request_timestamp());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationreject.errorcodes"] = canonical::number(message.error_codes());
    }

    void on(const protocol::NegotiationResponse& message) {
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse.uuid"] = canonical::number(message.uuid());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse.requesttimestamp"] = canonical::number(message.request_timestamp());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.negotiationresponse.secretkeysecureidexpiration"] = (message.secret_key_secure_id_expiration().has_value() ? canonical::number((*message.secret_key_secure_id_expiration())) : canonical::absent());
    }

    void on(const protocol::Terminate& message) {
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.reason"] = canonical::text(std::string(message.reason()), '\0', false);
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.uuid"] = canonical::number(message.uuid());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.requesttimestamp"] = canonical::number(message.request_timestamp());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.terminate.errorcodes"] = canonical::number(message.error_codes());
    }

    void on(const protocol::MarketDataRequest& message) {
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.marketdatarequest";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.marketdatarequest.mdreqid"] = canonical::number(message.md_req_id());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.marketdatarequest.subscriptionreqtype"] = canonical::number(message.subscription_req_type());
    }

    void on(const protocol::RequestAck& message) {
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack.mdreqid"] = canonical::number(message.md_req_id());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack.subscriptionreqtype"] = canonical::number(message.subscription_req_type());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestack.mdreqidstatus"] = canonical::number(message.md_req_id_status());
    }

    void on(const protocol::RequestReject& message) {
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject.mdreqidoptional"] = (message.md_req_id_optional().has_value() ? canonical::number((*message.md_req_id_optional())) : canonical::absent());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject.mdreqrejreason"] = canonical::number(message.md_req_rej_reason());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.requestreject.text"] = canonical::text(std::string(message.text()), '\0', false);
    }

    void on(const protocol::SecurityListRequest& message) {
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitylistrequest";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitylistrequest.mdreqid"] = canonical::number(message.md_req_id());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitylistrequest.subscriptionreqtype"] = canonical::number(message.subscription_req_type());
    }

    void on(const protocol::SecurityStatusRequest& message) {
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload"] = "udppacket.message.payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitystatusrequest";
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitystatusrequest.mdreqid"] = canonical::number(message.md_req_id());
        values[entry + ".payload.mdpsessionmgmtmessage.mdpsessionmgmtpayload.securitystatusrequest.subscriptionreqtype"] = canonical::number(message.subscription_req_type());
    }
};

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::UdpPacket& packet) {
        values["udppacket.binarypacketheader.packetsequencenumber"] = canonical::number(packet.binary_packet_header().packet_sequence_number());
        values["udppacket.binarypacketheader.sendingtime"] = canonical::number(packet.binary_packet_header().sending_time());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::MktdataMessage& message) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        MktdataPayloadHandler selected{ values, entry };
        message.mktdata_payload(selected);
    }

    void on(const protocol::MdpsessionmgmtMessage& message) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
        MdpsessionmgmtPayloadHandler selected{ values, entry };
        message.mdpsessionmgmt_payload(selected);
    }
};

// The values the Flyweight reader reads from one datagram, by indexed address. A datagram it cannot
// read is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::UdpPacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Flyweight and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Cme.Globex.Mdp3.Sbe.v1.9 (flyweight values)\n");
    int failures = 0;
    failures += check("MdIncrementalRefreshBook", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshBook.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshBook.values");
    failures += check("MdIncrementalRefreshOrderBook", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshOrderBook.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshOrderBook.values");
    failures += check("MdIncrementalRefreshTradeSummary", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshTradeSummary.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshTradeSummary.values");
    failures += check("MdIncrementalRefreshVolume", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshVolume.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshVolume.values");
    return failures == 0 ? 0 : 1;
}
