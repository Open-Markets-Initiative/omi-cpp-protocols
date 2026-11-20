// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 canonical values, through the Modern iterator: every value Modern reads from
// each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/modern/b3/b3derivatives/binaryumdf/sbe/v1.8/definitions.hpp"

namespace protocol = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.channelid"] = canonical::number(iterator.packet_header->channel_id.get());
    values["packet.packetheader.packetreserved"] = canonical::number(iterator.packet_header->packet_reserved.get());
    values["packet.packetheader.sequenceversion"] = canonical::number(iterator.packet_header->sequence_version.get());
    values["packet.packetheader.sequencenumber"] = canonical::number(iterator.packet_header->sequence_number.get());
    values["packet.packetheader.sendingtime"] = canonical::number(iterator.packet_header->sending_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".framingheader.messagelength"] = canonical::number(iterator.framing_header->message_length.get());
        values[entry + ".framingheader.encodingtype"] = canonical::number(iterator.framing_header->encoding_type.get());
        values[entry + ".messageheader.blocklength"] = canonical::number(iterator.message_header->block_length.get());
        values[entry + ".messageheader.templateid"] = canonical::number(iterator.message_header->template_id.get());
        values[entry + ".messageheader.schemaid"] = canonical::number(iterator.message_header->schema_id.get());
        values[entry + ".messageheader.version"] = canonical::number(iterator.message_header->version.get());

        if (iterator.template_id == 2) {
            values[entry + ".payload"] = "packet.message.payload.sequencemessage";
            [[maybe_unused]] const auto* message = protocol::SequenceMessage::parse(iterator.message);
            values[entry + ".payload.sequencemessage.nextseqno"] = canonical::number(message->next_seq_no.get());
        } else if (iterator.template_id == 9) {
            values[entry + ".payload"] = "packet.message.payload.emptybookmessage";
            [[maybe_unused]] const auto* message = protocol::EmptyBookMessage::parse(iterator.message);
            values[entry + ".payload.emptybookmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.emptybookmessage.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.emptybookmessage.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.emptybookmessage.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.emptybookmessage.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.emptybookmessage.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.emptybookmessage.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.emptybookmessage.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.emptybookmessage.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
        } else if (iterator.template_id == 11) {
            values[entry + ".payload"] = "packet.message.payload.channelreset11message";
            [[maybe_unused]] const auto* message = protocol::ChannelReset11Message::parse(iterator.message);
            values[entry + ".payload.channelreset11message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.channelreset11message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.channelreset11message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.channelreset11message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.channelreset11message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.channelreset11message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.channelreset11message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.channelreset11message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
        } else if (iterator.template_id == 3) {
            values[entry + ".payload"] = "packet.message.payload.securitystatus3message";
            [[maybe_unused]] const auto* message = protocol::SecurityStatus3Message::parse(iterator.message);
            values[entry + ".payload.securitystatus3message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.securitystatus3message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.securitystatus3message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.securitystatus3message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.securitystatus3message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.securitystatus3message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.securitystatus3message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.securitystatus3message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.securitystatus3message.tradingsessionid"] = canonical::number(message->trading_session_id.get());
            values[entry + ".payload.securitystatus3message.securitytradingstatus"] = canonical::number(message->security_trading_status.get());
            values[entry + ".payload.securitystatus3message.securitytradingevent"] = (static_cast<std::uint8_t>(message->security_trading_event.get()) != 0x0FFU ? canonical::number(message->security_trading_event.get()) : canonical::absent());
            values[entry + ".payload.securitystatus3message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.securitystatus3message.tradsesopentime"] = (static_cast<std::uint64_t>(message->trad_ses_open_time.get()) != 0x0ULL ? canonical::number(message->trad_ses_open_time.get()) : canonical::absent());
            values[entry + ".payload.securitystatus3message.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0ULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.securitystatus3message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 10) {
            values[entry + ".payload"] = "packet.message.payload.securitygroupphase10message";
            [[maybe_unused]] const auto* message = protocol::SecurityGroupPhase10Message::parse(iterator.message);
            values[entry + ".payload.securitygroupphase10message.securitygroup"] = canonical::text(std::string(message->security_group.get()), '\0', false);
            values[entry + ".payload.securitygroupphase10message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.securitygroupphase10message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.securitygroupphase10message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.securitygroupphase10message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.securitygroupphase10message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.securitygroupphase10message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.securitygroupphase10message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.securitygroupphase10message.tradingsessionid"] = canonical::number(message->trading_session_id.get());
            values[entry + ".payload.securitygroupphase10message.tradingsessionsubid"] = canonical::number(message->trading_session_sub_id.get());
            values[entry + ".payload.securitygroupphase10message.securitytradingevent"] = (static_cast<std::uint8_t>(message->security_trading_event.get()) != 0x0FFU ? canonical::number(message->security_trading_event.get()) : canonical::absent());
            values[entry + ".payload.securitygroupphase10message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.securitygroupphase10message.tradsesopentime"] = (static_cast<std::uint64_t>(message->trad_ses_open_time.get()) != 0x0ULL ? canonical::number(message->trad_ses_open_time.get()) : canonical::absent());
            values[entry + ".payload.securitygroupphase10message.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0ULL ? canonical::number(message->transact_time.get()) : canonical::absent());
        } else if (iterator.template_id == 4) {
            values[entry + ".payload"] = "packet.message.payload.deprecatedsecuritydefinitionmessage";
            [[maybe_unused]] const auto* message = protocol::DeprecatedSecurityDefinitionMessage::parse(iterator.message);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityexchange"] = canonical::text(std::string(message->security_exchange.get()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityidsource"] = canonical::text(canonical::character(message->security_id_source.get()));
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitygroup"] = canonical::text(std::string(message->security_group.get()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.symbol"] = canonical::text(std::string(message->symbol.get()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityupdateaction"] = canonical::text(canonical::character(message->security_update_action.get()));
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitytype"] = canonical::number(message->security_type.get());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitysubtype"] = canonical::number(message->security_sub_type.get());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.totnorelatedsym"] = canonical::number(message->tot_no_related_sym.get());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.minpriceincrementlegacy"] = (static_cast<std::uint64_t>(message->min_price_increment_legacy.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->min_price_increment_legacy.integer(), -4) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.strikeprice"] = (static_cast<std::uint64_t>(message->strike_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->strike_price.integer(), -4) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractmultiplier"] = (static_cast<std::uint64_t>(message->contract_multiplier.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->contract_multiplier.integer(), -8) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.pricedivisor"] = (static_cast<std::uint64_t>(message->price_divisor.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_divisor.integer(), -8) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securityvaliditytimestamp"] = (static_cast<std::uint64_t>(message->security_validity_timestamp.get()) != 0x08000000000000000ULL ? canonical::number(message->security_validity_timestamp.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.nosharesissued"] = (static_cast<std::uint64_t>(message->no_shares_issued.get()) != 0x0ULL ? canonical::number(message->no_shares_issued.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.clearinghouseid"] = (static_cast<std::uint64_t>(message->clearing_house_id.get()) != 0x0ULL ? canonical::number(message->clearing_house_id.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.minorderqty"] = (static_cast<std::uint64_t>(message->min_order_qty.get()) != 0x08000000000000000ULL ? canonical::number(message->min_order_qty.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.maxorderqty"] = (static_cast<std::uint64_t>(message->max_order_qty.get()) != 0x08000000000000000ULL ? canonical::number(message->max_order_qty.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.minlotsize"] = (static_cast<std::uint64_t>(message->min_lot_size.get()) != 0x08000000000000000ULL ? canonical::number(message->min_lot_size.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.mintradevol"] = (static_cast<std::uint64_t>(message->min_trade_vol.get()) != 0x08000000000000000ULL ? canonical::number(message->min_trade_vol.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.corporateactioneventid"] = (static_cast<std::uint32_t>(message->corporate_action_event_id.get()) != 0x0U ? canonical::number(message->corporate_action_event_id.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.issuedate"] = canonical::number(message->issue_date.get());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitydate"] = (static_cast<std::uint32_t>(message->maturity_date.get()) != 0x0U ? canonical::number(message->maturity_date.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.startdate"] = (static_cast<std::uint32_t>(message->start_date.get()) != 0x0U ? canonical::number(message->start_date.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.enddate"] = (static_cast<std::uint32_t>(message->end_date.get()) != 0x0U ? canonical::number(message->end_date.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.settltype"] = (static_cast<std::uint16_t>(message->settl_type.get()) != 0x0FFFFU ? canonical::number(message->settl_type.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.settldate"] = (static_cast<std::uint32_t>(message->settl_date.get()) != 0x0U ? canonical::number(message->settl_date.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.dateddate"] = (static_cast<std::uint32_t>(message->dated_date.get()) != 0x0U ? canonical::number(message->dated_date.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.asset"] = canonical::text(std::string(message->asset.get()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.cficode"] = canonical::text(std::string(message->cfi_code.get()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.year"] = (static_cast<std::uint16_t>(message->maturity_month_year.year.get()) != 0x0U ? canonical::number(message->maturity_month_year.year.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.month"] = (static_cast<std::uint8_t>(message->maturity_month_year.month.get()) != 0x0U ? canonical::number(message->maturity_month_year.month.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.day"] = (static_cast<std::uint8_t>(message->maturity_month_year.day.get()) != 0x0U ? canonical::number(message->maturity_month_year.day.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.maturitymonthyear.week"] = (static_cast<std::uint8_t>(message->maturity_month_year.week.get()) != 0x0U ? canonical::number(message->maturity_month_year.week.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.year"] = (static_cast<std::uint16_t>(message->contract_settl_month.year.get()) != 0x0U ? canonical::number(message->contract_settl_month.year.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.month"] = (static_cast<std::uint8_t>(message->contract_settl_month.month.get()) != 0x0U ? canonical::number(message->contract_settl_month.month.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.day"] = (static_cast<std::uint8_t>(message->contract_settl_month.day.get()) != 0x0U ? canonical::number(message->contract_settl_month.day.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.contractsettlmonth.week"] = (static_cast<std::uint8_t>(message->contract_settl_month.week.get()) != 0x0U ? canonical::number(message->contract_settl_month.week.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.currency"] = canonical::text(std::string(message->currency.get()), '\0', false);
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.lottype"] = (static_cast<std::uint8_t>(message->lot_type.get()) != 0x0FFU ? canonical::number(message->lot_type.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.ticksizedenominator"] = (static_cast<std::uint8_t>(message->tick_size_denominator.get()) != 0x0FFU ? canonical::number(message->tick_size_denominator.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.product"] = canonical::number(message->product.get());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.exercisestyle"] = (static_cast<std::uint8_t>(message->exercise_style.get()) != 0x0FFU ? canonical::number(message->exercise_style.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.putorcall"] = (static_cast<std::uint8_t>(message->put_or_call.get()) != 0x0FFU ? canonical::number(message->put_or_call.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.pricetypeoptional"] = (static_cast<std::uint8_t>(message->price_type_optional.get()) != 0x0U ? canonical::number(message->price_type_optional.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.marketsegmentid"] = (static_cast<std::uint8_t>(message->market_segment_id.get()) != 0x0U ? canonical::number(message->market_segment_id.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.governanceindicator"] = (static_cast<std::uint8_t>(message->governance_indicator.get()) != 0x0FFU ? canonical::number(message->governance_indicator.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.securitymatchtype"] = (static_cast<std::uint8_t>(message->security_match_type.get()) != 0x0FFU ? canonical::number(message->security_match_type.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.lastfragment"] = (static_cast<std::uint8_t>(message->last_fragment.get()) != 0x0FFU ? canonical::number(message->last_fragment.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.multilegmodel"] = (static_cast<std::uint8_t>(message->multi_leg_model.get()) != 0x0FFU ? canonical::number(message->multi_leg_model.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.multilegpricemethod"] = (static_cast<std::uint8_t>(message->multi_leg_price_method.get()) != 0x0FFU ? canonical::number(message->multi_leg_price_method.get()) : canonical::absent());
            values[entry + ".payload.deprecatedsecuritydefinitionmessage.mincrossqty"] = (static_cast<std::uint64_t>(message->min_cross_qty.get()) != 0x08000000000000000ULL ? canonical::number(message->min_cross_qty.get()) : canonical::absent());
        } else if (iterator.template_id == 12) {
            values[entry + ".payload"] = "packet.message.payload.securitydefinitionmessage";
            [[maybe_unused]] const auto* message = protocol::SecurityDefinitionMessage::parse(iterator.message);
            values[entry + ".payload.securitydefinitionmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.securitydefinitionmessage.securityexchange"] = canonical::text(std::string(message->security_exchange.get()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.securityidsource"] = canonical::text(canonical::character(message->security_id_source.get()));
            values[entry + ".payload.securitydefinitionmessage.securitygroup"] = canonical::text(std::string(message->security_group.get()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.symbol"] = canonical::text(std::string(message->symbol.get()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.securityupdateaction"] = canonical::text(canonical::character(message->security_update_action.get()));
            values[entry + ".payload.securitydefinitionmessage.securitytype"] = canonical::number(message->security_type.get());
            values[entry + ".payload.securitydefinitionmessage.securitysubtype"] = canonical::number(message->security_sub_type.get());
            values[entry + ".payload.securitydefinitionmessage.totnorelatedsym"] = canonical::number(message->tot_no_related_sym.get());
            values[entry + ".payload.securitydefinitionmessage.minpriceincrementoptional"] = (static_cast<std::uint64_t>(message->min_price_increment_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->min_price_increment_optional.integer(), -8) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.strikeprice"] = (static_cast<std::uint64_t>(message->strike_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->strike_price.integer(), -4) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.contractmultiplier"] = (static_cast<std::uint64_t>(message->contract_multiplier.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->contract_multiplier.integer(), -8) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.pricedivisor"] = (static_cast<std::uint64_t>(message->price_divisor.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price_divisor.integer(), -8) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.securityvaliditytimestamp"] = (static_cast<std::uint64_t>(message->security_validity_timestamp.get()) != 0x08000000000000000ULL ? canonical::number(message->security_validity_timestamp.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.nosharesissued"] = (static_cast<std::uint64_t>(message->no_shares_issued.get()) != 0x0ULL ? canonical::number(message->no_shares_issued.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.clearinghouseid"] = (static_cast<std::uint64_t>(message->clearing_house_id.get()) != 0x0ULL ? canonical::number(message->clearing_house_id.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.minorderqty"] = (static_cast<std::uint64_t>(message->min_order_qty.get()) != 0x08000000000000000ULL ? canonical::number(message->min_order_qty.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.maxorderqty"] = (static_cast<std::uint64_t>(message->max_order_qty.get()) != 0x08000000000000000ULL ? canonical::number(message->max_order_qty.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.minlotsize"] = (static_cast<std::uint64_t>(message->min_lot_size.get()) != 0x08000000000000000ULL ? canonical::number(message->min_lot_size.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.mintradevol"] = (static_cast<std::uint64_t>(message->min_trade_vol.get()) != 0x08000000000000000ULL ? canonical::number(message->min_trade_vol.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.corporateactioneventid"] = (static_cast<std::uint32_t>(message->corporate_action_event_id.get()) != 0x0U ? canonical::number(message->corporate_action_event_id.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.issuedate"] = canonical::number(message->issue_date.get());
            values[entry + ".payload.securitydefinitionmessage.maturitydate"] = (static_cast<std::uint32_t>(message->maturity_date.get()) != 0x0U ? canonical::number(message->maturity_date.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.startdate"] = (static_cast<std::uint32_t>(message->start_date.get()) != 0x0U ? canonical::number(message->start_date.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.enddate"] = (static_cast<std::uint32_t>(message->end_date.get()) != 0x0U ? canonical::number(message->end_date.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.settltype"] = (static_cast<std::uint16_t>(message->settl_type.get()) != 0x0FFFFU ? canonical::number(message->settl_type.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.settldate"] = (static_cast<std::uint32_t>(message->settl_date.get()) != 0x0U ? canonical::number(message->settl_date.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.dateddate"] = (static_cast<std::uint32_t>(message->dated_date.get()) != 0x0U ? canonical::number(message->dated_date.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.asset"] = canonical::text(std::string(message->asset.get()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.cficode"] = canonical::text(std::string(message->cfi_code.get()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.year"] = (static_cast<std::uint16_t>(message->maturity_month_year.year.get()) != 0x0U ? canonical::number(message->maturity_month_year.year.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.month"] = (static_cast<std::uint8_t>(message->maturity_month_year.month.get()) != 0x0U ? canonical::number(message->maturity_month_year.month.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.day"] = (static_cast<std::uint8_t>(message->maturity_month_year.day.get()) != 0x0U ? canonical::number(message->maturity_month_year.day.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.maturitymonthyear.week"] = (static_cast<std::uint8_t>(message->maturity_month_year.week.get()) != 0x0U ? canonical::number(message->maturity_month_year.week.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.year"] = (static_cast<std::uint16_t>(message->contract_settl_month.year.get()) != 0x0U ? canonical::number(message->contract_settl_month.year.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.month"] = (static_cast<std::uint8_t>(message->contract_settl_month.month.get()) != 0x0U ? canonical::number(message->contract_settl_month.month.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.day"] = (static_cast<std::uint8_t>(message->contract_settl_month.day.get()) != 0x0U ? canonical::number(message->contract_settl_month.day.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.contractsettlmonth.week"] = (static_cast<std::uint8_t>(message->contract_settl_month.week.get()) != 0x0U ? canonical::number(message->contract_settl_month.week.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.currency"] = canonical::text(std::string(message->currency.get()), '\0', false);
            values[entry + ".payload.securitydefinitionmessage.lottype"] = (static_cast<std::uint8_t>(message->lot_type.get()) != 0x0FFU ? canonical::number(message->lot_type.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.ticksizedenominator"] = (static_cast<std::uint8_t>(message->tick_size_denominator.get()) != 0x0FFU ? canonical::number(message->tick_size_denominator.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.product"] = canonical::number(message->product.get());
            values[entry + ".payload.securitydefinitionmessage.exercisestyle"] = (static_cast<std::uint8_t>(message->exercise_style.get()) != 0x0FFU ? canonical::number(message->exercise_style.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.putorcall"] = (static_cast<std::uint8_t>(message->put_or_call.get()) != 0x0FFU ? canonical::number(message->put_or_call.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.pricetypeoptional"] = (static_cast<std::uint8_t>(message->price_type_optional.get()) != 0x0U ? canonical::number(message->price_type_optional.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.marketsegmentid"] = (static_cast<std::uint8_t>(message->market_segment_id.get()) != 0x0U ? canonical::number(message->market_segment_id.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.governanceindicator"] = (static_cast<std::uint8_t>(message->governance_indicator.get()) != 0x0FFU ? canonical::number(message->governance_indicator.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.securitymatchtype"] = (static_cast<std::uint8_t>(message->security_match_type.get()) != 0x0FFU ? canonical::number(message->security_match_type.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.lastfragment"] = (static_cast<std::uint8_t>(message->last_fragment.get()) != 0x0FFU ? canonical::number(message->last_fragment.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.multilegmodel"] = (static_cast<std::uint8_t>(message->multi_leg_model.get()) != 0x0FFU ? canonical::number(message->multi_leg_model.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.multilegpricemethod"] = (static_cast<std::uint8_t>(message->multi_leg_price_method.get()) != 0x0FFU ? canonical::number(message->multi_leg_price_method.get()) : canonical::absent());
            values[entry + ".payload.securitydefinitionmessage.mincrossqty"] = (static_cast<std::uint64_t>(message->min_cross_qty.get()) != 0x08000000000000000ULL ? canonical::number(message->min_cross_qty.get()) : canonical::absent());
        } else if (iterator.template_id == 5) {
            values[entry + ".payload"] = "packet.message.payload.news5message";
            [[maybe_unused]] const auto* message = protocol::News5Message::parse(iterator.message);
            values[entry + ".payload.news5message.securityidoptional"] = (static_cast<std::uint64_t>(message->security_id_optional.get()) != 0x0ULL ? canonical::number(message->security_id_optional.get()) : canonical::absent());
            values[entry + ".payload.news5message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.news5message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.news5message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.news5message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.news5message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.news5message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.news5message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.news5message.newssource"] = canonical::number(message->news_source.get());
            values[entry + ".payload.news5message.partcount"] = canonical::number(message->part_count.get());
            values[entry + ".payload.news5message.partnumber"] = canonical::number(message->part_number.get());
            values[entry + ".payload.news5message.newsid"] = (static_cast<std::uint64_t>(message->news_id.get()) != 0x0ULL ? canonical::number(message->news_id.get()) : canonical::absent());
            values[entry + ".payload.news5message.origtime"] = (static_cast<std::uint64_t>(message->orig_time.get()) != 0x0ULL ? canonical::number(message->orig_time.get()) : canonical::absent());
            values[entry + ".payload.news5message.totaltextlength"] = canonical::number(message->total_text_length.get());
        } else if (iterator.template_id == 15) {
            values[entry + ".payload"] = "packet.message.payload.openingprice15message";
            [[maybe_unused]] const auto* message = protocol::OpeningPrice15Message::parse(iterator.message);
            values[entry + ".payload.openingprice15message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.openingprice15message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.openingprice15message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.openingprice15message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.openingprice15message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.openingprice15message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.openingprice15message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.openingprice15message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.openingprice15message.mdupdateaction"] = canonical::number(message->md_update_action.get());
            values[entry + ".payload.openingprice15message.openclosesettlflag"] = canonical::number(message->open_close_settl_flag.get());
            values[entry + ".payload.openingprice15message.mdfutureprice"] = canonical::scaled(message->md_future_price.integer(), -4);
            values[entry + ".payload.openingprice15message.netchgprevday"] = (static_cast<std::uint64_t>(message->net_chg_prev_day.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->net_chg_prev_day.integer(), -8) : canonical::absent());
            values[entry + ".payload.openingprice15message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.openingprice15message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.openingprice15message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 16) {
            values[entry + ".payload"] = "packet.message.payload.theoreticalopeningprice16message";
            [[maybe_unused]] const auto* message = protocol::TheoreticalOpeningPrice16Message::parse(iterator.message);
            values[entry + ".payload.theoreticalopeningprice16message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.theoreticalopeningprice16message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.theoreticalopeningprice16message.mdupdateaction"] = canonical::number(message->md_update_action.get());
            values[entry + ".payload.theoreticalopeningprice16message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.theoreticalopeningprice16message.mdcorporateoffsetpriceoptional"] = (static_cast<std::uint64_t>(message->md_corporate_offset_price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->md_corporate_offset_price_optional.integer(), -4) : canonical::absent());
            values[entry + ".payload.theoreticalopeningprice16message.mdentrysizeoptional"] = (static_cast<std::uint64_t>(message->md_entry_size_optional.get()) != 0x08000000000000000ULL ? canonical::number(message->md_entry_size_optional.get()) : canonical::absent());
            values[entry + ".payload.theoreticalopeningprice16message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.theoreticalopeningprice16message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 17) {
            values[entry + ".payload"] = "packet.message.payload.closingprice17message";
            [[maybe_unused]] const auto* message = protocol::ClosingPrice17Message::parse(iterator.message);
            values[entry + ".payload.closingprice17message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.closingprice17message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.closingprice17message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.closingprice17message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.closingprice17message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.closingprice17message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.closingprice17message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.closingprice17message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.closingprice17message.openclosesettlflag"] = canonical::number(message->open_close_settl_flag.get());
            values[entry + ".payload.closingprice17message.mdcorporateprice"] = canonical::scaled(message->md_corporate_price.integer(), -8);
            values[entry + ".payload.closingprice17message.lasttradedate"] = (static_cast<std::uint16_t>(message->last_trade_date.get()) != 0x0U ? canonical::number(message->last_trade_date.get()) : canonical::absent());
            values[entry + ".payload.closingprice17message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.closingprice17message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.closingprice17message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 19) {
            values[entry + ".payload"] = "packet.message.payload.auctionimbalance19message";
            [[maybe_unused]] const auto* message = protocol::AuctionImbalance19Message::parse(iterator.message);
            values[entry + ".payload.auctionimbalance19message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.auctionimbalance19message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.auctionimbalance19message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.auctionimbalance19message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.auctionimbalance19message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.auctionimbalance19message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.auctionimbalance19message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.auctionimbalance19message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.auctionimbalance19message.mdupdateaction"] = canonical::number(message->md_update_action.get());
            values[entry + ".payload.auctionimbalance19message.imbalancecondition.imbalancemorebuyers"] = canonical::number(static_cast<std::uint64_t>(message->imbalance_condition.ImbalanceMoreBuyers()));
            values[entry + ".payload.auctionimbalance19message.imbalancecondition.imbalancemoresellers"] = canonical::number(static_cast<std::uint64_t>(message->imbalance_condition.ImbalanceMoreSellers()));
            values[entry + ".payload.auctionimbalance19message.mdentrysizeoptional"] = (static_cast<std::uint64_t>(message->md_entry_size_optional.get()) != 0x08000000000000000ULL ? canonical::number(message->md_entry_size_optional.get()) : canonical::absent());
            values[entry + ".payload.auctionimbalance19message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.auctionimbalance19message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 20) {
            values[entry + ".payload"] = "packet.message.payload.priceband20message";
            [[maybe_unused]] const auto* message = protocol::PriceBand20Message::parse(iterator.message);
            values[entry + ".payload.priceband20message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.priceband20message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.priceband20message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.priceband20message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.priceband20message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.priceband20message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.priceband20message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.priceband20message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.priceband20message.pricebandtype"] = (static_cast<std::uint8_t>(message->price_band_type.get()) != 0x0FFU ? canonical::number(message->price_band_type.get()) : canonical::absent());
            values[entry + ".payload.priceband20message.pricelimittype"] = (static_cast<std::uint8_t>(message->price_limit_type.get()) != 0x0FFU ? canonical::number(message->price_limit_type.get()) : canonical::absent());
            values[entry + ".payload.priceband20message.pricebandmidpointpricetype"] = (static_cast<std::uint8_t>(message->price_band_midpoint_price_type.get()) != 0x0FFU ? canonical::number(message->price_band_midpoint_price_type.get()) : canonical::absent());
            values[entry + ".payload.priceband20message.lowlimitprice"] = (static_cast<std::uint64_t>(message->low_limit_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->low_limit_price.integer(), -4) : canonical::absent());
            values[entry + ".payload.priceband20message.highlimitprice"] = (static_cast<std::uint64_t>(message->high_limit_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->high_limit_price.integer(), -4) : canonical::absent());
            values[entry + ".payload.priceband20message.tradingreferencepricelegacy"] = (static_cast<std::uint64_t>(message->trading_reference_price_legacy.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->trading_reference_price_legacy.integer(), -4) : canonical::absent());
            values[entry + ".payload.priceband20message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.priceband20message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 21) {
            values[entry + ".payload"] = "packet.message.payload.quantityband21message";
            [[maybe_unused]] const auto* message = protocol::QuantityBand21Message::parse(iterator.message);
            values[entry + ".payload.quantityband21message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.quantityband21message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.quantityband21message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.quantityband21message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.quantityband21message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.quantityband21message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.quantityband21message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.quantityband21message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.quantityband21message.avgdailytradedqty"] = (static_cast<std::uint64_t>(message->avg_daily_traded_qty.get()) != 0x08000000000000000ULL ? canonical::number(message->avg_daily_traded_qty.get()) : canonical::absent());
            values[entry + ".payload.quantityband21message.maxtradevol"] = (static_cast<std::uint64_t>(message->max_trade_vol.get()) != 0x08000000000000000ULL ? canonical::number(message->max_trade_vol.get()) : canonical::absent());
            values[entry + ".payload.quantityband21message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.quantityband21message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 22) {
            values[entry + ".payload"] = "packet.message.payload.priceband22message";
            [[maybe_unused]] const auto* message = protocol::PriceBand22Message::parse(iterator.message);
            values[entry + ".payload.priceband22message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.priceband22message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.priceband22message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.priceband22message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.priceband22message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.priceband22message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.priceband22message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.priceband22message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.priceband22message.pricebandtype"] = (static_cast<std::uint8_t>(message->price_band_type.get()) != 0x0FFU ? canonical::number(message->price_band_type.get()) : canonical::absent());
            values[entry + ".payload.priceband22message.pricelimittype"] = (static_cast<std::uint8_t>(message->price_limit_type.get()) != 0x0FFU ? canonical::number(message->price_limit_type.get()) : canonical::absent());
            values[entry + ".payload.priceband22message.pricebandmidpointpricetype"] = (static_cast<std::uint8_t>(message->price_band_midpoint_price_type.get()) != 0x0FFU ? canonical::number(message->price_band_midpoint_price_type.get()) : canonical::absent());
            values[entry + ".payload.priceband22message.lowlimitprice"] = (static_cast<std::uint64_t>(message->low_limit_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->low_limit_price.integer(), -4) : canonical::absent());
            values[entry + ".payload.priceband22message.highlimitprice"] = (static_cast<std::uint64_t>(message->high_limit_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->high_limit_price.integer(), -4) : canonical::absent());
            values[entry + ".payload.priceband22message.tradingreferencepriceoptional"] = (static_cast<std::uint64_t>(message->trading_reference_price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->trading_reference_price_optional.integer(), -8) : canonical::absent());
            values[entry + ".payload.priceband22message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.priceband22message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 24) {
            values[entry + ".payload"] = "packet.message.payload.highprice24message";
            [[maybe_unused]] const auto* message = protocol::HighPrice24Message::parse(iterator.message);
            values[entry + ".payload.highprice24message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.highprice24message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.highprice24message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.highprice24message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.highprice24message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.highprice24message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.highprice24message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.highprice24message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.highprice24message.mdupdateaction"] = canonical::number(message->md_update_action.get());
            values[entry + ".payload.highprice24message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.highprice24message.mdfutureprice"] = canonical::scaled(message->md_future_price.integer(), -4);
            values[entry + ".payload.highprice24message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.highprice24message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 25) {
            values[entry + ".payload"] = "packet.message.payload.lowprice25message";
            [[maybe_unused]] const auto* message = protocol::LowPrice25Message::parse(iterator.message);
            values[entry + ".payload.lowprice25message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.lowprice25message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.lowprice25message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.lowprice25message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.lowprice25message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.lowprice25message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.lowprice25message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.lowprice25message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.lowprice25message.mdupdateaction"] = canonical::number(message->md_update_action.get());
            values[entry + ".payload.lowprice25message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.lowprice25message.mdfutureprice"] = canonical::scaled(message->md_future_price.integer(), -4);
            values[entry + ".payload.lowprice25message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.lowprice25message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 27) {
            values[entry + ".payload"] = "packet.message.payload.lasttradeprice27message";
            [[maybe_unused]] const auto* message = protocol::LastTradePrice27Message::parse(iterator.message);
            values[entry + ".payload.lasttradeprice27message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.lasttradeprice27message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.lasttradeprice27message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.lasttradeprice27message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.lasttradeprice27message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.lasttradeprice27message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.lasttradeprice27message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.lasttradeprice27message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.lasttradeprice27message.tradingsessionid"] = canonical::number(message->trading_session_id.get());
            values[entry + ".payload.lasttradeprice27message.tradecondition.openingprice"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.OpeningPrice()));
            values[entry + ".payload.lasttradeprice27message.tradecondition.crossed"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.Crossed()));
            values[entry + ".payload.lasttradeprice27message.tradecondition.lasttradeatthesameprice"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.LastTradeAtTheSamePrice()));
            values[entry + ".payload.lasttradeprice27message.tradecondition.outofsequence"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.OutOfSequence()));
            values[entry + ".payload.lasttradeprice27message.tradecondition.tradeonbehalf"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.TradeOnBehalf()));
            values[entry + ".payload.lasttradeprice27message.tradecondition.regulartrade"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.RegularTrade()));
            values[entry + ".payload.lasttradeprice27message.tradecondition.blocktrade"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.BlockTrade()));
            values[entry + ".payload.lasttradeprice27message.mdfutureprice"] = canonical::scaled(message->md_future_price.integer(), -4);
            values[entry + ".payload.lasttradeprice27message.mdentrysize"] = canonical::number(message->md_entry_size.get());
            values[entry + ".payload.lasttradeprice27message.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.lasttradeprice27message.mdentrybuyer"] = (static_cast<std::uint32_t>(message->md_entry_buyer.get()) != 0x0U ? canonical::number(message->md_entry_buyer.get()) : canonical::absent());
            values[entry + ".payload.lasttradeprice27message.mdentryseller"] = (static_cast<std::uint32_t>(message->md_entry_seller.get()) != 0x0U ? canonical::number(message->md_entry_seller.get()) : canonical::absent());
            values[entry + ".payload.lasttradeprice27message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.lasttradeprice27message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.lasttradeprice27message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
            values[entry + ".payload.lasttradeprice27message.sellerdays"] = (static_cast<std::uint16_t>(message->seller_days.get()) != 0x0U ? canonical::number(message->seller_days.get()) : canonical::absent());
            values[entry + ".payload.lasttradeprice27message.mdentryinterestrate"] = (static_cast<std::uint64_t>(message->md_entry_interest_rate.integer()) != 0x0ULL ? canonical::scaled(message->md_entry_interest_rate.integer(), -4) : canonical::absent());
            values[entry + ".payload.lasttradeprice27message.trdsubtype"] = (static_cast<std::uint8_t>(message->trd_sub_type.get()) != 0x0U ? canonical::number(message->trd_sub_type.get()) : canonical::absent());
        } else if (iterator.template_id == 28) {
            values[entry + ".payload"] = "packet.message.payload.settlementprice28message";
            [[maybe_unused]] const auto* message = protocol::SettlementPrice28Message::parse(iterator.message);
            values[entry + ".payload.settlementprice28message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.settlementprice28message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.settlementprice28message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.settlementprice28message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.settlementprice28message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.settlementprice28message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.settlementprice28message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.settlementprice28message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.settlementprice28message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.settlementprice28message.mdfutureprice"] = canonical::scaled(message->md_future_price.integer(), -4);
            values[entry + ".payload.settlementprice28message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.settlementprice28message.openclosesettlflag"] = canonical::number(message->open_close_settl_flag.get());
            values[entry + ".payload.settlementprice28message.pricetype"] = canonical::number(message->price_type.get());
            values[entry + ".payload.settlementprice28message.settlpricetype"] = canonical::number(message->settl_price_type.get());
            values[entry + ".payload.settlementprice28message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 29) {
            values[entry + ".payload"] = "packet.message.payload.openinterest29message";
            [[maybe_unused]] const auto* message = protocol::OpenInterest29Message::parse(iterator.message);
            values[entry + ".payload.openinterest29message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.openinterest29message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.openinterest29message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.openinterest29message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.openinterest29message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.openinterest29message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.openinterest29message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.openinterest29message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.openinterest29message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.openinterest29message.mdentrysize"] = canonical::number(message->md_entry_size.get());
            values[entry + ".payload.openinterest29message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.openinterest29message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 30) {
            values[entry + ".payload"] = "packet.message.payload.snapshotfullrefreshheader30message";
            [[maybe_unused]] const auto* message = protocol::SnapshotFullRefreshHeader30Message::parse(iterator.message);
            values[entry + ".payload.snapshotfullrefreshheader30message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.snapshotfullrefreshheader30message.lastmsgseqnumprocessed"] = canonical::number(message->last_msg_seq_num_processed.get());
            values[entry + ".payload.snapshotfullrefreshheader30message.totnumreports"] = canonical::number(message->tot_num_reports.get());
            values[entry + ".payload.snapshotfullrefreshheader30message.totnumbids"] = canonical::number(message->tot_num_bids.get());
            values[entry + ".payload.snapshotfullrefreshheader30message.totnumoffers"] = canonical::number(message->tot_num_offers.get());
            values[entry + ".payload.snapshotfullrefreshheader30message.totnumstats"] = canonical::number(message->tot_num_stats.get());
            values[entry + ".payload.snapshotfullrefreshheader30message.lastrptseq"] = (static_cast<std::uint32_t>(message->last_rpt_seq.get()) != 0x0U ? canonical::number(message->last_rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 50) {
            values[entry + ".payload"] = "packet.message.payload.ordermbo50message";
            [[maybe_unused]] const auto* message = protocol::OrderMbO50Message::parse(iterator.message);
            values[entry + ".payload.ordermbo50message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.ordermbo50message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.ordermbo50message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.ordermbo50message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.ordermbo50message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.ordermbo50message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.ordermbo50message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.ordermbo50message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.ordermbo50message.mdupdateaction"] = canonical::number(message->md_update_action.get());
            values[entry + ".payload.ordermbo50message.mdentrytype"] = canonical::text(canonical::character(message->md_entry_type.get()));
            values[entry + ".payload.ordermbo50message.mdcorporateoffsetpriceoptional"] = (static_cast<std::uint64_t>(message->md_corporate_offset_price_optional.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->md_corporate_offset_price_optional.integer(), -4) : canonical::absent());
            values[entry + ".payload.ordermbo50message.mdentrysize"] = canonical::number(message->md_entry_size.get());
            values[entry + ".payload.ordermbo50message.mdentrypositionno"] = canonical::number(message->md_entry_position_no.get());
            values[entry + ".payload.ordermbo50message.enteringfirm"] = (static_cast<std::uint32_t>(message->entering_firm.get()) != 0x0U ? canonical::number(message->entering_firm.get()) : canonical::absent());
            values[entry + ".payload.ordermbo50message.mdinserttimestamp"] = (static_cast<std::uint64_t>(message->md_insert_timestamp.get()) != 0x0ULL ? canonical::number(message->md_insert_timestamp.get()) : canonical::absent());
            values[entry + ".payload.ordermbo50message.secondaryorderid"] = canonical::number(message->secondary_order_id.get());
            values[entry + ".payload.ordermbo50message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
            values[entry + ".payload.ordermbo50message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
        } else if (iterator.template_id == 51) {
            values[entry + ".payload"] = "packet.message.payload.deleteordermbo51message";
            [[maybe_unused]] const auto* message = protocol::DeleteOrderMbO51Message::parse(iterator.message);
            values[entry + ".payload.deleteordermbo51message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.deleteordermbo51message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.deleteordermbo51message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.deleteordermbo51message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.deleteordermbo51message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.deleteordermbo51message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.deleteordermbo51message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.deleteordermbo51message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.deleteordermbo51message.mdentrytype"] = canonical::text(canonical::character(message->md_entry_type.get()));
            values[entry + ".payload.deleteordermbo51message.mdentrypositionno"] = canonical::number(message->md_entry_position_no.get());
            values[entry + ".payload.deleteordermbo51message.mdentrysizeoptional"] = (static_cast<std::uint64_t>(message->md_entry_size_optional.get()) != 0x08000000000000000ULL ? canonical::number(message->md_entry_size_optional.get()) : canonical::absent());
            values[entry + ".payload.deleteordermbo51message.secondaryorderid"] = canonical::number(message->secondary_order_id.get());
            values[entry + ".payload.deleteordermbo51message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.deleteordermbo51message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 52) {
            values[entry + ".payload"] = "packet.message.payload.massdeleteordersmbo52message";
            [[maybe_unused]] const auto* message = protocol::MassDeleteOrdersMbO52Message::parse(iterator.message);
            values[entry + ".payload.massdeleteordersmbo52message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.massdeleteordersmbo52message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.massdeleteordersmbo52message.mdupdateaction"] = canonical::number(message->md_update_action.get());
            values[entry + ".payload.massdeleteordersmbo52message.mdentrytype"] = canonical::text(canonical::character(message->md_entry_type.get()));
            values[entry + ".payload.massdeleteordersmbo52message.mdentrypositionno"] = canonical::number(message->md_entry_position_no.get());
            values[entry + ".payload.massdeleteordersmbo52message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.massdeleteordersmbo52message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 53) {
            values[entry + ".payload"] = "packet.message.payload.trade53message";
            [[maybe_unused]] const auto* message = protocol::Trade53Message::parse(iterator.message);
            values[entry + ".payload.trade53message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.trade53message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.trade53message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.trade53message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.trade53message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.trade53message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.trade53message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.trade53message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.trade53message.tradingsessionid"] = canonical::number(message->trading_session_id.get());
            values[entry + ".payload.trade53message.tradecondition.openingprice"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.OpeningPrice()));
            values[entry + ".payload.trade53message.tradecondition.crossed"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.Crossed()));
            values[entry + ".payload.trade53message.tradecondition.lasttradeatthesameprice"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.LastTradeAtTheSamePrice()));
            values[entry + ".payload.trade53message.tradecondition.outofsequence"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.OutOfSequence()));
            values[entry + ".payload.trade53message.tradecondition.tradeonbehalf"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.TradeOnBehalf()));
            values[entry + ".payload.trade53message.tradecondition.regulartrade"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.RegularTrade()));
            values[entry + ".payload.trade53message.tradecondition.blocktrade"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.BlockTrade()));
            values[entry + ".payload.trade53message.mdfutureprice"] = canonical::scaled(message->md_future_price.integer(), -4);
            values[entry + ".payload.trade53message.mdentrysize"] = canonical::number(message->md_entry_size.get());
            values[entry + ".payload.trade53message.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.trade53message.mdentrybuyer"] = (static_cast<std::uint32_t>(message->md_entry_buyer.get()) != 0x0U ? canonical::number(message->md_entry_buyer.get()) : canonical::absent());
            values[entry + ".payload.trade53message.mdentryseller"] = (static_cast<std::uint32_t>(message->md_entry_seller.get()) != 0x0U ? canonical::number(message->md_entry_seller.get()) : canonical::absent());
            values[entry + ".payload.trade53message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.trade53message.trdsubtype"] = (static_cast<std::uint8_t>(message->trd_sub_type.get()) != 0x0U ? canonical::number(message->trd_sub_type.get()) : canonical::absent());
            values[entry + ".payload.trade53message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.trade53message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 54) {
            values[entry + ".payload"] = "packet.message.payload.forwardtrade54message";
            [[maybe_unused]] const auto* message = protocol::ForwardTrade54Message::parse(iterator.message);
            values[entry + ".payload.forwardtrade54message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.forwardtrade54message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.forwardtrade54message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.forwardtrade54message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.forwardtrade54message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.forwardtrade54message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.forwardtrade54message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.forwardtrade54message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.forwardtrade54message.tradingsessionid"] = canonical::number(message->trading_session_id.get());
            values[entry + ".payload.forwardtrade54message.tradecondition.openingprice"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.OpeningPrice()));
            values[entry + ".payload.forwardtrade54message.tradecondition.crossed"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.Crossed()));
            values[entry + ".payload.forwardtrade54message.tradecondition.lasttradeatthesameprice"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.LastTradeAtTheSamePrice()));
            values[entry + ".payload.forwardtrade54message.tradecondition.outofsequence"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.OutOfSequence()));
            values[entry + ".payload.forwardtrade54message.tradecondition.tradeonbehalf"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.TradeOnBehalf()));
            values[entry + ".payload.forwardtrade54message.tradecondition.regulartrade"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.RegularTrade()));
            values[entry + ".payload.forwardtrade54message.tradecondition.blocktrade"] = canonical::number(static_cast<std::uint64_t>(message->trade_condition.BlockTrade()));
            values[entry + ".payload.forwardtrade54message.mdfutureprice"] = canonical::scaled(message->md_future_price.integer(), -4);
            values[entry + ".payload.forwardtrade54message.mdentrysize"] = canonical::number(message->md_entry_size.get());
            values[entry + ".payload.forwardtrade54message.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.forwardtrade54message.mdentrybuyer"] = (static_cast<std::uint32_t>(message->md_entry_buyer.get()) != 0x0U ? canonical::number(message->md_entry_buyer.get()) : canonical::absent());
            values[entry + ".payload.forwardtrade54message.mdentryseller"] = (static_cast<std::uint32_t>(message->md_entry_seller.get()) != 0x0U ? canonical::number(message->md_entry_seller.get()) : canonical::absent());
            values[entry + ".payload.forwardtrade54message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.forwardtrade54message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.forwardtrade54message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
            values[entry + ".payload.forwardtrade54message.sellerdays"] = (static_cast<std::uint16_t>(message->seller_days.get()) != 0x0U ? canonical::number(message->seller_days.get()) : canonical::absent());
            values[entry + ".payload.forwardtrade54message.mdentryinterestrate"] = (static_cast<std::uint64_t>(message->md_entry_interest_rate.integer()) != 0x0ULL ? canonical::scaled(message->md_entry_interest_rate.integer(), -4) : canonical::absent());
            values[entry + ".payload.forwardtrade54message.trdsubtype"] = (static_cast<std::uint8_t>(message->trd_sub_type.get()) != 0x0U ? canonical::number(message->trd_sub_type.get()) : canonical::absent());
        } else if (iterator.template_id == 55) {
            values[entry + ".payload"] = "packet.message.payload.executionsummary55message";
            [[maybe_unused]] const auto* message = protocol::ExecutionSummary55Message::parse(iterator.message);
            values[entry + ".payload.executionsummary55message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.executionsummary55message.aggressorside"] = canonical::number(message->aggressor_side.get());
            values[entry + ".payload.executionsummary55message.lastpx"] = canonical::scaled(message->last_px.integer(), -4);
            values[entry + ".payload.executionsummary55message.fillqty"] = canonical::number(message->fill_qty.get());
            values[entry + ".payload.executionsummary55message.tradedhiddenqty"] = (static_cast<std::uint64_t>(message->traded_hidden_qty.get()) != 0x08000000000000000ULL ? canonical::number(message->traded_hidden_qty.get()) : canonical::absent());
            values[entry + ".payload.executionsummary55message.cxlqty"] = (static_cast<std::uint64_t>(message->cxl_qty.get()) != 0x08000000000000000ULL ? canonical::number(message->cxl_qty.get()) : canonical::absent());
            values[entry + ".payload.executionsummary55message.aggressortime"] = (static_cast<std::uint64_t>(message->aggressor_time.get()) != 0x0ULL ? canonical::number(message->aggressor_time.get()) : canonical::absent());
            values[entry + ".payload.executionsummary55message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
            values[entry + ".payload.executionsummary55message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
        } else if (iterator.template_id == 56) {
            values[entry + ".payload"] = "packet.message.payload.executionstatistics56message";
            [[maybe_unused]] const auto* message = protocol::ExecutionStatistics56Message::parse(iterator.message);
            values[entry + ".payload.executionstatistics56message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.executionstatistics56message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.executionstatistics56message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.executionstatistics56message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.executionstatistics56message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.executionstatistics56message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.executionstatistics56message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.executionstatistics56message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.executionstatistics56message.tradingsessionid"] = canonical::number(message->trading_session_id.get());
            values[entry + ".payload.executionstatistics56message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.executionstatistics56message.tradevolume"] = canonical::number(message->trade_volume.get());
            values[entry + ".payload.executionstatistics56message.vwappx"] = (static_cast<std::uint64_t>(message->vwap_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->vwap_px.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionstatistics56message.netchgprevday"] = (static_cast<std::uint64_t>(message->net_chg_prev_day.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->net_chg_prev_day.integer(), -8) : canonical::absent());
            values[entry + ".payload.executionstatistics56message.numberoftrades"] = canonical::number(message->number_of_trades.get());
            values[entry + ".payload.executionstatistics56message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.executionstatistics56message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 57) {
            values[entry + ".payload"] = "packet.message.payload.tradebust57message";
            [[maybe_unused]] const auto* message = protocol::TradeBust57Message::parse(iterator.message);
            values[entry + ".payload.tradebust57message.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.tradebust57message.matcheventindicator.lasttrademsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastTradeMsg()));
            values[entry + ".payload.tradebust57message.matcheventindicator.lastvolumemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastVolumeMsg()));
            values[entry + ".payload.tradebust57message.matcheventindicator.lastquotemsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastQuoteMsg()));
            values[entry + ".payload.tradebust57message.matcheventindicator.laststatsmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastStatsMsg()));
            values[entry + ".payload.tradebust57message.matcheventindicator.lastimpliedmsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.LastImpliedMsg()));
            values[entry + ".payload.tradebust57message.matcheventindicator.recoverymsg"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.RecoveryMsg()));
            values[entry + ".payload.tradebust57message.matcheventindicator.endofevent"] = canonical::number(static_cast<std::uint64_t>(message->match_event_indicator.EndOfEvent()));
            values[entry + ".payload.tradebust57message.tradingsessionid"] = canonical::number(message->trading_session_id.get());
            values[entry + ".payload.tradebust57message.mdfutureprice"] = canonical::scaled(message->md_future_price.integer(), -4);
            values[entry + ".payload.tradebust57message.mdentrysize"] = canonical::number(message->md_entry_size.get());
            values[entry + ".payload.tradebust57message.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.tradebust57message.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.tradebust57message.mdentrytimestamp"] = (static_cast<std::uint64_t>(message->md_entry_timestamp.get()) != 0x0ULL ? canonical::number(message->md_entry_timestamp.get()) : canonical::absent());
            values[entry + ".payload.tradebust57message.rptseq"] = (static_cast<std::uint32_t>(message->rpt_seq.get()) != 0x0U ? canonical::number(message->rpt_seq.get()) : canonical::absent());
        } else if (iterator.template_id == 71) {
            values[entry + ".payload"] = "packet.message.payload.snapshotfullrefreshordersmbo71message";
            [[maybe_unused]] const auto* message = protocol::SnapshotFullRefreshOrdersMbO71Message::parse(iterator.message);
            values[entry + ".payload.snapshotfullrefreshordersmbo71message.securityid"] = canonical::number(message->security_id.get());
        }
    }

    return values;
}

// Read each datagram of a sample with Modern and hold it to the model's values
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
    std::printf("== B3.B3Derivatives.BinaryUmdf.Sbe.v1.8 (modern values)\n");
    int failures = 0;
    failures += check("SecurityDefinitionMessage", "B3/B3Derivatives.BinaryUmdf.Sbe.v1.8/SecurityDefinitionMessage.pcap", "b3/b3derivatives/binaryumdf/sbe/v1.8/SecurityDefinitionMessage.values");
    failures += check("SequenceMessage", "B3/B3Derivatives.BinaryUmdf.Sbe.v1.8/SequenceMessage.pcap", "b3/b3derivatives/binaryumdf/sbe/v1.8/SequenceMessage.values");
    return failures == 0 ? 0 : 1;
}
