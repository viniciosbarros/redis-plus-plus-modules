/**
 * Copyright 2021 Pieter du Preez <pdupreez@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/

#ifndef REDIS_PLUS_PLUS_REDIS_JSON_H
#define REDIS_PLUS_PLUS_REDIS_JSON_H

#include "Module.h"

namespace redis::module {

template <typename RedisInstance>
class RedisJSON : public Module<RedisInstance>
{
public:
    enum class DelOpt{ NX = 0, XX = 1 };

    explicit RedisJSON(RedisInstance& redis)
        : Module<RedisInstance>(redis, "ReJSON", "JSON")
        {}

    auto del(const sw::redis::StringView& key) {
        return Module<RedisInstance>::_redis.template
            command<long long>("JSON.DEL", key);
    }

    auto del(const sw::redis::StringView& key,
             const sw::redis::StringView& path) {
        return Module<RedisInstance>::_redis.template
            command<long long>("JSON.DEL", key, path);
    }

    auto forget(const sw::redis::StringView& key) {
        return Module<RedisInstance>::_redis.template
            command<long long>("JSON.DEL", key);
    }

    auto forget(const sw::redis::StringView& key,
                const sw::redis::StringView& path) {
        return Module<RedisInstance>::_redis.template
            command<long long>("JSON.DEL", key, path);
    }

    bool set(const sw::redis::StringView& key,
             const sw::redis::StringView& path,
             const sw::redis::StringView& value,
             const DelOpt& opt = DelOpt::NX) {
        auto ret = Module<RedisInstance>::_redis.template
            // TODO: Find out if we should json-escape value.
            command<sw::redis::OptionalString>
            ("JSON.SET", key, path,
             std::string("\"") + value.data() + "\"",
             (opt == DelOpt::NX) ? "NX" : "XX");
        return (ret && *ret == "OK");
    }

    bool set(const sw::redis::StringView& key,
             const sw::redis::StringView& path,
             long long value,
             const DelOpt& opt = DelOpt::NX) {
        auto ret = Module<RedisInstance>::_redis.template
            command<sw::redis::OptionalString>
            ("JSON.SET", key, path, value,
             (opt == DelOpt::NX) ? "NX" : "XX");
        return (ret && *ret == "OK");
    }

    auto strlen(const sw::redis::StringView& key) {
        return Module<RedisInstance>::_redis.template
            command<long long>("JSON.STRLEN", key);
    }

    auto strlen(const sw::redis::StringView& key,
                const sw::redis::StringView& path) {
        return Module<RedisInstance>::_redis.template
            command<long long>("JSON.STRLEN", key, path);
    }

    auto type(const sw::redis::StringView& key) {
        return Module<RedisInstance>::_redis.template
            command<std::string>("JSON.TYPE", key);
    }

    auto type(const sw::redis::StringView& key,
              const sw::redis::StringView& path) {
        return Module<RedisInstance>::_redis.template
            command<std::string>("JSON.TYPE", key, path);
    }

    auto resp(const sw::redis::StringView& key) {
        return Module<RedisInstance>::_redis.template
            command<std::string>("JSON.RESP", key);
    }

    auto resp(const sw::redis::StringView& key,
              const sw::redis::StringView& path) {
        return Module<RedisInstance>::_redis.template
            command<std::string>("JSON.RESP", key, path);
    }

    auto numincrby(const sw::redis::StringView& key,
                   const sw::redis::StringView& path,
                   long long num) {
        return std::stoll(Module<RedisInstance>::_redis.template
                          command<std::string>("JSON.NUMINCRBY", key, path, num));
    }

    auto nummultby(const sw::redis::StringView& key,
                   const sw::redis::StringView& path,
                   long long num) {
        return std::stoll(Module<RedisInstance>::_redis.template
                          command<std::string>("JSON.NUMMULTBY", key, path, num));
    }

    auto strappend(const sw::redis::StringView& key,
                   const sw::redis::StringView& str) {
        return Module<RedisInstance>::_redis.template
            command<long long>("JSON.STRAPPEND", key,
                               std::string("\"") + str.data() + "\"");
    }

    auto strappend(const sw::redis::StringView& key,
                   const sw::redis::StringView& path,
                   const sw::redis::StringView& str) {
        return Module<RedisInstance>::_redis.template
            command<long long>("JSON.STRAPPEND", key, path,
                               std::string("\"") + str.data() + "\"");
    }

};

} // namespace

#endif