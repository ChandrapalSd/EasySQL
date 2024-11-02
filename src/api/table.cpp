#include <drogon/drogon.h>
#include "api/api.hpp"
#include "log.hpp"

namespace esql::api {
    using drogon::HttpController;
    using drogon::HttpRequestPtr;
    using drogon::HttpResponsePtr;
    using drogon::HttpResponse;
    using drogon::Get;

    Json::Value getJson(const Column& column) {
        Json::Value json;
        json["name"] = column.name;
        json["type"] = column.type;
        json["nullable"] = column.nullable;

        return json;
    }

    Json::Value getJson(const Table& table) {
        Json::Value json;
        json["name"] = table.name;
        
        for(const Column& column: table.columns)
            json["columns"].append(getJson(column));

        return json;
    }

    class TableApi : public HttpController<TableApi>
    {
    public:
        METHOD_LIST_BEGIN
        METHOD_ADD(allTables, "/", Get);
        METHOD_ADD(getTable, "/{tableName}", Get);
        METHOD_LIST_END
    protected:
        void allTables(const HttpRequestPtr&,
            std::function<void(const HttpResponsePtr&)>&& callback)
        {
            LOG(INFO) << "Table/ : #allTables";

            const auto& tables = getDB().getAllTables();

            Json::Value json;
            
            for (const Table& table: tables)
                json.append(getJson(table));

            auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
            callback(resp);
        }
        
        void getTable(const HttpRequestPtr&,
            std::function<void(const HttpResponsePtr&)>&& callback,
            const std::string& tableName)
        {
            LOG(INFO) << std::format("Table/{} : getTable", tableName);
            LOG(INFO) << tableName;

            Json::Value json;
            HttpResponsePtr resp;

            if (tableName.length() > 0) {
                auto table = getDB().getTable(tableName);
                if (table) {
                    json = getJson(table.value());
                    resp = drogon::HttpResponse::newHttpJsonResponse(json);
                    resp->setStatusCode(drogon::k302Found);
                }
                else {
                    json["error"] = std::format("No table found with name : {}", tableName);
                    resp = drogon::HttpResponse::newHttpJsonResponse(json); 
                    resp->setStatusCode(drogon::k404NotFound);
                }
            }
            else {
                    json["error"] = std::format("Empty table name");
                    resp = drogon::HttpResponse::newHttpJsonResponse(json); 
                    resp->setStatusCode(drogon::k400BadRequest);
            }

            callback(resp);

        }
    };

}