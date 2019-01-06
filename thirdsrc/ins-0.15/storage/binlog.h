#ifndef GALAXY_SDK_BINGLOG_H_
#define GALAXY_SDK_BINGLOG_H_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <boost/function.hpp>
#include "common/mutex.h"
#include "proto/ins_node.pb.h"
#include "leveldb/db.h"

namespace galaxy {
namespace ins {

struct LogEntry {
    LogOperation op;
    std::string user;
    std::string key;
    std::string value;
    int64_t term;
    LogEntry() : op(kNop), user(""), term(-1) {
    }
};

class BinLogger {
public:
    BinLogger(const std::string& data_dir, 
              bool compress = false,
              int32_t block_size = 32748,
              int32_t write_buffer_size = 33554432);
    ~BinLogger();
    int64_t GetLength();
    bool ReadSlot(int64_t slot_index, LogEntry* log_entry);
    void AppendEntry(const LogEntry& log_entry);
    void Truncate(int64_t trunc_slot_index);
    void DumpLogEntry(const LogEntry& log_entry, std::string* buf);
    void LoadLogEntry(const std::string& buf, LogEntry* log_entry);
    void AppendEntryList(
       const ::google::protobuf::RepeatedPtrField< ::galaxy::ins::Entry > &entries
    );
    bool RemoveSlot(int64_t slot_index);
    bool RemoveSlotBefore(int64_t slot_gc_index);
    static std::string IntToString(int64_t num);
    static int64_t StringToInt(const std::string& s);
    void GetLastLogIndexAndTerm(int64_t* last_log_index, int64_t* last_log_term);
private:
    leveldb::DB* db_;
    int64_t length_;
    int64_t last_log_term_;
    Mutex mu_;
};

} //namespace ins 
} //namespace galaxy

#endif
