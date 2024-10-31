#include <drogon/drogon.h>
#include "log.hpp"

namespace esql::api {
    using drogon::HttpController;
    using drogon::HttpRequestPtr;
    using drogon::HttpResponsePtr;
    using drogon::HttpResponse;
    using drogon::Get;

    class Table : public HttpController<Table>
    {
    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(root, "/", Get);
        METHOD_ADD(hello, "/hello", Get);
        METHOD_LIST_END
    protected:
        void root(const HttpRequestPtr&,
            std::function<void(const HttpResponsePtr&)>&& callback)
        {
            LOG(INFO) << "Table/ROOT";
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("Table/root/");
            callback(resp);
        }
        void hello(const HttpRequestPtr&,
            std::function<void(const HttpResponsePtr&)>&& callback)
        {
            LOG(INFO) << "Table/HELLO";
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("Table/hello/");
            callback(resp);
        }
    };

}