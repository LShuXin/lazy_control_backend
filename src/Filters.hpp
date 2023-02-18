//
// Created by apple on 2022/8/18.
//

#ifndef LAZY_CONTROL_BACKEND_FILTERS_H
#define LAZY_CONTROL_BACKEND_FILTERS_H

#include <string>
#include <regex>
#include <cstdlib>
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "dto/QueryParamsDto.hpp"
#include "utils/UrlEncodeDecode.hpp"

using namespace std;

template <class T>
class QueryParamsMathRes {
public:
    string sort[2] = {};
    int range[2]  = {0 , 0};
    oatpp::Object<T> filter;
};

QueryParamsMathRes<NormalFilterDto> matchQueryParams(oatpp::web::server::api::ApiController::QueryParams queryParams) {
    // 首先对url进行decode
    string rangeString = UrlDecode(queryParams.get("range")->c_str());
    string sortString = UrlDecode(queryParams.get("sort")->c_str()).data();
    string filterString = UrlDecode(queryParams.get("filter")->c_str()).data();

     // OATPP_LOGD("param", "%s", rangeString.data());
     // OATPP_LOGD("param", "%s", sortString.data());
     // OATPP_LOGD("param", "%s", filterString.data());

    QueryParamsMathRes<NormalFilterDto> queryParamsMathRes;

    string rangeBegString;
    string rangeEndString;
    string sortFieldString;
    string sortOrderString;
    smatch match1;
    smatch match2;
    regex rangePattern("\\[(\\d+),(\\d+)\\]");
    regex sortPattern("\\[\"([a-z_]+)\",\"([A-Z]+)\"");

    if (regex_search(rangeString, match1, rangePattern))
    {
        for (size_t i = 1; i < match1.size(); ++i)
        {
            // cout << "range:" << match1[i] << endl;
            queryParamsMathRes.range[i - 1] = std::atoi(match1[i].str().c_str());
        }
    }



    if (regex_search(sortString, match2, sortPattern))
    {
        for (size_t i = 1; i < match2.size(); ++i)
        {
            // cout << "sort:" << match2[i] << endl;
            queryParamsMathRes.sort[i - 1] = match2[i].str();
        }
    }

    /* create json ObjectMapper with default configs */
    auto jsonObjectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

    auto res = jsonObjectMapper->readFromString<oatpp::Object<NormalFilterDto>>(filterString);


     // ATPP_LOGD("", "%s", queryParamsMathRes.sort[0].c_str())
     // ATPP_LOGD("", "%s", queryParamsMathRes.sort[1].c_str())
     // ATPP_LOGD("", "%d", queryParamsMathRes.range[0])
     // ATPP_LOGD("", "%d", queryParamsMathRes.range[1])
    // cout << res->post_id << endl;

    // 反序列化
    queryParamsMathRes.filter = res;
    return queryParamsMathRes;
}

#endif //LAZY_CONTROL_BACKEND_FILTERS_H
