#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <unordered_map>
#include <vector>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "../pcap/TcpReassembler.hpp"
#include "cpp/binary/modern/databento/marketdata/normalized/dbn/v3/definitions.hpp"

namespace statistics {

// Databento Dbn C++ statistics
struct Statistics {

    databento::marketdata::normalized::dbn::v3::RecordIterator record;
    packet::TcpReassembler record_reassembler;
    std::unordered_map<packet::TcpFlowKey, std::vector<std::uint8_t>, packet::TcpFlowKey::hash> record_flows;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t trade_msg = 0;
    uint64_t mbp_1_msg = 0;
    uint64_t mbp_10_msg = 0;
    uint64_t ohlcv_msg = 0;
    uint64_t status_msg = 0;
    uint64_t instrument_def_msg = 0;
    uint64_t imbalance_msg = 0;
    uint64_t error_msg = 0;
    uint64_t symbol_mapping_msg = 0;
    uint64_t system_msg = 0;
    uint64_t stat_msg = 0;
    uint64_t mbo_msg = 0;
    uint64_t cmbp_1_msg = 0;
    uint64_t cbbo_msg = 0;
    uint64_t bbo_msg = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {
        record_reassembler.on_data = [this](const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) { record_flow(key, data, length); };
    }

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_tcp()) {
            record_reassembler.process(frame);
        }
    }

    // walk the Gateway Stream tree's reassembled bytes
    void record_flow(const packet::TcpFlowKey& key, const std::byte* data, std::size_t length) {
        auto& bytes = record_flows[key];
        bytes.insert(bytes.end(),
                     reinterpret_cast<const std::uint8_t*>(data),
                     reinterpret_cast<const std::uint8_t*>(data) + length);

        const auto* base = reinterpret_cast<const std::byte*>(bytes.data());
        record.initialize(base, bytes.size());

        std::size_t consumed = 0;

        while (record.next()) {
            if (record.current > record.end) { break; }   // the packet's bytes have not all arrived

            consumed = static_cast<std::size_t>(record.current - base);
            process_record(record.message, record.rtype);
        }

        // drop what was read, keeping the packet that is still arriving
        if (consumed > 0) {
            bytes.erase(bytes.begin(), bytes.begin() + static_cast<std::ptrdiff_t>(consumed));
        }
    }

    // count a message of the Gateway Stream tree
    void process_record(const std::byte*, const std::uint8_t rtype) {
        switch (rtype) {
            case 0:
                ++total_messages;
                ++trade_msg;
                break;
            case 1:
                ++total_messages;
                ++mbp_1_msg;
                break;
            case 10:
                ++total_messages;
                ++mbp_10_msg;
                break;
            case 17:
                ++total_messages;
                ++ohlcv_msg;
                break;
            case 18:
                ++total_messages;
                ++status_msg;
                break;
            case 19:
                ++total_messages;
                ++instrument_def_msg;
                break;
            case 20:
                ++total_messages;
                ++imbalance_msg;
                break;
            case 21:
                ++total_messages;
                ++error_msg;
                break;
            case 22:
                ++total_messages;
                ++symbol_mapping_msg;
                break;
            case 23:
                ++total_messages;
                ++system_msg;
                break;
            case 24:
                ++total_messages;
                ++stat_msg;
                break;
            case 32:
                ++total_messages;
                ++ohlcv_msg;
                break;
            case 33:
                ++total_messages;
                ++ohlcv_msg;
                break;
            case 34:
                ++total_messages;
                ++ohlcv_msg;
                break;
            case 35:
                ++total_messages;
                ++ohlcv_msg;
                break;
            case 36:
                ++total_messages;
                ++ohlcv_msg;
                break;
            case 160:
                ++total_messages;
                ++mbo_msg;
                break;
            case 177:
                ++total_messages;
                ++cmbp_1_msg;
                break;
            case 192:
                ++total_messages;
                ++cbbo_msg;
                break;
            case 193:
                ++total_messages;
                ++cbbo_msg;
                break;
            case 194:
                ++total_messages;
                ++cmbp_1_msg;
                break;
            case 195:
                ++total_messages;
                ++bbo_msg;
                break;
            case 196:
                ++total_messages;
                ++bbo_msg;
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown rtype: " << static_cast<int>(rtype) << std::endl;
                }
                break;
        }
    }

    // report statistics
    void report() {
        std::cout << std::endl;
        std::cout << "Statistics Report" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Total packets:   " << total_packets << std::endl;
        std::cout << "Unknown packets: " << unknown_packets << std::endl;
        std::cout << "Total messages:  " << total_messages << std::endl;
        std::cout << "Unknown types:   " << unknown_messages << std::endl;
        std::cout << "Heartbeats:      " << heartbeats << std::endl;

        std::cout << std::endl;
        std::cout << "Message Counts:" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "  TradeMsg (0)           " << trade_msg << std::endl;
        std::cout << "  Mbp1Msg (1)            " << mbp_1_msg << std::endl;
        std::cout << "  Mbp10Msg (10)          " << mbp_10_msg << std::endl;
        std::cout << "  OhlcvMsg (17)          " << ohlcv_msg << std::endl;
        std::cout << "  StatusMsg (18)         " << status_msg << std::endl;
        std::cout << "  InstrumentDefMsg (19)  " << instrument_def_msg << std::endl;
        std::cout << "  ImbalanceMsg (20)      " << imbalance_msg << std::endl;
        std::cout << "  ErrorMsg (21)          " << error_msg << std::endl;
        std::cout << "  SymbolMappingMsg (22)  " << symbol_mapping_msg << std::endl;
        std::cout << "  SystemMsg (23)         " << system_msg << std::endl;
        std::cout << "  StatMsg (24)           " << stat_msg << std::endl;
        std::cout << "  MboMsg (160)           " << mbo_msg << std::endl;
        std::cout << "  Cmbp1Msg (177)         " << cmbp_1_msg << std::endl;
        std::cout << "  CbboMsg (192)          " << cbbo_msg << std::endl;
        std::cout << "  BboMsg (195)           " << bbo_msg << std::endl;
    }
};
}
