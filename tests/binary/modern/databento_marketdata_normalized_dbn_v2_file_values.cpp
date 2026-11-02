// Databento.MarketData.Normalized.Dbn.v2 canonical values of 'file', through the Modern iterator: every value
// Modern reads from each file, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "decompressor/Detect.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/modern/databento/marketdata/normalized/dbn/v2/definitions.hpp"

namespace protocol = ::databento::marketdata::normalized::dbn::v2;

namespace {

// An unsigned number of the width given, in the byte order given
std::uint64_t unsigned_at(const std::byte* at, std::size_t width, bool big) {
    std::uint64_t value = 0;

    for (std::size_t index = 0; index < width; ++index) {
        std::size_t position = width - 1 - index;

        if (big) {
            position = index;
        }

        value = (value << 8) | std::to_integer<std::uint64_t>(at[position]);
    }

    return value;
}

// Where the records start: past Metadata, or past the end where the bytes end inside it
std::size_t start(const std::byte* data, std::size_t length) {
    std::size_t at = 0;

    // Metadata
    if (length < at + 8) {
        return length + 1;
    }
    at += static_cast<std::size_t>(unsigned_at(data + at + 4, 4, false) + 8);

    return at;
}

// The values the Modern iterator reads from one stream of 'file', by indexed address
canonical::Listing read(const std::byte* data, std::size_t length) {
    canonical::Listing values;
    protocol::RecordIterator iterator;
    const std::size_t first = start(data, length);

    if (first > length) {
        values["(does not decode)"] = "the bytes end inside what the file opens with";
        return values;
    }

    iterator.initialize(data + first, length - first);

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "file.record[" + std::to_string(index++) + "]";

        // the iterator steps past a record the bytes end inside; its values are not read
        if (iterator.current > iterator.end) {
            values[entry] = "(ends inside the record)";
            break;
        }

        values[entry + ".recordheader.recordlength"] = canonical::number(iterator.record->record_header.record_length.get());
        values[entry + ".recordheader.rtype"] = canonical::number(iterator.record->record_header.rtype.get());
        values[entry + ".recordheader.publisherid"] = canonical::number(iterator.record->record_header.publisher_id.get());
        values[entry + ".recordheader.instrumentid"] = canonical::number(iterator.record->record_header.instrument_id.get());
        values[entry + ".recordheader.tsevent"] = (static_cast<std::uint64_t>(iterator.record->record_header.ts_event.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(iterator.record->record_header.ts_event.get()) : canonical::absent());

        if (iterator.rtype == 0) {
            values[entry + ".recordbody"] = "file.record.recordbody.trademsg";
            [[maybe_unused]] const auto* message = protocol::TradeMsg::parse(iterator.message);
            values[entry + ".recordbody.trademsg.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.trademsg.size"] = canonical::number(message->size.get());
            values[entry + ".recordbody.trademsg.action"] = canonical::text(canonical::character(message->action.get()));
            values[entry + ".recordbody.trademsg.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".recordbody.trademsg.flags.reservedflag"] = canonical::number(static_cast<std::uint64_t>(message->flags.ReservedFlag()));
            values[entry + ".recordbody.trademsg.flags.publisherspecific"] = canonical::number(static_cast<std::uint64_t>(message->flags.PublisherSpecific()));
            values[entry + ".recordbody.trademsg.flags.maybebadbook"] = canonical::number(static_cast<std::uint64_t>(message->flags.MaybeBadBook()));
            values[entry + ".recordbody.trademsg.flags.badtsrecv"] = canonical::number(static_cast<std::uint64_t>(message->flags.BadTsRecv()));
            values[entry + ".recordbody.trademsg.flags.mbp"] = canonical::number(static_cast<std::uint64_t>(message->flags.Mbp()));
            values[entry + ".recordbody.trademsg.flags.snapshot"] = canonical::number(static_cast<std::uint64_t>(message->flags.Snapshot()));
            values[entry + ".recordbody.trademsg.flags.tob"] = canonical::number(static_cast<std::uint64_t>(message->flags.Tob()));
            values[entry + ".recordbody.trademsg.flags.last"] = canonical::number(static_cast<std::uint64_t>(message->flags.Last()));
            values[entry + ".recordbody.trademsg.depth"] = canonical::number(message->depth.get());
            values[entry + ".recordbody.trademsg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.trademsg.tsindelta"] = canonical::number(message->ts_in_delta.get());
            values[entry + ".recordbody.trademsg.sequence"] = canonical::number(message->sequence.get());
        } else if (iterator.rtype == 1) {
            values[entry + ".recordbody"] = "file.record.recordbody.mbp1msg";
            [[maybe_unused]] const auto* message = protocol::Mbp1Msg::parse(iterator.message);
            values[entry + ".recordbody.mbp1msg.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.mbp1msg.size"] = canonical::number(message->size.get());
            values[entry + ".recordbody.mbp1msg.action"] = canonical::text(canonical::character(message->action.get()));
            values[entry + ".recordbody.mbp1msg.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".recordbody.mbp1msg.flags.reservedflag"] = canonical::number(static_cast<std::uint64_t>(message->flags.ReservedFlag()));
            values[entry + ".recordbody.mbp1msg.flags.publisherspecific"] = canonical::number(static_cast<std::uint64_t>(message->flags.PublisherSpecific()));
            values[entry + ".recordbody.mbp1msg.flags.maybebadbook"] = canonical::number(static_cast<std::uint64_t>(message->flags.MaybeBadBook()));
            values[entry + ".recordbody.mbp1msg.flags.badtsrecv"] = canonical::number(static_cast<std::uint64_t>(message->flags.BadTsRecv()));
            values[entry + ".recordbody.mbp1msg.flags.mbp"] = canonical::number(static_cast<std::uint64_t>(message->flags.Mbp()));
            values[entry + ".recordbody.mbp1msg.flags.snapshot"] = canonical::number(static_cast<std::uint64_t>(message->flags.Snapshot()));
            values[entry + ".recordbody.mbp1msg.flags.tob"] = canonical::number(static_cast<std::uint64_t>(message->flags.Tob()));
            values[entry + ".recordbody.mbp1msg.flags.last"] = canonical::number(static_cast<std::uint64_t>(message->flags.Last()));
            values[entry + ".recordbody.mbp1msg.depth"] = canonical::number(message->depth.get());
            values[entry + ".recordbody.mbp1msg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.mbp1msg.tsindelta"] = canonical::number(message->ts_in_delta.get());
            values[entry + ".recordbody.mbp1msg.sequence"] = canonical::number(message->sequence.get());
            values[entry + ".recordbody.mbp1msg.bidaskpair.bidpx"] = (static_cast<std::uint64_t>(message->bid_ask_pair.bid_px.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->bid_ask_pair.bid_px.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.mbp1msg.bidaskpair.askpx"] = (static_cast<std::uint64_t>(message->bid_ask_pair.ask_px.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->bid_ask_pair.ask_px.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.mbp1msg.bidaskpair.bidsz"] = canonical::number(message->bid_ask_pair.bid_sz.get());
            values[entry + ".recordbody.mbp1msg.bidaskpair.asksz"] = canonical::number(message->bid_ask_pair.ask_sz.get());
            values[entry + ".recordbody.mbp1msg.bidaskpair.bidct"] = canonical::number(message->bid_ask_pair.bid_ct.get());
            values[entry + ".recordbody.mbp1msg.bidaskpair.askct"] = canonical::number(message->bid_ask_pair.ask_ct.get());
        } else if (iterator.rtype == 10) {
            values[entry + ".recordbody"] = "file.record.recordbody.mbp10msg";
            [[maybe_unused]] const auto* message = protocol::Mbp10Msg::parse(iterator.message);
            values[entry + ".recordbody.mbp10msg.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.mbp10msg.size"] = canonical::number(message->size.get());
            values[entry + ".recordbody.mbp10msg.action"] = canonical::text(canonical::character(message->action.get()));
            values[entry + ".recordbody.mbp10msg.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".recordbody.mbp10msg.flags.reservedflag"] = canonical::number(static_cast<std::uint64_t>(message->flags.ReservedFlag()));
            values[entry + ".recordbody.mbp10msg.flags.publisherspecific"] = canonical::number(static_cast<std::uint64_t>(message->flags.PublisherSpecific()));
            values[entry + ".recordbody.mbp10msg.flags.maybebadbook"] = canonical::number(static_cast<std::uint64_t>(message->flags.MaybeBadBook()));
            values[entry + ".recordbody.mbp10msg.flags.badtsrecv"] = canonical::number(static_cast<std::uint64_t>(message->flags.BadTsRecv()));
            values[entry + ".recordbody.mbp10msg.flags.mbp"] = canonical::number(static_cast<std::uint64_t>(message->flags.Mbp()));
            values[entry + ".recordbody.mbp10msg.flags.snapshot"] = canonical::number(static_cast<std::uint64_t>(message->flags.Snapshot()));
            values[entry + ".recordbody.mbp10msg.flags.tob"] = canonical::number(static_cast<std::uint64_t>(message->flags.Tob()));
            values[entry + ".recordbody.mbp10msg.flags.last"] = canonical::number(static_cast<std::uint64_t>(message->flags.Last()));
            values[entry + ".recordbody.mbp10msg.depth"] = canonical::number(message->depth.get());
            values[entry + ".recordbody.mbp10msg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.mbp10msg.tsindelta"] = canonical::number(message->ts_in_delta.get());
            values[entry + ".recordbody.mbp10msg.sequence"] = canonical::number(message->sequence.get());
        } else if (iterator.rtype == 17 || iterator.rtype == 32 || iterator.rtype == 33 || iterator.rtype == 34 || iterator.rtype == 35 || iterator.rtype == 36) {
            values[entry + ".recordbody"] = "file.record.recordbody.ohlcvmsg";
            [[maybe_unused]] const auto* message = protocol::OhlcvMsg::parse(iterator.message);
            values[entry + ".recordbody.ohlcvmsg.open"] = (static_cast<std::uint64_t>(message->open.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->open.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.ohlcvmsg.high"] = (static_cast<std::uint64_t>(message->high.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->high.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.ohlcvmsg.low"] = (static_cast<std::uint64_t>(message->low.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->low.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.ohlcvmsg.close"] = (static_cast<std::uint64_t>(message->close.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->close.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.ohlcvmsg.volume"] = canonical::number(message->volume.get());
        } else if (iterator.rtype == 18) {
            values[entry + ".recordbody"] = "file.record.recordbody.statusmsg";
            [[maybe_unused]] const auto* message = protocol::StatusMsg::parse(iterator.message);
            values[entry + ".recordbody.statusmsg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.statusmsg.statusaction"] = canonical::number(message->status_action.get());
            values[entry + ".recordbody.statusmsg.statusreason"] = canonical::number(message->status_reason.get());
            values[entry + ".recordbody.statusmsg.tradingevent"] = canonical::number(message->trading_event.get());
            values[entry + ".recordbody.statusmsg.istrading"] = canonical::text(canonical::character(message->is_trading.get()));
            values[entry + ".recordbody.statusmsg.isquoting"] = canonical::text(canonical::character(message->is_quoting.get()));
            values[entry + ".recordbody.statusmsg.isshortsellrestricted"] = canonical::text(canonical::character(message->is_short_sell_restricted.get()));
        } else if (iterator.rtype == 19) {
            values[entry + ".recordbody"] = "file.record.recordbody.instrumentdefmsg";
            [[maybe_unused]] const auto* message = protocol::InstrumentDefMsg::parse(iterator.message);
            values[entry + ".recordbody.instrumentdefmsg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.minpriceincrement"] = (static_cast<std::uint64_t>(message->min_price_increment.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->min_price_increment.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.displayfactor"] = (static_cast<std::uint64_t>(message->display_factor.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->display_factor.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.expiration"] = (static_cast<std::uint64_t>(message->expiration.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->expiration.get()) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.activation"] = (static_cast<std::uint64_t>(message->activation.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->activation.get()) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.highlimitprice"] = (static_cast<std::uint64_t>(message->high_limit_price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->high_limit_price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.lowlimitprice"] = (static_cast<std::uint64_t>(message->low_limit_price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->low_limit_price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.maxpricevariation"] = (static_cast<std::uint64_t>(message->max_price_variation.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->max_price_variation.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.tradingreferenceprice"] = (static_cast<std::uint64_t>(message->trading_reference_price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->trading_reference_price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.unitofmeasureqty"] = (static_cast<std::uint64_t>(message->unit_of_measure_qty.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->unit_of_measure_qty.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.minpriceincrementamount"] = (static_cast<std::uint64_t>(message->min_price_increment_amount.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->min_price_increment_amount.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.priceratio"] = (static_cast<std::uint64_t>(message->price_ratio.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->price_ratio.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.strikeprice"] = (static_cast<std::uint64_t>(message->strike_price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->strike_price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.instrumentdefmsg.instattribvalue"] = canonical::number(message->inst_attrib_value.get());
            values[entry + ".recordbody.instrumentdefmsg.underlyingid"] = canonical::number(message->underlying_id.get());
            values[entry + ".recordbody.instrumentdefmsg.rawinstrumentid"] = canonical::number(message->raw_instrument_id.get());
            values[entry + ".recordbody.instrumentdefmsg.marketdepthimplied"] = canonical::number(message->market_depth_implied.get());
            values[entry + ".recordbody.instrumentdefmsg.marketdepth"] = canonical::number(message->market_depth.get());
            values[entry + ".recordbody.instrumentdefmsg.marketsegmentid"] = canonical::number(message->market_segment_id.get());
            values[entry + ".recordbody.instrumentdefmsg.maxtradevol"] = canonical::number(message->max_trade_vol.get());
            values[entry + ".recordbody.instrumentdefmsg.minlotsize"] = canonical::number(message->min_lot_size.get());
            values[entry + ".recordbody.instrumentdefmsg.minlotsizeblock"] = canonical::number(message->min_lot_size_block.get());
            values[entry + ".recordbody.instrumentdefmsg.minlotsizeroundlot"] = canonical::number(message->min_lot_size_round_lot.get());
            values[entry + ".recordbody.instrumentdefmsg.mintradevol"] = canonical::number(message->min_trade_vol.get());
            values[entry + ".recordbody.instrumentdefmsg.contractmultiplier"] = canonical::number(message->contract_multiplier.get());
            values[entry + ".recordbody.instrumentdefmsg.decayquantity"] = canonical::number(message->decay_quantity.get());
            values[entry + ".recordbody.instrumentdefmsg.originalcontractsize"] = canonical::number(message->original_contract_size.get());
            values[entry + ".recordbody.instrumentdefmsg.tradingreferencedate"] = canonical::number(message->trading_reference_date.get());
            values[entry + ".recordbody.instrumentdefmsg.applid"] = canonical::number(message->appl_id.get());
            values[entry + ".recordbody.instrumentdefmsg.maturityyear"] = canonical::number(message->maturity_year.get());
            values[entry + ".recordbody.instrumentdefmsg.decaystartdate"] = canonical::number(message->decay_start_date.get());
            values[entry + ".recordbody.instrumentdefmsg.channel"] = canonical::number(message->channel.get());
            values[entry + ".recordbody.instrumentdefmsg.currency"] = canonical::text(std::string(message->currency.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.settlcurrency"] = canonical::text(std::string(message->settl_currency.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.secsubtype"] = canonical::text(std::string(message->secsubtype.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.rawsymbol"] = canonical::text(std::string(message->raw_symbol.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.group"] = canonical::text(std::string(message->group.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.exchange"] = canonical::text(std::string(message->exchange.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.asset"] = canonical::text(std::string(message->asset.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.cfi"] = canonical::text(std::string(message->cfi.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.securitytype"] = canonical::text(std::string(message->security_type.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.unitofmeasure"] = canonical::text(std::string(message->unit_of_measure.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.underlying"] = canonical::text(std::string(message->underlying.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.strikepricecurrency"] = canonical::text(std::string(message->strike_price_currency.get()), '\0', false);
            values[entry + ".recordbody.instrumentdefmsg.instrumentclass"] = canonical::text(canonical::character(message->instrument_class.get()));
            values[entry + ".recordbody.instrumentdefmsg.matchalgorithm"] = canonical::text(canonical::character(message->match_algorithm.get()));
            values[entry + ".recordbody.instrumentdefmsg.mdsecuritytradingstatus"] = canonical::number(message->md_security_trading_status.get());
            values[entry + ".recordbody.instrumentdefmsg.mainfraction"] = canonical::number(message->main_fraction.get());
            values[entry + ".recordbody.instrumentdefmsg.pricedisplayformat"] = canonical::number(message->price_display_format.get());
            values[entry + ".recordbody.instrumentdefmsg.settlpricetype"] = canonical::number(message->settl_price_type.get());
            values[entry + ".recordbody.instrumentdefmsg.subfraction"] = canonical::number(message->sub_fraction.get());
            values[entry + ".recordbody.instrumentdefmsg.underlyingproduct"] = canonical::number(message->underlying_product.get());
            values[entry + ".recordbody.instrumentdefmsg.securityupdateaction"] = canonical::text(canonical::character(message->security_update_action.get()));
            values[entry + ".recordbody.instrumentdefmsg.maturitymonth"] = canonical::number(message->maturity_month.get());
            values[entry + ".recordbody.instrumentdefmsg.maturityday"] = canonical::number(message->maturity_day.get());
            values[entry + ".recordbody.instrumentdefmsg.maturityweek"] = canonical::number(message->maturity_week.get());
            values[entry + ".recordbody.instrumentdefmsg.userdefinedinstrument"] = canonical::text(canonical::character(message->user_defined_instrument.get()));
            values[entry + ".recordbody.instrumentdefmsg.contractmultiplierunit"] = canonical::number(message->contract_multiplier_unit.get());
            values[entry + ".recordbody.instrumentdefmsg.flowscheduletype"] = canonical::number(message->flow_schedule_type.get());
            values[entry + ".recordbody.instrumentdefmsg.tickrule"] = canonical::number(message->tick_rule.get());
        } else if (iterator.rtype == 20) {
            values[entry + ".recordbody"] = "file.record.recordbody.imbalancemsg";
            [[maybe_unused]] const auto* message = protocol::ImbalanceMsg::parse(iterator.message);
            values[entry + ".recordbody.imbalancemsg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.imbalancemsg.refprice"] = (static_cast<std::uint64_t>(message->ref_price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->ref_price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.imbalancemsg.auctiontime"] = (static_cast<std::uint64_t>(message->auction_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->auction_time.get()) : canonical::absent());
            values[entry + ".recordbody.imbalancemsg.contbookclrprice"] = (static_cast<std::uint64_t>(message->cont_book_clr_price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->cont_book_clr_price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.imbalancemsg.auctinterestclrprice"] = (static_cast<std::uint64_t>(message->auct_interest_clr_price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->auct_interest_clr_price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.imbalancemsg.ssrfillingprice"] = (static_cast<std::uint64_t>(message->ssr_filling_price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->ssr_filling_price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.imbalancemsg.indmatchprice"] = (static_cast<std::uint64_t>(message->ind_match_price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->ind_match_price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.imbalancemsg.uppercollar"] = (static_cast<std::uint64_t>(message->upper_collar.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->upper_collar.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.imbalancemsg.lowercollar"] = (static_cast<std::uint64_t>(message->lower_collar.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->lower_collar.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.imbalancemsg.pairedqty"] = canonical::number(message->paired_qty.get());
            values[entry + ".recordbody.imbalancemsg.totalimbalanceqty"] = canonical::number(message->total_imbalance_qty.get());
            values[entry + ".recordbody.imbalancemsg.marketimbalanceqty"] = canonical::number(message->market_imbalance_qty.get());
            values[entry + ".recordbody.imbalancemsg.unpairedqty"] = canonical::number(message->unpaired_qty.get());
            values[entry + ".recordbody.imbalancemsg.auctiontype"] = canonical::text(canonical::character(message->auction_type.get()));
            values[entry + ".recordbody.imbalancemsg.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".recordbody.imbalancemsg.auctionstatus"] = canonical::number(message->auction_status.get());
            values[entry + ".recordbody.imbalancemsg.freezestatus"] = canonical::number(message->freeze_status.get());
            values[entry + ".recordbody.imbalancemsg.numextensions"] = canonical::number(message->num_extensions.get());
            values[entry + ".recordbody.imbalancemsg.unpairedside"] = canonical::text(canonical::character(message->unpaired_side.get()));
            values[entry + ".recordbody.imbalancemsg.significantimbalance"] = canonical::text(canonical::character(message->significant_imbalance.get()));
        } else if (iterator.rtype == 21) {
            values[entry + ".recordbody"] = "file.record.recordbody.errormsg";
            [[maybe_unused]] const auto* message = protocol::ErrorMsg::parse(iterator.message);
            values[entry + ".recordbody.errormsg.err"] = canonical::text(std::string(message->err.get()), '\0', false);
            values[entry + ".recordbody.errormsg.errorcode"] = canonical::number(message->error_code.get());
            values[entry + ".recordbody.errormsg.islast"] = canonical::number(message->is_last.get());
        } else if (iterator.rtype == 22) {
            values[entry + ".recordbody"] = "file.record.recordbody.symbolmappingmsg";
            [[maybe_unused]] const auto* message = protocol::SymbolMappingMsg::parse(iterator.message);
            values[entry + ".recordbody.symbolmappingmsg.stypein"] = (static_cast<std::uint8_t>(message->stype_in.get()) != 0x0FFU ? canonical::number(message->stype_in.get()) : canonical::absent());
            values[entry + ".recordbody.symbolmappingmsg.stypeinsymbol"] = canonical::text(std::string(message->stype_in_symbol.get()), '\0', false);
            values[entry + ".recordbody.symbolmappingmsg.stypeout"] = canonical::number(message->stype_out.get());
            values[entry + ".recordbody.symbolmappingmsg.stypeoutsymbol"] = canonical::text(std::string(message->stype_out_symbol.get()), '\0', false);
            values[entry + ".recordbody.symbolmappingmsg.startts"] = (static_cast<std::uint64_t>(message->start_ts.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->start_ts.get()) : canonical::absent());
            values[entry + ".recordbody.symbolmappingmsg.endts"] = (static_cast<std::uint64_t>(message->end_ts.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->end_ts.get()) : canonical::absent());
        } else if (iterator.rtype == 23) {
            values[entry + ".recordbody"] = "file.record.recordbody.systemmsg";
            [[maybe_unused]] const auto* message = protocol::SystemMsg::parse(iterator.message);
            values[entry + ".recordbody.systemmsg.msg"] = canonical::text(std::string(message->msg.get()), '\0', false);
            values[entry + ".recordbody.systemmsg.systemcode"] = canonical::number(message->system_code.get());
        } else if (iterator.rtype == 24) {
            values[entry + ".recordbody"] = "file.record.recordbody.statmsg";
            [[maybe_unused]] const auto* message = protocol::StatMsg::parse(iterator.message);
            values[entry + ".recordbody.statmsg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.statmsg.tsref"] = (static_cast<std::uint64_t>(message->ts_ref.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_ref.get()) : canonical::absent());
            values[entry + ".recordbody.statmsg.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.statmsg.quantity"] = (static_cast<std::uint32_t>(message->quantity.get()) != 0x7FFFFFFFU ? canonical::number(message->quantity.get()) : canonical::absent());
            values[entry + ".recordbody.statmsg.sequence"] = canonical::number(message->sequence.get());
            values[entry + ".recordbody.statmsg.tsindelta"] = canonical::number(message->ts_in_delta.get());
            values[entry + ".recordbody.statmsg.stattype"] = canonical::number(message->stat_type.get());
            values[entry + ".recordbody.statmsg.channel"] = canonical::number(message->channel.get());
            values[entry + ".recordbody.statmsg.updateaction"] = canonical::number(message->update_action.get());
            values[entry + ".recordbody.statmsg.statflags"] = canonical::number(message->stat_flags.get());
        } else if (iterator.rtype == 160) {
            values[entry + ".recordbody"] = "file.record.recordbody.mbomsg";
            [[maybe_unused]] const auto* message = protocol::MboMsg::parse(iterator.message);
            values[entry + ".recordbody.mbomsg.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".recordbody.mbomsg.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.mbomsg.size"] = canonical::number(message->size.get());
            values[entry + ".recordbody.mbomsg.flags.reservedflag"] = canonical::number(static_cast<std::uint64_t>(message->flags.ReservedFlag()));
            values[entry + ".recordbody.mbomsg.flags.publisherspecific"] = canonical::number(static_cast<std::uint64_t>(message->flags.PublisherSpecific()));
            values[entry + ".recordbody.mbomsg.flags.maybebadbook"] = canonical::number(static_cast<std::uint64_t>(message->flags.MaybeBadBook()));
            values[entry + ".recordbody.mbomsg.flags.badtsrecv"] = canonical::number(static_cast<std::uint64_t>(message->flags.BadTsRecv()));
            values[entry + ".recordbody.mbomsg.flags.mbp"] = canonical::number(static_cast<std::uint64_t>(message->flags.Mbp()));
            values[entry + ".recordbody.mbomsg.flags.snapshot"] = canonical::number(static_cast<std::uint64_t>(message->flags.Snapshot()));
            values[entry + ".recordbody.mbomsg.flags.tob"] = canonical::number(static_cast<std::uint64_t>(message->flags.Tob()));
            values[entry + ".recordbody.mbomsg.flags.last"] = canonical::number(static_cast<std::uint64_t>(message->flags.Last()));
            values[entry + ".recordbody.mbomsg.channelid"] = canonical::number(message->channel_id.get());
            values[entry + ".recordbody.mbomsg.action"] = canonical::text(canonical::character(message->action.get()));
            values[entry + ".recordbody.mbomsg.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".recordbody.mbomsg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.mbomsg.tsindelta"] = canonical::number(message->ts_in_delta.get());
            values[entry + ".recordbody.mbomsg.sequence"] = canonical::number(message->sequence.get());
        } else if (iterator.rtype == 177 || iterator.rtype == 194) {
            values[entry + ".recordbody"] = "file.record.recordbody.cmbp1msg";
            [[maybe_unused]] const auto* message = protocol::Cmbp1Msg::parse(iterator.message);
            values[entry + ".recordbody.cmbp1msg.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.cmbp1msg.size"] = canonical::number(message->size.get());
            values[entry + ".recordbody.cmbp1msg.action"] = canonical::text(canonical::character(message->action.get()));
            values[entry + ".recordbody.cmbp1msg.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".recordbody.cmbp1msg.flags.reservedflag"] = canonical::number(static_cast<std::uint64_t>(message->flags.ReservedFlag()));
            values[entry + ".recordbody.cmbp1msg.flags.publisherspecific"] = canonical::number(static_cast<std::uint64_t>(message->flags.PublisherSpecific()));
            values[entry + ".recordbody.cmbp1msg.flags.maybebadbook"] = canonical::number(static_cast<std::uint64_t>(message->flags.MaybeBadBook()));
            values[entry + ".recordbody.cmbp1msg.flags.badtsrecv"] = canonical::number(static_cast<std::uint64_t>(message->flags.BadTsRecv()));
            values[entry + ".recordbody.cmbp1msg.flags.mbp"] = canonical::number(static_cast<std::uint64_t>(message->flags.Mbp()));
            values[entry + ".recordbody.cmbp1msg.flags.snapshot"] = canonical::number(static_cast<std::uint64_t>(message->flags.Snapshot()));
            values[entry + ".recordbody.cmbp1msg.flags.tob"] = canonical::number(static_cast<std::uint64_t>(message->flags.Tob()));
            values[entry + ".recordbody.cmbp1msg.flags.last"] = canonical::number(static_cast<std::uint64_t>(message->flags.Last()));
            values[entry + ".recordbody.cmbp1msg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.cmbp1msg.tsindelta"] = canonical::number(message->ts_in_delta.get());
            values[entry + ".recordbody.cmbp1msg.consolidatedbidaskpair.bidpx"] = (static_cast<std::uint64_t>(message->consolidated_bid_ask_pair.bid_px.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->consolidated_bid_ask_pair.bid_px.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.cmbp1msg.consolidatedbidaskpair.askpx"] = (static_cast<std::uint64_t>(message->consolidated_bid_ask_pair.ask_px.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->consolidated_bid_ask_pair.ask_px.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.cmbp1msg.consolidatedbidaskpair.bidsz"] = canonical::number(message->consolidated_bid_ask_pair.bid_sz.get());
            values[entry + ".recordbody.cmbp1msg.consolidatedbidaskpair.asksz"] = canonical::number(message->consolidated_bid_ask_pair.ask_sz.get());
            values[entry + ".recordbody.cmbp1msg.consolidatedbidaskpair.bidpb"] = canonical::number(message->consolidated_bid_ask_pair.bid_pb.get());
            values[entry + ".recordbody.cmbp1msg.consolidatedbidaskpair.askpb"] = canonical::number(message->consolidated_bid_ask_pair.ask_pb.get());
        } else if (iterator.rtype == 192 || iterator.rtype == 193) {
            values[entry + ".recordbody"] = "file.record.recordbody.cbbomsg";
            [[maybe_unused]] const auto* message = protocol::CbboMsg::parse(iterator.message);
            values[entry + ".recordbody.cbbomsg.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.cbbomsg.size"] = canonical::number(message->size.get());
            values[entry + ".recordbody.cbbomsg.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".recordbody.cbbomsg.flags.reservedflag"] = canonical::number(static_cast<std::uint64_t>(message->flags.ReservedFlag()));
            values[entry + ".recordbody.cbbomsg.flags.publisherspecific"] = canonical::number(static_cast<std::uint64_t>(message->flags.PublisherSpecific()));
            values[entry + ".recordbody.cbbomsg.flags.maybebadbook"] = canonical::number(static_cast<std::uint64_t>(message->flags.MaybeBadBook()));
            values[entry + ".recordbody.cbbomsg.flags.badtsrecv"] = canonical::number(static_cast<std::uint64_t>(message->flags.BadTsRecv()));
            values[entry + ".recordbody.cbbomsg.flags.mbp"] = canonical::number(static_cast<std::uint64_t>(message->flags.Mbp()));
            values[entry + ".recordbody.cbbomsg.flags.snapshot"] = canonical::number(static_cast<std::uint64_t>(message->flags.Snapshot()));
            values[entry + ".recordbody.cbbomsg.flags.tob"] = canonical::number(static_cast<std::uint64_t>(message->flags.Tob()));
            values[entry + ".recordbody.cbbomsg.flags.last"] = canonical::number(static_cast<std::uint64_t>(message->flags.Last()));
            values[entry + ".recordbody.cbbomsg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.cbbomsg.consolidatedbidaskpair.bidpx"] = (static_cast<std::uint64_t>(message->consolidated_bid_ask_pair.bid_px.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->consolidated_bid_ask_pair.bid_px.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.cbbomsg.consolidatedbidaskpair.askpx"] = (static_cast<std::uint64_t>(message->consolidated_bid_ask_pair.ask_px.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->consolidated_bid_ask_pair.ask_px.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.cbbomsg.consolidatedbidaskpair.bidsz"] = canonical::number(message->consolidated_bid_ask_pair.bid_sz.get());
            values[entry + ".recordbody.cbbomsg.consolidatedbidaskpair.asksz"] = canonical::number(message->consolidated_bid_ask_pair.ask_sz.get());
            values[entry + ".recordbody.cbbomsg.consolidatedbidaskpair.bidpb"] = canonical::number(message->consolidated_bid_ask_pair.bid_pb.get());
            values[entry + ".recordbody.cbbomsg.consolidatedbidaskpair.askpb"] = canonical::number(message->consolidated_bid_ask_pair.ask_pb.get());
        } else if (iterator.rtype == 195 || iterator.rtype == 196) {
            values[entry + ".recordbody"] = "file.record.recordbody.bbomsg";
            [[maybe_unused]] const auto* message = protocol::BboMsg::parse(iterator.message);
            values[entry + ".recordbody.bbomsg.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->price.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.bbomsg.size"] = canonical::number(message->size.get());
            values[entry + ".recordbody.bbomsg.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".recordbody.bbomsg.flags.reservedflag"] = canonical::number(static_cast<std::uint64_t>(message->flags.ReservedFlag()));
            values[entry + ".recordbody.bbomsg.flags.publisherspecific"] = canonical::number(static_cast<std::uint64_t>(message->flags.PublisherSpecific()));
            values[entry + ".recordbody.bbomsg.flags.maybebadbook"] = canonical::number(static_cast<std::uint64_t>(message->flags.MaybeBadBook()));
            values[entry + ".recordbody.bbomsg.flags.badtsrecv"] = canonical::number(static_cast<std::uint64_t>(message->flags.BadTsRecv()));
            values[entry + ".recordbody.bbomsg.flags.mbp"] = canonical::number(static_cast<std::uint64_t>(message->flags.Mbp()));
            values[entry + ".recordbody.bbomsg.flags.snapshot"] = canonical::number(static_cast<std::uint64_t>(message->flags.Snapshot()));
            values[entry + ".recordbody.bbomsg.flags.tob"] = canonical::number(static_cast<std::uint64_t>(message->flags.Tob()));
            values[entry + ".recordbody.bbomsg.flags.last"] = canonical::number(static_cast<std::uint64_t>(message->flags.Last()));
            values[entry + ".recordbody.bbomsg.tsrecv"] = (static_cast<std::uint64_t>(message->ts_recv.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->ts_recv.get()) : canonical::absent());
            values[entry + ".recordbody.bbomsg.sequence"] = canonical::number(message->sequence.get());
            values[entry + ".recordbody.bbomsg.bidaskpair.bidpx"] = (static_cast<std::uint64_t>(message->bid_ask_pair.bid_px.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->bid_ask_pair.bid_px.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.bbomsg.bidaskpair.askpx"] = (static_cast<std::uint64_t>(message->bid_ask_pair.ask_px.integer()) != 0x7FFFFFFFFFFFFFFFULL ? canonical::scaled(message->bid_ask_pair.ask_px.integer(), -9) : canonical::absent());
            values[entry + ".recordbody.bbomsg.bidaskpair.bidsz"] = canonical::number(message->bid_ask_pair.bid_sz.get());
            values[entry + ".recordbody.bbomsg.bidaskpair.asksz"] = canonical::number(message->bid_ask_pair.ask_sz.get());
            values[entry + ".recordbody.bbomsg.bidaskpair.bidct"] = canonical::number(message->bid_ask_pair.bid_ct.get());
            values[entry + ".recordbody.bbomsg.bidaskpair.askct"] = canonical::number(message->bid_ask_pair.ask_ct.get());
        }
    }

    return values;
}

// Read a sample's file with Modern and hold it to the model's values
int check(const char* name, const char* excerpt, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);

    std::vector<std::byte> bytes;

    try {
        auto file = packet::open_decompressor(std::string{packets} + "/" + excerpt);
        std::vector<std::byte> chunk(65536);
        std::size_t got = 0;

        while ((got = file->read(chunk.data(), chunk.size())) > 0) {
            bytes.insert(bytes.end(), chunk.begin(), chunk.begin() + static_cast<std::ptrdiff_t>(got));
        }
    } catch (const std::exception& error) {
        std::printf("FAIL %s: %s\n", name, error.what());
        return 1;
    }

    if (model.size() != 1) {
        std::printf("FAIL %s: the model read %zu streams of one file\n", name, model.size());
        return 1;
    }

    const auto values = read(bytes.data(), bytes.size());

    if (values.empty() && !model[0].empty()) {
        std::printf("FAIL %s: no value read from %zu bytes\n", name, bytes.size());
        return 1;
    }

    const int differences = canonical::compare(name, 0, model[0], values);

    if (differences == 0) {
        std::printf("ok   %s: %zu values of %zu bytes\n", name, values.size(), bytes.size());
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Databento.MarketData.Normalized.Dbn.v2 (modern 'file' values)\n");
    int failures = 0;
    failures += check("BboMsg", "Databento/MarketData.Normalized.Dbn.v2/BboMsg.excerpt.gz", "databento/marketdata/normalized/dbn/v2/file/BboMsg.values");
    failures += check("InstrumentDefMsg", "Databento/MarketData.Normalized.Dbn.v2/InstrumentDefMsg.excerpt.gz", "databento/marketdata/normalized/dbn/v2/file/InstrumentDefMsg.values");
    failures += check("MboMsg", "Databento/MarketData.Normalized.Dbn.v2/MboMsg.excerpt.gz", "databento/marketdata/normalized/dbn/v2/file/MboMsg.values");
    failures += check("Mbp1Msg", "Databento/MarketData.Normalized.Dbn.v2/Mbp1Msg.excerpt.gz", "databento/marketdata/normalized/dbn/v2/file/Mbp1Msg.values");
    failures += check("StatMsg", "Databento/MarketData.Normalized.Dbn.v2/StatMsg.excerpt.gz", "databento/marketdata/normalized/dbn/v2/file/StatMsg.values");
    failures += check("TradeMsg", "Databento/MarketData.Normalized.Dbn.v2/TradeMsg.excerpt.gz", "databento/marketdata/normalized/dbn/v2/file/TradeMsg.values");
    return failures == 0 ? 0 : 1;
}
