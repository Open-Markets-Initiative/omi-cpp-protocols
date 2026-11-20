// Iex.IexEquities.Tops.Snap.v1.6 canonical values of 'packet', through the Modern iterator: every value
// Modern reads from each side of each connection the tree is sent from, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "TcpReassembler.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/modern/iex/iexequities/tops/snap/v1.6/definitions.hpp"

namespace protocol = ::iex::iexequities::tops::snap::v1_6;

namespace {

// The values the Modern iterator reads from one stream of 'packet', by indexed address
canonical::Listing read(const std::byte* data, std::size_t length) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(data, length);

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";

        // the iterator steps past a record the bytes end inside; its values are not read
        if (iterator.current > iterator.end) {
            values[entry] = "(ends inside the record)";
            break;
        }

        values[entry + ".messageheader.messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::SnapshotRequestMessage::message_type) {
            values[entry + ".messagedata"] = "packet.message.messagedata.snapshotrequestmessage";
            [[maybe_unused]] const auto* message = protocol::SnapshotRequestMessage::parse(iterator.message);
            values[entry + ".messagedata.snapshotrequestmessage.authenticationtoken"] = canonical::text(std::string(message->authentication_token.get()), ' ', false);
            values[entry + ".messagedata.snapshotrequestmessage.channelid"] = canonical::number(message->channel_id.get());
            values[entry + ".messagedata.snapshotrequestmessage.sessionid"] = canonical::number(message->session_id.get());
            values[entry + ".messagedata.snapshotrequestmessage.minimumsequencenumber"] = canonical::number(message->minimum_sequence_number.get());
        } else if (iterator.message_type == protocol::ErrorResponseMessage::message_type) {
            values[entry + ".messagedata"] = "packet.message.messagedata.errorresponsemessage";
            [[maybe_unused]] const auto* message = protocol::ErrorResponseMessage::parse(iterator.message);
            values[entry + ".messagedata.errorresponsemessage.rejectreasoncode"] = canonical::text(canonical::character(message->reject_reason_code.get()));
        } else if (iterator.message_type == protocol::SnapshotStartMessage::message_type) {
            values[entry + ".messagedata"] = "packet.message.messagedata.snapshotstartmessage";
            [[maybe_unused]] const auto* message = protocol::SnapshotStartMessage::parse(iterator.message);
            values[entry + ".messagedata.snapshotstartmessage.snapshotlength"] = canonical::number(message->snapshot_length.get());
        } else if (iterator.message_type == protocol::SnapshotDataMessage::message_type) {
            values[entry + ".messagedata"] = "packet.message.messagedata.snapshotdatamessage";
            [[maybe_unused]] const auto* message = protocol::SnapshotDataMessage::parse(iterator.message);
            values[entry + ".messagedata.snapshotdatamessage.iextpheader.version"] = canonical::number(message->iextp_header.version.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpheader.messageprotocolid"] = canonical::number(message->iextp_header.message_protocol_id.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpheader.channelid"] = canonical::number(message->iextp_header.channel_id.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpheader.sessionid"] = canonical::number(message->iextp_header.session_id.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpheader.payloadlength"] = canonical::number(message->iextp_header.payload_length.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpheader.messagecount"] = canonical::number(message->iextp_header.message_count.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpheader.streamoffset"] = canonical::number(message->iextp_header.stream_offset.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpheader.firstmessagesequencenumber"] = canonical::number(message->iextp_header.first_message_sequence_number.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpheader.sendtime"] = canonical::number(message->iextp_header.send_time.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpmessageblocklength"] = canonical::number(message->iex_tp_message_block_length.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpmessagelength"] = canonical::number(message->iex_tp_message_length.get());
            values[entry + ".messagedata.snapshotdatamessage.iextpmessagetype"] = canonical::text(canonical::character(message->iex_tp_message_type.get()));
        } else if (iterator.message_type == protocol::SnapshotEndMessage::message_type) {
            values[entry + ".messagedata"] = "packet.message.messagedata.snapshotendmessage";
            [[maybe_unused]] const auto* message = protocol::SnapshotEndMessage::parse(iterator.message);
            values[entry + ".messagedata.snapshotendmessage.snapshotsequencenumber"] = canonical::number(message->snapshot_sequence_number.get());
        }
    }

    return values;
}

// Reassemble each side of a sample's connections, read each side with Modern and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);

    std::vector<packet::TcpFlowKey> order;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::byte>, packet::TcpFlowKey::hash> sides;
    packet::TcpReassembler reassembler;
    bool dialled = false;
    std::uint32_t client_ip = 0;
    std::uint16_t client_port = 0;

    reassembler.on_data = [&](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& side = sides[key];
        side.insert(side.end(), data, data + length);
    };

    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);
    packet::PcapIterator captures(sources);

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_tcp()) { continue; }

        const packet::TcpFlowKey key{ frame.src_ip, frame.dst_ip, frame.src_port, frame.dst_port };

        if (sides.find(key) == sides.end()) {
            sides[key];
            order.push_back(key);
        }

        if (!dialled && (frame.tcp_flags & 0x02) != 0 && (frame.tcp_flags & 0x10) == 0) {
            dialled = true;
            client_ip = frame.src_ip;
            client_port = frame.src_port;
        }

        reassembler.process(frame);
    }

    std::size_t stream = 0;
    std::size_t read_values = 0;
    int differences = 0;

    for (const auto& key : order) {
        [[maybe_unused]] const bool from_client = dialled && key.src_ip == client_ip && key.src_port == client_port;
        [[maybe_unused]] const bool to_client = dialled && key.dst_ip == client_ip && key.dst_port == client_port;

        if (!(true)) { continue; }

        if (stream >= model.size()) {
            std::printf("FAIL %s: more streams than the model read\n", name);
            return 1;
        }

        const auto& bytes = sides[key];
        const auto values = read(bytes.data(), bytes.size());

        if (values.empty() && !model[stream].empty()) {
            std::printf("FAIL %s: no value read from stream %zu, %zu bytes\n", name, stream, bytes.size());
            return 1;
        }

        read_values += values.size();
        differences += canonical::compare(name, stream, model[stream], values);
        ++stream;
    }

    if (stream != model.size()) {
        std::printf("FAIL %s: %zu streams, the model read %zu\n", name, stream, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu values of %zu streams\n", name, read_values, stream);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Iex.IexEquities.Tops.Snap.v1.6 (modern 'packet' values)\n");
    int failures = 0;
    failures += check("Simulated", "tests/simulated/iex/iexequities/tops/snap/v1.6.pcap", "iex/iexequities/tops/snap/v1.6/packet/Simulated.values");
    return failures == 0 ? 0 : 1;
}
