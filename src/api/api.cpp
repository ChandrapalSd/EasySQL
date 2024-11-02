#include "api/api.hpp"
#include <drogon/drogon.h>
#include "log.hpp"

namespace esql::api {

	static DB* dbPtr = NULL;

	void run(DB& db) {
		dbPtr = &db;
		const uint32_t port = 8848;
		const std::string ip = "127.0.0.1";

		drogon::app().registerHandler("/", 
			[](const drogon::HttpRequestPtr& request,
			std::function<void(const drogon::HttpResponsePtr&)>&& callback)
			{

				LOG(INFO) << "GET : /";
				LOG(INFO) << "connected:" << (request->connected() ? "true" : "false");
				auto resp = drogon::HttpResponse::newHttpResponse();
				resp->setBody("Hello, World!");
				callback(resp);
			}, { drogon::Get });
		
		drogon::app().registerHandler("/db", 
			[](const drogon::HttpRequestPtr& request,
			std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

				LOG(INFO) << "GET : /dbInfo";
				auto info = getDB().getInfo();

				Json::Value json;
				json["dbms_name"] = info.dbms_name;
				json["dbms_version"] = info.dbms_version;
				json["driver_name"] = info.driver_name;
				json["driver_version"] = info.driver_version;
				json["database_name"] = info.database_name;
				json["catalog_name"] = info.catalog_name;

				auto resp = drogon::HttpResponse::newHttpJsonResponse(json);

				callback(resp);
			}, { drogon::Get });

		LOG(INFO) << std::format("Listening at http://{}/{}", ip, port);
		drogon::app().addListener(ip, port).run();
	}

	DB& getDB()
	{
		return *dbPtr;
	}

}
