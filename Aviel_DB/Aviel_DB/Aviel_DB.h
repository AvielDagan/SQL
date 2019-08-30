/* Aviel Dagan 203345061 */

#ifndef Aviel_DB_h
#define Aviel_DB_h
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
using namespace sql;
using namespace std;
#define Aviel_DB_NAME "Aviel_Dagan"
#define Aviel_DB_HOST "tcp://127.0.0.1/"
#define Aviel_DB_PORT 3306
#define Aviel_DB_USER "root"
#define Aviel_DB_PASS "yourpassword"

class Aviel_DB {
private:
    static Aviel_DB *instance;
    
    Driver *driver;
    ConnectOptionsMap connection_properties;
    
    Aviel_DB();
public:
    static Aviel_DB& getInstance();
    
    Connection *getConnection();
    
    void query1 ();
    void query2  ();
    void query3 ();
    void query4 ();
    void query5 ();
    void query6 ();
    void query7 ();
    void query8 ();
    void query9 ();
    void query10 ();
    void query11 ();
    void query12 ();
    void query13 ();
    void query14  ();
    void query15 ();
    virtual ~Aviel_DB() {}
};
#endif
