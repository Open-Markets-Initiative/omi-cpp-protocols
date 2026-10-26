// Cme.Globex.Mdp3.Sbe.v1.8 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/cme/globex/mdp3/sbe/v1.8/definitions.hpp"

namespace protocol = ::cme::globex::mdp3::sbe::v1_8;

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
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.minpriceincrement"] = canonical::scaled(message.min_price_increment().mantissa(), message.min_price_increment().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.displayfactor"] = canonical::scaled(message.display_factor().mantissa(), message.display_factor().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.mainfraction"] = (message.main_fraction().has_value() ? canonical::number((*message.main_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.subfraction"] = (message.sub_fraction().has_value() ? canonical::number((*message.sub_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.pricedisplayformat"] = (message.price_display_format().has_value() ? canonical::number((*message.price_display_format())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.unitofmeasureqty"] = (message.unit_of_measure_qty().has_value() ? canonical::scaled((*message.unit_of_measure_qty()).mantissa(), (*message.unit_of_measure_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.tradingreferenceprice"] = (message.trading_reference_price().has_value() ? canonical::scaled((*message.trading_reference_price()).mantissa(), (*message.trading_reference_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.final"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().final()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().reserved_bits()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_5()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_6()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.openinterestqty"] = (message.open_interest_qty().has_value() ? canonical::number((*message.open_interest_qty())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.clearedvolume"] = (message.cleared_volume().has_value() ? canonical::number((*message.cleared_volume())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.highlimitprice"] = (message.high_limit_price().has_value() ? canonical::scaled((*message.high_limit_price()).mantissa(), (*message.high_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.lowlimitprice"] = (message.low_limit_price().has_value() ? canonical::scaled((*message.low_limit_price()).mantissa(), (*message.low_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.maxpricevariation"] = (message.max_price_variation().has_value() ? canonical::scaled((*message.max_price_variation()).mantissa(), (*message.max_price_variation()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.decayquantity"] = (message.decay_quantity().has_value() ? canonical::number((*message.decay_quantity())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.decaystartdate"] = (message.decay_start_date().has_value() ? canonical::number((*message.decay_start_date())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.originalcontractsize"] = (message.original_contract_size().has_value() ? canonical::number((*message.original_contract_size())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.contractmultiplier"] = (message.contract_multiplier().has_value() ? canonical::number((*message.contract_multiplier())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.contractmultiplierunit"] = (message.contract_multiplier_unit().has_value() ? canonical::number((*message.contract_multiplier_unit())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.flowscheduletype"] = (message.flow_schedule_type().has_value() ? canonical::number((*message.flow_schedule_type())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.minpriceincrementamount"] = (message.min_price_increment_amount().has_value() ? canonical::scaled((*message.min_price_increment_amount()).mantissa(), (*message.min_price_increment_amount()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.userdefinedinstrument"] = canonical::text(canonical::character(message.user_defined_instrument()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionfuture.tradingreferencedate"] = (message.trading_reference_date().has_value() ? canonical::number((*message.trading_reference_date())) : canonical::absent());
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
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.minpriceincrement"] = canonical::scaled(message.min_price_increment().mantissa(), message.min_price_increment().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.displayfactor"] = canonical::scaled(message.display_factor().mantissa(), message.display_factor().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.pricedisplayformat"] = (message.price_display_format().has_value() ? canonical::number((*message.price_display_format())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.priceratio"] = (message.price_ratio().has_value() ? canonical::scaled((*message.price_ratio()).mantissa(), (*message.price_ratio()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tickrule"] = (message.tick_rule().has_value() ? canonical::number((*message.tick_rule())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tradingreferenceprice"] = (message.trading_reference_price().has_value() ? canonical::scaled((*message.trading_reference_price()).mantissa(), (*message.trading_reference_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.final"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().final()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().reserved_bits()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_5()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_6()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.openinterestqty"] = (message.open_interest_qty().has_value() ? canonical::number((*message.open_interest_qty())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.clearedvolume"] = (message.cleared_volume().has_value() ? canonical::number((*message.cleared_volume())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.highlimitprice"] = (message.high_limit_price().has_value() ? canonical::scaled((*message.high_limit_price()).mantissa(), (*message.high_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.lowlimitprice"] = (message.low_limit_price().has_value() ? canonical::scaled((*message.low_limit_price()).mantissa(), (*message.low_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.maxpricevariation"] = (message.max_price_variation().has_value() ? canonical::scaled((*message.max_price_variation()).mantissa(), (*message.max_price_variation()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.mainfraction"] = (message.main_fraction().has_value() ? canonical::number((*message.main_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.subfraction"] = (message.sub_fraction().has_value() ? canonical::number((*message.sub_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionspread.tradingreferencedate"] = (message.trading_reference_date().has_value() ? canonical::number((*message.trading_reference_date())) : canonical::absent());
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

    void on(const protocol::MdIncrementalRefreshTrade& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade";
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.transacttime"] = canonical::number(message.transact_time());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_trade_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_volume_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_quote_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_stats_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().last_implied_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().recovery_msg()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.reserved"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().reserved()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdincrementalrefreshtrade.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message.match_event_indicator().end_of_event()));
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
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.highlimitprice"] = (message.high_limit_price().has_value() ? canonical::scaled((*message.high_limit_price()).mantissa(), (*message.high_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.lowlimitprice"] = (message.low_limit_price().has_value() ? canonical::scaled((*message.low_limit_price()).mantissa(), (*message.low_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefresh.maxpricevariation"] = (message.max_price_variation().has_value() ? canonical::scaled((*message.max_price_variation()).mantissa(), (*message.max_price_variation()).exponent()) : canonical::absent());
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
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.strikeprice"] = (message.strike_price().has_value() ? canonical::scaled((*message.strike_price()).mantissa(), (*message.strike_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.strikecurrency"] = canonical::text(std::string(message.strike_currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlcurrency"] = canonical::text(std::string(message.settl_currency()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mincabprice"] = (message.min_cab_price().has_value() ? canonical::scaled((*message.min_cab_price()).mantissa(), (*message.min_cab_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.matchalgorithm"] = canonical::text(canonical::character(message.match_algorithm()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mintradevol"] = canonical::number(message.min_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.maxtradevol"] = canonical::number(message.max_trade_vol());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.minpriceincrementoptional"] = (message.min_price_increment_optional().has_value() ? canonical::scaled((*message.min_price_increment_optional()).mantissa(), (*message.min_price_increment_optional()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.minpriceincrementamount"] = (message.min_price_increment_amount().has_value() ? canonical::scaled((*message.min_price_increment_amount()).mantissa(), (*message.min_price_increment_amount()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.displayfactor"] = canonical::scaled(message.display_factor().mantissa(), message.display_factor().exponent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tickrule"] = (message.tick_rule().has_value() ? canonical::number((*message.tick_rule())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.mainfraction"] = (message.main_fraction().has_value() ? canonical::number((*message.main_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.subfraction"] = (message.sub_fraction().has_value() ? canonical::number((*message.sub_fraction())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.pricedisplayformat"] = (message.price_display_format().has_value() ? canonical::number((*message.price_display_format())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.unitofmeasure"] = canonical::text(std::string(message.unit_of_measure()), '\0', false);
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.unitofmeasureqty"] = (message.unit_of_measure_qty().has_value() ? canonical::scaled((*message.unit_of_measure_qty()).mantissa(), (*message.unit_of_measure_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tradingreferenceprice"] = (message.trading_reference_price().has_value() ? canonical::scaled((*message.trading_reference_price()).mantissa(), (*message.trading_reference_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.final"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().final()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.actual"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().actual()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.rounded"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().rounded()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.intraday"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().intraday()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.reservedbits"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().reserved_bits()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.unusedsettlpricetype5"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_5()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.unusedsettlpricetype6"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().unused_settl_price_type_6()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.settlpricetype.nullvalue"] = canonical::number(static_cast<std::uint64_t>(message.settl_price_type().null_value()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.clearedvolume"] = (message.cleared_volume().has_value() ? canonical::number((*message.cleared_volume())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.openinterestqty"] = (message.open_interest_qty().has_value() ? canonical::number((*message.open_interest_qty())) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.lowlimitprice"] = (message.low_limit_price().has_value() ? canonical::scaled((*message.low_limit_price()).mantissa(), (*message.low_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.highlimitprice"] = (message.high_limit_price().has_value() ? canonical::scaled((*message.high_limit_price()).mantissa(), (*message.high_limit_price()).exponent()) : canonical::absent());
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.userdefinedinstrument"] = canonical::text(canonical::character(message.user_defined_instrument()));
        values[entry + ".payload.mktdatamessage.mktdatapayload.mdinstrumentdefinitionoption.tradingreferencedate"] = (message.trading_reference_date().has_value() ? canonical::number((*message.trading_reference_date())) : canonical::absent());
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

    void on(const protocol::SnapshotFullRefreshOrderBook& message) {
        values[entry + ".payload.mktdatamessage.mktdatapayload"] = "udppacket.message.payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook";
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.lastmsgseqnumprocessed"] = canonical::number(message.last_msg_seq_num_processed());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.totnumreports"] = canonical::number(message.tot_num_reports());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.securityid"] = canonical::number(message.security_id());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.nochunks"] = canonical::number(message.no_chunks());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.currentchunk"] = canonical::number(message.current_chunk());
        values[entry + ".payload.mktdatamessage.mktdatapayload.snapshotfullrefreshorderbook.transacttime"] = canonical::number(message.transact_time());
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
    std::printf("== Cme.Globex.Mdp3.Sbe.v1.8 (flyweight values)\n");
    int failures = 0;
    failures += check("MdIncrementalRefreshTradeSummary", "Cme/Globex.Mdp3.Sbe.v1.8/MdIncrementalRefreshTradeSummary.pcap", "cme/globex/mdp3/sbe/v1.8/MdIncrementalRefreshTradeSummary.values");
    return failures == 0 ? 0 : 1;
}
