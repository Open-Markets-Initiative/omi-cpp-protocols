// Nyse.ArcaOptions.TopFeed.Pillar.v1.2.c canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/nyse/arcaoptions/topfeed/pillar/v1.2.c/definitions.hpp"

namespace protocol = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.pktsize"] = canonical::number(packet.packet_header().pkt_size());
        values["packet.packetheader.deliveryflag"] = canonical::number(packet.packet_header().delivery_flag());
        values["packet.packetheader.numbermsgs"] = canonical::number(packet.packet_header().number_msgs());
        values["packet.packetheader.seqnum"] = canonical::number(packet.packet_header().seq_num());
        values["packet.packetheader.sendtime.seconds"] = canonical::number(packet.packet_header().send_time().seconds());
        values["packet.packetheader.sendtime.nanoseconds"] = canonical::number(packet.packet_header().send_time().nanoseconds());
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

    void on(const protocol::SequenceNumberResetMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.sequencenumberresetmessage";
        values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message.channel_id());
    }

    void on(const protocol::TimeReferenceMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.timereferencemessage";
        values[entry + ".payload.timereferencemessage.id"] = canonical::number(message.id());
        values[entry + ".payload.timereferencemessage.sourcetime"] = canonical::number(message.source_time());
    }

    void on(const protocol::SymbolIndexMappingMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingmessage";
        values[entry + ".payload.symbolindexmappingmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.symbolindexmappingmessage.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.marketid"] = canonical::number(message.market_id());
        values[entry + ".payload.symbolindexmappingmessage.systemid"] = canonical::number(message.system_id());
        values[entry + ".payload.symbolindexmappingmessage.exchangecode"] = canonical::text(canonical::character(message.exchange_code()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.pricescalecode"] = canonical::number(message.price_scale_code());
        values[entry + ".payload.symbolindexmappingmessage.securitytype"] = canonical::text(canonical::character(message.security_type()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.lotsize"] = canonical::number(message.lot_size());
        values[entry + ".payload.symbolindexmappingmessage.prevcloseprice"] = canonical::number(message.prev_close_price());
        values[entry + ".payload.symbolindexmappingmessage.prevclosevolume"] = canonical::number(message.prev_close_volume());
        values[entry + ".payload.symbolindexmappingmessage.priceresolution"] = canonical::number(message.price_resolution());
        values[entry + ".payload.symbolindexmappingmessage.roundlot"] = canonical::text(canonical::character(message.round_lot()), '\0', false);
    }

    void on(const protocol::RetransmissionRequestMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.retransmissionrequestmessage";
        values[entry + ".payload.retransmissionrequestmessage.beginseqnum"] = canonical::number(message.begin_seq_num());
        values[entry + ".payload.retransmissionrequestmessage.endseqnum"] = canonical::number(message.end_seq_num());
        values[entry + ".payload.retransmissionrequestmessage.sourceid"] = canonical::text(std::string(message.source_id()), '\0', false);
        values[entry + ".payload.retransmissionrequestmessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.retransmissionrequestmessage.channelid"] = canonical::number(message.channel_id());
    }

    void on(const protocol::RequestResponseMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.requestresponsemessage";
        values[entry + ".payload.requestresponsemessage.requestseqnum"] = canonical::number(message.request_seq_num());
        values[entry + ".payload.requestresponsemessage.beginseqnum"] = canonical::number(message.begin_seq_num());
        values[entry + ".payload.requestresponsemessage.endseqnum"] = canonical::number(message.end_seq_num());
        values[entry + ".payload.requestresponsemessage.sourceid"] = canonical::text(std::string(message.source_id()), '\0', false);
        values[entry + ".payload.requestresponsemessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.requestresponsemessage.channelid"] = canonical::number(message.channel_id());
        values[entry + ".payload.requestresponsemessage.status"] = canonical::text(canonical::character(message.status()), '\0', false);
    }

    void on(const protocol::HeartbeatResponseMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.heartbeatresponsemessage";
        values[entry + ".payload.heartbeatresponsemessage.sourceid"] = canonical::text(std::string(message.source_id()), '\0', false);
    }

    void on(const protocol::SymbolIndexMappingRequestMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingrequestmessage";
        values[entry + ".payload.symbolindexmappingrequestmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.symbolindexmappingrequestmessage.sourceid"] = canonical::text(std::string(message.source_id()), '\0', false);
        values[entry + ".payload.symbolindexmappingrequestmessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.symbolindexmappingrequestmessage.channelid"] = canonical::number(message.channel_id());
        values[entry + ".payload.symbolindexmappingrequestmessage.retransmitmethod"] = canonical::number(message.retransmit_method());
    }

    void on(const protocol::RefreshRequestMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.refreshrequestmessage";
        values[entry + ".payload.refreshrequestmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.refreshrequestmessage.sourceid"] = canonical::text(std::string(message.source_id()), '\0', false);
        values[entry + ".payload.refreshrequestmessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.refreshrequestmessage.channelid"] = canonical::number(message.channel_id());
    }

    void on(const protocol::MessageUnavailableMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.messageunavailablemessage";
        values[entry + ".payload.messageunavailablemessage.beginseqnum"] = canonical::number(message.begin_seq_num());
        values[entry + ".payload.messageunavailablemessage.endseqnum"] = canonical::number(message.end_seq_num());
        values[entry + ".payload.messageunavailablemessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.messageunavailablemessage.channelid"] = canonical::number(message.channel_id());
    }

    void on(const protocol::SymbolClearMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.symbolclearmessage";
        values[entry + ".payload.symbolclearmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.symbolclearmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.symbolclearmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.symbolclearmessage.nextsourceseqnum"] = canonical::number(message.next_source_seq_num());
    }

    void on(const protocol::SecurityStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.securitystatusmessage";
        values[entry + ".payload.securitystatusmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.securitystatusmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.securitystatusmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.securitystatusmessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.securitystatusmessage.securitystatus"] = canonical::text(canonical::character(message.security_status()), '\0', false);
        values[entry + ".payload.securitystatusmessage.haltcondition"] = canonical::text(canonical::character(message.halt_condition()), '\0', false);
        values[entry + ".payload.securitystatusmessage.price1"] = canonical::number(message.price_1());
        values[entry + ".payload.securitystatusmessage.price2"] = canonical::number(message.price_2());
        values[entry + ".payload.securitystatusmessage.ssrtriggeringexchangeid"] = canonical::text(canonical::character(message.ssr_triggering_exchange_id()), '\0', false);
        values[entry + ".payload.securitystatusmessage.ssrtriggeringvolume"] = canonical::number(message.ssr_triggering_volume());
        values[entry + ".payload.securitystatusmessage.time"] = (message.time().has_value() ? canonical::number((*message.time())) : canonical::absent());
        values[entry + ".payload.securitystatusmessage.ssrstate"] = canonical::text(canonical::character(message.ssr_state()), '\0', false);
        values[entry + ".payload.securitystatusmessage.marketstate"] = canonical::text(canonical::character(message.market_state()), '\0', false);
        values[entry + ".payload.securitystatusmessage.sessionstate"] = canonical::number(message.session_state());
    }

    void on(const protocol::RefreshHeaderMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.refreshheadermessage";
        values[entry + ".payload.refreshheadermessage.currentrefreshpkt"] = canonical::number(message.current_refresh_pkt());
        values[entry + ".payload.refreshheadermessage.totalrefreshpkts"] = canonical::number(message.total_refresh_pkts());
    }

    void on(const protocol::OutrightSeriesIndexMappingMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.outrightseriesindexmappingmessage";
        values[entry + ".payload.outrightseriesindexmappingmessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.outrightseriesindexmappingmessage.seriestype"] = canonical::number(message.series_type());
        values[entry + ".payload.outrightseriesindexmappingmessage.marketid"] = canonical::number(message.market_id());
        values[entry + ".payload.outrightseriesindexmappingmessage.systemid"] = canonical::number(message.system_id());
        values[entry + ".payload.outrightseriesindexmappingmessage.optionsymbolroot"] = canonical::text(std::string(message.option_symbol_root()), '\0', false);
        values[entry + ".payload.outrightseriesindexmappingmessage.underlyingsymbol"] = canonical::text(std::string(message.underlying_symbol()), '\0', false);
        values[entry + ".payload.outrightseriesindexmappingmessage.underlyingindex"] = canonical::number(message.underlying_index());
        values[entry + ".payload.outrightseriesindexmappingmessage.pricescalecode"] = canonical::number(message.price_scale_code());
        values[entry + ".payload.outrightseriesindexmappingmessage.contractmultiplier"] = canonical::number(message.contract_multiplier());
        values[entry + ".payload.outrightseriesindexmappingmessage.maturitydate"] = canonical::text(std::string(message.maturity_date()), '\0', false);
        values[entry + ".payload.outrightseriesindexmappingmessage.putorcall"] = canonical::number(message.put_or_call());
        values[entry + ".payload.outrightseriesindexmappingmessage.strikeprice"] = canonical::text(std::string(message.strike_price()), '\0', false);
        values[entry + ".payload.outrightseriesindexmappingmessage.closingonlyindicator"] = canonical::text(canonical::character(message.closing_only_indicator()), '\0', false);
    }

    void on(const protocol::OptionsStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.optionsstatusmessage";
        values[entry + ".payload.optionsstatusmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.optionsstatusmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.optionsstatusmessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.optionsstatusmessage.seriesseqnum"] = canonical::number(message.series_seq_num());
        values[entry + ".payload.optionsstatusmessage.seriesstatus"] = canonical::text(canonical::character(message.series_status()), '\0', false);
        values[entry + ".payload.optionsstatusmessage.marketstate"] = canonical::text(canonical::character(message.market_state()), '\0', false);
        values[entry + ".payload.optionsstatusmessage.haltcondition"] = canonical::text(canonical::character(message.halt_condition()), '\0', false);
    }

    void on(const protocol::OptionsQuoteMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.optionsquotemessage";
        values[entry + ".payload.optionsquotemessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.optionsquotemessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.optionsquotemessage.seriesseqnum"] = canonical::number(message.series_seq_num());
        values[entry + ".payload.optionsquotemessage.askprice"] = canonical::number(message.ask_price());
        values[entry + ".payload.optionsquotemessage.askvolume"] = canonical::number(message.ask_volume());
        values[entry + ".payload.optionsquotemessage.bidprice"] = canonical::number(message.bid_price());
        values[entry + ".payload.optionsquotemessage.bidvolume"] = canonical::number(message.bid_volume());
        values[entry + ".payload.optionsquotemessage.quotecondition"] = canonical::text(canonical::character(message.quote_condition()), '\0', false);
        values[entry + ".payload.optionsquotemessage.askcustomervolume"] = canonical::number(message.ask_customer_volume());
        values[entry + ".payload.optionsquotemessage.bidcustomervolume"] = canonical::number(message.bid_customer_volume());
    }

    void on(const protocol::OptionsTradeMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.optionstrademessage";
        values[entry + ".payload.optionstrademessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.optionstrademessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.optionstrademessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.optionstrademessage.seriesseqnum"] = canonical::number(message.series_seq_num());
        values[entry + ".payload.optionstrademessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.optionstrademessage.price"] = canonical::number(message.price());
        values[entry + ".payload.optionstrademessage.volume"] = canonical::number(message.volume());
        values[entry + ".payload.optionstrademessage.tradecondition.series"] = canonical::text(canonical::character(message.trade_condition().series()), '\0', false);
        values[entry + ".payload.optionstrademessage.tradecondition.opening"] = canonical::text(canonical::character(message.trade_condition().opening()), '\0', false);
        values[entry + ".payload.optionstrademessage.tradecondition.offical"] = canonical::text(canonical::character(message.trade_condition().offical()), '\0', false);
    }

    void on(const protocol::OptionsTradeCancelMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.optionstradecancelmessage";
        values[entry + ".payload.optionstradecancelmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.optionstradecancelmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.optionstradecancelmessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.optionstradecancelmessage.seriesseqnum"] = canonical::number(message.series_seq_num());
        values[entry + ".payload.optionstradecancelmessage.originaltradeid"] = canonical::number(message.original_trade_id());
    }

    void on(const protocol::OptionsTradeCorrectionMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.optionstradecorrectionmessage";
        values[entry + ".payload.optionstradecorrectionmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.optionstradecorrectionmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.optionstradecorrectionmessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.optionstradecorrectionmessage.seriesseqnum"] = canonical::number(message.series_seq_num());
        values[entry + ".payload.optionstradecorrectionmessage.originaltradeid"] = canonical::number(message.original_trade_id());
        values[entry + ".payload.optionstradecorrectionmessage.tradeid"] = canonical::number(message.trade_id());
        values[entry + ".payload.optionstradecorrectionmessage.price"] = canonical::number(message.price());
        values[entry + ".payload.optionstradecorrectionmessage.volume"] = canonical::number(message.volume());
        values[entry + ".payload.optionstradecorrectionmessage.correctioncondition.transaction"] = canonical::text(canonical::character(message.correction_condition().transaction()), '\0', false);
    }

    void on(const protocol::OptionsImbalanceMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.optionsimbalancemessage";
        values[entry + ".payload.optionsimbalancemessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.optionsimbalancemessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.optionsimbalancemessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.optionsimbalancemessage.seriesseqnum"] = canonical::number(message.series_seq_num());
        values[entry + ".payload.optionsimbalancemessage.pairedqty"] = canonical::number(message.paired_qty());
        values[entry + ".payload.optionsimbalancemessage.totalimbalanceqty"] = canonical::number(message.total_imbalance_qty());
        values[entry + ".payload.optionsimbalancemessage.marketimbalanceqty"] = canonical::number(message.market_imbalance_qty());
        values[entry + ".payload.optionsimbalancemessage.auctiontype"] = canonical::text(canonical::character(message.auction_type()), '\0', false);
        values[entry + ".payload.optionsimbalancemessage.imbalanceside"] = canonical::text(canonical::character(message.imbalance_side()), '\0', false);
        values[entry + ".payload.optionsimbalancemessage.continuousbookclearingprice"] = canonical::number(message.continuous_book_clearing_price());
        values[entry + ".payload.optionsimbalancemessage.auctioninterestclearingprice"] = canonical::number(message.auction_interest_clearing_price());
        values[entry + ".payload.optionsimbalancemessage.indicativematchprice"] = canonical::number(message.indicative_match_price());
        values[entry + ".payload.optionsimbalancemessage.uppercollar"] = canonical::number(message.upper_collar());
        values[entry + ".payload.optionsimbalancemessage.lowercollar"] = canonical::number(message.lower_collar());
        values[entry + ".payload.optionsimbalancemessage.auctionstatus"] = canonical::number(message.auction_status());
    }

    void on(const protocol::SeriesRfqMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.seriesrfqmessage";
        values[entry + ".payload.seriesrfqmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.seriesrfqmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.seriesrfqmessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.seriesrfqmessage.seriesseqnum"] = canonical::number(message.series_seq_num());
        values[entry + ".payload.seriesrfqmessage.side"] = canonical::text(canonical::character(message.side()), '\0', false);
        values[entry + ".payload.seriesrfqmessage.type"] = canonical::text(canonical::character(message.type_field()), '\0', false);
        values[entry + ".payload.seriesrfqmessage.capacity"] = canonical::text(canonical::character(message.capacity()), '\0', false);
        values[entry + ".payload.seriesrfqmessage.totalquantity"] = canonical::number(message.total_quantity());
        values[entry + ".payload.seriesrfqmessage.workingprice"] = canonical::number(message.working_price());
        values[entry + ".payload.seriesrfqmessage.participant"] = canonical::number(message.participant());
        values[entry + ".payload.seriesrfqmessage.auctionid"] = canonical::number(message.auction_id());
        values[entry + ".payload.seriesrfqmessage.rfqstatus"] = canonical::text(canonical::character(message.rfq_status()), '\0', false);
    }

    void on(const protocol::OutrightSeriesSummaryMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.outrightseriessummarymessage";
        values[entry + ".payload.outrightseriessummarymessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.outrightseriessummarymessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.outrightseriessummarymessage.seriesindex"] = canonical::number(message.series_index());
        values[entry + ".payload.outrightseriessummarymessage.highprice"] = canonical::number(message.high_price());
        values[entry + ".payload.outrightseriessummarymessage.lowprice"] = canonical::number(message.low_price());
        values[entry + ".payload.outrightseriessummarymessage.open"] = canonical::number(message.open());
        values[entry + ".payload.outrightseriessummarymessage.close"] = canonical::number(message.close());
        values[entry + ".payload.outrightseriessummarymessage.totalvolume"] = canonical::number(message.total_volume());
    }
};

// The values the Flyweight reader reads from one datagram, by indexed address. A datagram it cannot
// read is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
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
    std::printf("== Nyse.ArcaOptions.TopFeed.Pillar.v1.2.c (flyweight values)\n");
    int failures = 0;
    failures += check("HeartBeat", "Nyse/ArcaOptions.TopFeed.Pillar.v1.2.c/HeartBeat.pcap", "nyse/arcaoptions/topfeed/pillar/v1.2.c/HeartBeat.values");
    failures += check("OptionsQuoteMessage", "Nyse/ArcaOptions.TopFeed.Pillar.v1.2.c/OptionsQuoteMessage.pcap", "nyse/arcaoptions/topfeed/pillar/v1.2.c/OptionsQuoteMessage.values");
    failures += check("SequenceNumberResetMessage", "Nyse/ArcaOptions.TopFeed.Pillar.v1.2.c/SequenceNumberResetMessage.pcap", "nyse/arcaoptions/topfeed/pillar/v1.2.c/SequenceNumberResetMessage.values");
    return failures == 0 ? 0 : 1;
}
