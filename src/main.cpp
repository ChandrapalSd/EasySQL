#include "log.hpp"
#include "db.hpp"
#include <nanodbc/nanodbc.h>
#include <algorithm>
#include <cstring>
#include <api/api.hpp>


void show(nanodbc::result& results)
{
    const short columns = results.columns();
    long rows_displayed = 0;

    LOG(INFO) << "\nDisplaying " << results.affected_rows() << " rows "
        << "(" << results.rowset_size() << " fetched at a time):" ;

    // show the column names
    LOG(INFO) << "row\t";
    for (short i = 0; i < columns; ++i)
        LOG(INFO) << results.column_name(i) << "\t";
    LOG(INFO) ;

    // show the column data for each row
    while (results.next())
    {
        LOG(INFO) << rows_displayed++ << "\t";
        for (short col = 0; col < columns; ++col)
            LOG(INFO) << "(" << results.get<nanodbc::string>(col, "null") << ")\t";
        LOG(INFO) << std::endl;
    }
}

void initLogging(const char* argv0)
{
    google::InitGoogleLogging(argv0);
    FLAGS_logtostderr = 1;
    LOG(INFO) << "Glog is initalized";
    LOG(INFO) << "Running : " << argv0;
}

int main(int argc, char* argv[])
{
    initLogging(argv[0]);
    std::string conStr = "Driver={MySQL ODBC 8.0 Unicode Driver};Server=localhost;Database=rbdb;UID=root;PWD=3690;Port=3306;";
    

    if (argc != 2)
    {
       LOG(WARNING) << "Using default connection string : " << conStr;
    }
    else 
    {
        conStr = argv[1];
    }

    try
    {
        esql::DB db(conStr);
        esql::api::run(db);
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << e.what() ;
    }
    return EXIT_FAILURE;
}
