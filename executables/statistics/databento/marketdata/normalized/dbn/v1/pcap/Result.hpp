// Databento.MarketData.Normalized.Dbn.v1: pcap/Result.hpp
#pragma once

namespace packet {

    enum class result {
        databento_marketdata_normalized_dbn_v1,
        error,
        end_of_file,
        unknown
    };

}