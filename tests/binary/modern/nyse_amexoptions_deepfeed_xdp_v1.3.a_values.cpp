// Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/nyse/amexoptions/deepfeed/xdp/v1.3.a/definitions.hpp"

namespace protocol = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.packetsize"] = canonical::number(iterator.packet_header->packet_size.get());
    values["packet.packetheader.deliveryflag"] = canonical::number(iterator.packet_header->delivery_flag.get());
    values["packet.packetheader.messagecount"] = canonical::number(iterator.packet_header->message_count.get());
    values["packet.packetheader.sequencenumber"] = canonical::number(iterator.packet_header->sequence_number.get());
    values["packet.packetheader.sendtime.seconds"] = canonical::number(iterator.packet_header->send_time.seconds.get());
    values["packet.packetheader.sendtime.nanoseconds"] = canonical::number(iterator.packet_header->send_time.nanoseconds.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(iterator.message_header->message_size.get());
        values[entry + ".messageheader.messagetype"] = canonical::number(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::OutrightMarketDepthBuyMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.outrightmarketdepthbuymessage";
            [[maybe_unused]] const auto* message = protocol::OutrightMarketDepthBuyMessage::parse(iterator.message);
            values[entry + ".payload.outrightmarketdepthbuymessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.sourcens"] = canonical::number(message->source_ns.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.firstlevelprice"] = canonical::number(message->first_level_price.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.secondlevelprice"] = canonical::number(message->second_level_price.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.thirdlevelprice"] = canonical::number(message->third_level_price.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.firstlevelvolume"] = canonical::number(message->first_level_volume.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.secondlevelvolume"] = canonical::number(message->second_level_volume.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.thirdlevelvolume"] = canonical::number(message->third_level_volume.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.quotecondition"] = canonical::text(canonical::character(message->quote_condition.get()), '\0', false);
            values[entry + ".payload.outrightmarketdepthbuymessage.firstlevelcustomervolume"] = canonical::number(message->first_level_customer_volume.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.secondlevelcustomervolume"] = canonical::number(message->second_level_customer_volume.get());
            values[entry + ".payload.outrightmarketdepthbuymessage.thirdlevelcustomervolume"] = canonical::number(message->third_level_customer_volume.get());
        } else if (iterator.message_type == protocol::OutrightMarketDepthSellMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.outrightmarketdepthsellmessage";
            [[maybe_unused]] const auto* message = protocol::OutrightMarketDepthSellMessage::parse(iterator.message);
            values[entry + ".payload.outrightmarketdepthsellmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.sourcens"] = canonical::number(message->source_ns.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.firstlevelprice"] = canonical::number(message->first_level_price.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.secondlevelprice"] = canonical::number(message->second_level_price.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.thirdlevelprice"] = canonical::number(message->third_level_price.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.firstvolume"] = canonical::number(message->first_volume.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.secondvolume"] = canonical::number(message->second_volume.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.thirdvolume"] = canonical::number(message->third_volume.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.quotecondition"] = canonical::text(canonical::character(message->quote_condition.get()), '\0', false);
            values[entry + ".payload.outrightmarketdepthsellmessage.firstlevelcustomervolume"] = canonical::number(message->first_level_customer_volume.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.secondlevelcustomervolume"] = canonical::number(message->second_level_customer_volume.get());
            values[entry + ".payload.outrightmarketdepthsellmessage.thirdlevelcustomervolume"] = canonical::number(message->third_level_customer_volume.get());
        } else if (iterator.message_type == protocol::UnderlyingStatusMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.underlyingstatusmessage";
            [[maybe_unused]] const auto* message = protocol::UnderlyingStatusMessage::parse(iterator.message);
            values[entry + ".payload.underlyingstatusmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.underlyingstatusmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.underlyingstatusmessage.underlyingindex"] = canonical::number(message->underlying_index.get());
            values[entry + ".payload.underlyingstatusmessage.underlyingseqnum"] = canonical::number(message->underlying_seq_num.get());
            values[entry + ".payload.underlyingstatusmessage.securitystatus"] = canonical::text(canonical::character(message->security_status.get()), '\0', false);
            values[entry + ".payload.underlyingstatusmessage.haltcondition"] = canonical::text(canonical::character(message->halt_condition.get()), '\0', false);
        } else if (iterator.message_type == protocol::OutrightSeriesStatusMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.outrightseriesstatusmessage";
            [[maybe_unused]] const auto* message = protocol::OutrightSeriesStatusMessage::parse(iterator.message);
            values[entry + ".payload.outrightseriesstatusmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.outrightseriesstatusmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.outrightseriesstatusmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.outrightseriesstatusmessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.outrightseriesstatusmessage.securitystatus"] = canonical::text(canonical::character(message->security_status.get()), '\0', false);
            values[entry + ".payload.outrightseriesstatusmessage.haltcondition"] = canonical::text(canonical::character(message->halt_condition.get()), '\0', false);
        } else if (iterator.message_type == protocol::RefreshOutrightMarketDepthBuyMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.refreshoutrightmarketdepthbuymessage";
            [[maybe_unused]] const auto* message = protocol::RefreshOutrightMarketDepthBuyMessage::parse(iterator.message);
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.sourcens"] = canonical::number(message->source_ns.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.firstlevelprice"] = canonical::number(message->first_level_price.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.secondlevelprice"] = canonical::number(message->second_level_price.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.thirdlevelprice"] = canonical::number(message->third_level_price.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.firstvolume"] = canonical::number(message->first_volume.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.secondvolume"] = canonical::number(message->second_volume.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.thirdvolume"] = canonical::number(message->third_volume.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.quotecondition"] = canonical::text(canonical::character(message->quote_condition.get()), '\0', false);
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.firstlevelcustomervolume"] = canonical::number(message->first_level_customer_volume.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.secondlevelcustomervolume"] = canonical::number(message->second_level_customer_volume.get());
            values[entry + ".payload.refreshoutrightmarketdepthbuymessage.thirdlevelcustomervolume"] = canonical::number(message->third_level_customer_volume.get());
        } else if (iterator.message_type == protocol::RefreshOutrightMarketDepthSellMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.refreshoutrightmarketdepthsellmessage";
            [[maybe_unused]] const auto* message = protocol::RefreshOutrightMarketDepthSellMessage::parse(iterator.message);
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.firstlevelprice"] = canonical::number(message->first_level_price.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.secondlevelprice"] = canonical::number(message->second_level_price.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.thirdlevelprice"] = canonical::number(message->third_level_price.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.firstvolume"] = canonical::number(message->first_volume.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.secondvolume"] = canonical::number(message->second_volume.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.thirdvolume"] = canonical::number(message->third_volume.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.quotecondition"] = canonical::text(canonical::character(message->quote_condition.get()), '\0', false);
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.firstlevelcustomervolume"] = canonical::number(message->first_level_customer_volume.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.secondlevelcustomervolume"] = canonical::number(message->second_level_customer_volume.get());
            values[entry + ".payload.refreshoutrightmarketdepthsellmessage.thirdlevelcustomervolume"] = canonical::number(message->third_level_customer_volume.get());
        } else if (iterator.message_type == protocol::UnderlyingIndexMappingMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.underlyingindexmappingmessage";
            [[maybe_unused]] const auto* message = protocol::UnderlyingIndexMappingMessage::parse(iterator.message);
            values[entry + ".payload.underlyingindexmappingmessage.underlyingindex"] = canonical::number(message->underlying_index.get());
            values[entry + ".payload.underlyingindexmappingmessage.underlyingsymbol"] = canonical::text(std::string(message->underlying_symbol.get()), '\0', false);
            values[entry + ".payload.underlyingindexmappingmessage.channelid"] = canonical::number(message->channel_id.get());
            values[entry + ".payload.underlyingindexmappingmessage.marketid"] = canonical::number(message->market_id.get());
            values[entry + ".payload.underlyingindexmappingmessage.systemid"] = canonical::number(message->system_id.get());
            values[entry + ".payload.underlyingindexmappingmessage.exchangecode"] = canonical::text(canonical::character(message->exchange_code.get()), '\0', false);
            values[entry + ".payload.underlyingindexmappingmessage.pricescalecode"] = canonical::number(message->price_scale_code.get());
            values[entry + ".payload.underlyingindexmappingmessage.securitytype"] = canonical::text(canonical::character(message->security_type.get()), '\0', false);
            values[entry + ".payload.underlyingindexmappingmessage.priceresolution"] = canonical::number(message->price_resolution.get());
        } else if (iterator.message_type == protocol::SeriesIndexMappingMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.seriesindexmappingmessage";
            [[maybe_unused]] const auto* message = protocol::SeriesIndexMappingMessage::parse(iterator.message);
            values[entry + ".payload.seriesindexmappingmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.seriesindexmappingmessage.channelid"] = canonical::number(message->channel_id.get());
            values[entry + ".payload.seriesindexmappingmessage.marketid"] = canonical::number(message->market_id.get());
            values[entry + ".payload.seriesindexmappingmessage.systemid"] = canonical::number(message->system_id.get());
            values[entry + ".payload.seriesindexmappingmessage.streamid"] = canonical::number(message->stream_id.get());
            values[entry + ".payload.seriesindexmappingmessage.underlyingindex"] = canonical::number(message->underlying_index.get());
            values[entry + ".payload.seriesindexmappingmessage.contractmultiplier"] = canonical::number(message->contract_multiplier.get());
            values[entry + ".payload.seriesindexmappingmessage.maturitydate"] = canonical::text(std::string(message->maturity_date.get()), '\0', false);
            values[entry + ".payload.seriesindexmappingmessage.putorcall"] = canonical::number(message->put_or_call.get());
            values[entry + ".payload.seriesindexmappingmessage.strikeprice"] = canonical::text(std::string(message->strike_price.get()), '\0', false);
            values[entry + ".payload.seriesindexmappingmessage.pricescalecode"] = canonical::number(message->price_scale_code.get());
            values[entry + ".payload.seriesindexmappingmessage.underlyingsymbol"] = canonical::text(std::string(message->underlying_symbol.get()), '\0', false);
            values[entry + ".payload.seriesindexmappingmessage.optionsymbolroot"] = canonical::text(std::string(message->option_symbol_root.get()), '\0', false);
            values[entry + ".payload.seriesindexmappingmessage.groupid"] = canonical::number(message->group_id.get());
        } else if (iterator.message_type == protocol::StreamIdMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.streamidmessage";
            [[maybe_unused]] const auto* message = protocol::StreamIdMessage::parse(iterator.message);
            values[entry + ".payload.streamidmessage.streamid"] = canonical::number(message->stream_id.get());
        } else if (iterator.message_type == protocol::SequenceNumberResetMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.sequencenumberresetmessage";
            [[maybe_unused]] const auto* message = protocol::SequenceNumberResetMessage::parse(iterator.message);
            values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message->channel_id.get());
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
    std::printf("== Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a (modern values)\n");
    int failures = 0;
    failures += check("OutrightMarketDepthBuyMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/OutrightMarketDepthBuyMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/OutrightMarketDepthBuyMessage.values");
    failures += check("OutrightMarketDepthSellMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/OutrightMarketDepthSellMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/OutrightMarketDepthSellMessage.values");
    failures += check("RefreshOutrightMarketDepthBuyMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/RefreshOutrightMarketDepthBuyMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/RefreshOutrightMarketDepthBuyMessage.values");
    failures += check("RefreshOutrightMarketDepthSellMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/RefreshOutrightMarketDepthSellMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/RefreshOutrightMarketDepthSellMessage.values");
    failures += check("StreamIdMessage", "Nyse/AmexOptions.DeepFeed.Xdp.v1.3.a/StreamIdMessage.pcap", "nyse/amexoptions/deepfeed/xdp/v1.3.a/StreamIdMessage.values");
    return failures == 0 ? 0 : 1;
}
