// Iex.IexEquities.Tops.IexTp.v1.56 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/modern/iex/iexequities/tops/iextp/v1.56/definitions.hpp"

namespace protocol = ::iex::iexequities::tops::iextp::v1_56;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.iextpheader.version"] = canonical::number(iterator.iextp_header->version.get());
    values["packet.iextpheader.messageprotocolid"] = canonical::number(iterator.iextp_header->message_protocol_id.get());
    values["packet.iextpheader.channelid"] = canonical::number(iterator.iextp_header->channel_id.get());
    values["packet.iextpheader.sessionid"] = canonical::number(iterator.iextp_header->session_id.get());
    values["packet.iextpheader.payloadlength"] = canonical::number(iterator.iextp_header->payload_length.get());
    values["packet.iextpheader.messagecount"] = canonical::number(iterator.iextp_header->message_count.get());
    values["packet.iextpheader.streamoffset"] = canonical::number(iterator.iextp_header->stream_offset.get());
    values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(iterator.iextp_header->first_message_sequence_number.get());
    values["packet.iextpheader.sendtime"] = canonical::number(iterator.iextp_header->send_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::QuoteUpdateMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.quoteupdatemessage";
            [[maybe_unused]] const auto* message = protocol::QuoteUpdateMessage::parse(iterator.message);
            values[entry + ".messagedata.quoteupdatemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.quoteupdatemessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.quoteupdatemessage.bidsize"] = canonical::number(message->bid_size.get());
            values[entry + ".messagedata.quoteupdatemessage.bidprice"] = canonical::scaled(message->bid_price.integer(), -4);
            values[entry + ".messagedata.quoteupdatemessage.askprice"] = canonical::scaled(message->ask_price.integer(), -4);
            values[entry + ".messagedata.quoteupdatemessage.asksize"] = canonical::number(message->ask_size.get());
        } else if (iterator.message_type == protocol::TradeReportMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradereportmessage";
            [[maybe_unused]] const auto* message = protocol::TradeReportMessage::parse(iterator.message);
            values[entry + ".messagedata.tradereportmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.tradereportmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.tradereportmessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.tradereportmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".messagedata.tradereportmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".messagedata.tradereportmessage.reserved4"] = canonical::number(message->reserved_4.get());
        } else if (iterator.message_type == protocol::TradeBreakMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
            [[maybe_unused]] const auto* message = protocol::TradeBreakMessage::parse(iterator.message);
            values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".messagedata.tradebreakmessage.reserved4"] = canonical::number(message->reserved_4.get());
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
    std::printf("== Iex.IexEquities.Tops.IexTp.v1.56 (modern values)\n");
    int failures = 0;
    failures += check("QuoteUpdateMessage", "Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap", "iex/iexequities/tops/iextp/v1.56/QuoteUpdateMessage.values");
    failures += check("TradeReportMessage", "Iex/IexEquities.Tops.IexTp.v1.56/TradeReportMessage.pcap", "iex/iexequities/tops/iextp/v1.56/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}