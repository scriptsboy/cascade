// Copyright 2017-2019 VMware, Inc.
// SPDX-License-Identifier: BSD-2-Clause
//
// The BSD-2 license (the License) set forth below applies to all parts of the
// Cascade project.  You may not use this file except in compliance with the
// License.
//
// BSD-2 License
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef CASCADE_SRC_TARGET_INTERFACE_REMOTE_REMOTE_INTERFACE_H
#define CASCADE_SRC_TARGET_INTERFACE_REMOTE_REMOTE_INTERFACE_H

#include <cassert>
#include "src/base/stream/sockstream.h"
#include "src/target/common/rpc.h"
#include "src/target/interface.h"

namespace cascade {

class RemoteInterface : public Interface {
  public:
    explicit RemoteInterface(sockstream* sock, Rpc::Id id);
    ~RemoteInterface() override = default;

    void display(const std::string& s) override;
    void error(const std::string& s) override;
    void finish(int arg) override;
    void info(const std::string& s) override;
    void restart(const std::string& s) override;
    void retarget(const std::string& s) override;
    void save(const std::string& s) override;
    void warning(const std::string& s) override;
    void write(const std::string& s) override;

    void write(VId id, const Bits* b) override;
      
  private:
    sockstream* sock_;
    Rpc::Id id_;
}; 

inline RemoteInterface::RemoteInterface(sockstream* sock, Rpc::Id id) : Interface() {
  sock_ = sock;
  id_ = id;
}

inline void RemoteInterface::display(const std::string& s) {
  Rpc(Rpc::Type::DISPLAY, id_).serialize(*sock_);
  sock_->write(s.c_str(), s.length());
  sock_->put('\0');
}

inline void RemoteInterface::error(const std::string& s) {
  Rpc(Rpc::Type::ERROR, id_).serialize(*sock_);
  sock_->write(s.c_str(), s.length());
  sock_->put('\0');
}

inline void RemoteInterface::finish(int arg) {
  Rpc(Rpc::Type::FINISH, id_).serialize(*sock_);
  sock_->write(reinterpret_cast<const char*>(&arg), 4);
  sock_->flush();
}

inline void RemoteInterface::info(const std::string& s) {
  Rpc(Rpc::Type::INFO, id_).serialize(*sock_);
  sock_->write(s.c_str(), s.length());
  sock_->put('\0');
}

inline void RemoteInterface::restart(const std::string& s) {
  Rpc(Rpc::Type::RESTART, id_).serialize(*sock_);
  sock_->write(s.c_str(), s.length());
  sock_->put('\0');
}

inline void RemoteInterface::retarget(const std::string& s) {
  Rpc(Rpc::Type::RETARGET, id_).serialize(*sock_);
  sock_->write(s.c_str(), s.length());
  sock_->put('\0');
}

inline void RemoteInterface::save(const std::string& s) {
  Rpc(Rpc::Type::SAVE, id_).serialize(*sock_);
  sock_->write(s.c_str(), s.length());
  sock_->put('\0');
}

inline void RemoteInterface::warning(const std::string& s) {
  Rpc(Rpc::Type::WARNING, id_).serialize(*sock_);
  sock_->write(s.c_str(), s.length());
  sock_->put('\0');
}

inline void RemoteInterface::write(const std::string& s) {
  Rpc(Rpc::Type::WRITE, id_).serialize(*sock_);
  sock_->write(s.c_str(), s.length());
  sock_->put('\0');
}

inline void RemoteInterface::write(VId id, const Bits* b) {
  Rpc(Rpc::Type::WRITE_BITS, id_).serialize(*sock_);
  sock_->write(reinterpret_cast<const char*>(&id), 4);
  b->serialize(*sock_);
}

} // namespace cascade

#endif
