#include "api/api.hpp"
#include <drogon/drogon.h>
#include "log.hpp"

namespace esql::api {
	


	void run() {

		
		drogon::app().registerHandler(
			"/",
			[](const drogon::HttpRequestPtr& request,
				std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
					LOG(INFO) << "GET : /";
					LOG(INFO) << "connected:" << (request->connected() ? "true" : "false");
					auto resp = drogon::HttpResponse::newHttpResponse();
					resp->setBody("Hello, World!");
					callback(resp);
			},
			{ drogon::Get });


		const uint32_t port = 8848;
		const std::string ip = "127.0.0.1";
		LOG(INFO) << "Listening at IP : " << ip << " PORT : " << port;
		LOG(INFO) << std::format("http://{}/{}", ip, port);
		drogon::app().addListener(ip, port).run();
	}

}
