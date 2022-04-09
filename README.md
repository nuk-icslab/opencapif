# OpenCAPIF

A general API invocation framework based-on 3GPP Common API Framework (CAPIF)

## Features

- Authentication, Authorization and Accounting on API invocation
- Publish and discover service API
- Logging service API invocation
- Management of service API and API invokers

## Entities

- Standalone CAPIF Core Function(CCF) executable written in C++
- Language-agnostic API Exposing Function(AEF) based-on Nginx module 
- WebUI of API Publishing Function(APF) and API Management Function(AMF)
- API-invoker agent library across multiple programming language
    - Currently support JavaScript

## Dependency

### CCF
- [mongocxx, bsoncxx](http://mongocxx.org/)
- [pistache](https://github.com/pistacheio/pistache)
- [spdlog](https://github.com/gabime/spdlog)
- [nlohmann_json](https://github.com/nlohmann/json)
- [fmt](https://github.com/fmtlib/fmt)
- [yaml-cpp](https://github.com/jbeder/yaml-cpp)

## References

- 3GPP, TS 23.222 v17.5.0, "Common API Framework for 3GPP Northbound APIs"
- 3GPP, TS 29.222 v17.5.0, "Common API Framework for 3GPP Northbound APIs"
- 3GPP, TS 33.122 v17.0.0, "Security aspects of Common API Framework (CAPIF) for 3GPP northbound APIs"
- 3GPP, TR 23.722 v15.1.0, "Study on common Application Programming Interface (API) framework for 3GPP northbound APIs"
