// Iex.IexEquities.Tops.IexTp.v1.56 canonical values, through the Advanced session layer: every value Advanced
// reads from each sample, at its address, held to what the model reads.

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
#include "cpp/advanced/iex/iexequities/tops/iextp/v1.56/messages/session.hpp"

namespace protocol = ::iex::iexequities::tops::iextp::v1_56;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::iextp_header& header, const packet::Frame&) {
        values["packet.iextpheader.version"] = canonical::number(header.version.get().value());
        values["packet.iextpheader.messageprotocolid"] = canonical::number(header.message_protocol_id.get().value());
        values["packet.iextpheader.channelid"] = canonical::number(header.channel_id.get().value());
        values["packet.iextpheader.sessionid"] = canonical::number(header.session_id.get().value());
        values["packet.iextpheader.payloadlength"] = canonical::number(header.payload_length.get().value());
        values["packet.iextpheader.messagecount"] = canonical::number(header.message_count.get().value());
        values["packet.iextpheader.streamoffset"] = canonical::number(header.stream_offset.get().value());
        values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(header.first_message_sequence_number.get().value());
        values["packet.iextpheader.sendtime"] = canonical::number(header.send_time.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::iextp_header&) {
        ++index;
    }

    void on_message(const protocol::quote_update_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.quoteupdatemessage";
        values[entry + ".messagedata.quoteupdatemessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.quoteupdatemessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.quoteupdatemessage.bidsize"] = canonical::number(message.fields.bid_size.get().value());
        values[entry + ".messagedata.quoteupdatemessage.bidprice"] = canonical::scaled(message.fields.bid_price.get().value(), -4);
        values[entry + ".messagedata.quoteupdatemessage.askprice"] = canonical::scaled(message.fields.ask_price.get().value(), -4);
        values[entry + ".messagedata.quoteupdatemessage.asksize"] = canonical::number(message.fields.ask_size.get().value());
    }

    void on_message(const protocol::trade_report_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradereportmessage";
        values[entry + ".messagedata.tradereportmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.tradereportmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.tradereportmessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.tradereportmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".messagedata.tradereportmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".messagedata.tradereportmessage.reserved4"] = canonical::number(message.fields.reserved_4.get().value());
    }

    void on_message(const protocol::trade_break_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
        values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".messagedata.tradebreakmessage.reserved4"] = canonical::number(message.fields.reserved_4.get().value());
    }
};

// The values Advanced reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.values;
}

// Read each datagram of a sample with Advanced and hold it to the model's values
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
    std::printf("== Iex.IexEquities.Tops.IexTp.v1.56 (advanced values)\n");
    int failures = 0;
    failures += check("QuoteUpdateMessage", "Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap", "iex/iexequities/tops/iextp/v1.56/QuoteUpdateMessage.values");
    failures += check("TradeReportMessage", "Iex/IexEquities.Tops.IexTp.v1.56/TradeReportMessage.pcap", "iex/iexequities/tops/iextp/v1.56/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}