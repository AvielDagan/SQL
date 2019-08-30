/* Aviel Dagan 203345061 */

#include "Aviel_DB.h"
#include <iostream>
#include <string>

Aviel_DB *Aviel_DB::instance = 0;

Aviel_DB::Aviel_DB() : driver(get_driver_instance()) {
    connection_properties["hostName"] = Aviel_DB_HOST;
    connection_properties["port"] = Aviel_DB_PORT;
    connection_properties["userName"] = Aviel_DB_USER;
    connection_properties["password"] = Aviel_DB_PASS;
    connection_properties["OPT_RECONNECT"] = true;
    // use database
    try {
        Connection *connection = driver->connect(connection_properties);
        try {
            connection->setSchema(Aviel_DB_NAME);
        }
        catch (SQLException &e) {
            cout << "ERROR";
        }
        
        delete connection;
    }
    catch (SQLException &e) {
        cout << e.getErrorCode() << " " << e.what() << " " << e.getSQLState();
        throw e;
    }
}

Aviel_DB & Aviel_DB::getInstance() {
    if (Aviel_DB::instance == 0) {
        instance = new Aviel_DB();
    }
    return *instance;
}
Connection * Aviel_DB::getConnection() {
    try {
        Connection *connection = driver->connect(connection_properties);
        connection->setSchema(Aviel_DB_NAME);
        return connection;
    } catch (SQLException &e) {
        cout << e.what();
    }
    return 0;
}

void Aviel_DB::query1() {
    string Date1, Date2;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> Date1;
    cout << "Please enter finish date (yyyy-mm-dd)" << endl;
    cin >> Date2;
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    PreparedStatement *state = connection->prepareStatement("SELECT COUNT(*) AS counter FROM albumtable WHERE Start_Date>='"+Date1+"' AND Finish_Date<= '"+Date2+"' ;");
    ResultSet *res = state->executeQuery();
    res->first();
    cout<<"The number of albums is: "<<res->getUInt("counter");
    cout << endl<<endl;
    delete connection;
    delete state;
    delete res;
}

void Aviel_DB::query2 () {
    string fName,lName,Date1,Date2;
    cout<< "Enter musician first name:";
    cin>> fName;
    cout<< "Enter musician last name:";
    cin>> lName;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> Date1;
    cout << "Please enter finish date (yyyy-mm-dd)" << endl;
    cin >> Date2;
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    
    PreparedStatement *state = connection->prepareStatement("SELECT COUNT(*) FROM songtable WHERE Record_Date between '"+Date1+"' AND '"+Date2+"' AND ID_Song in (SELECT songid FROM musicinsongtable WHERE musicinsong_id in (SELECT Musician_ID FROM musiciantable WHERE Musician_FName='"+fName+"' AND Musician_LName='"+lName+"')); ");
    ResultSet *res = state->executeQuery();
    res->first();
    cout<<"The number of songs:" <<res->getUInt(1);
    cout << endl<<endl;
    delete connection;
    delete state;
    delete res;
}

void Aviel_DB::query3 () {
    string fName,lName,Date1,Date2;
    cout<< "Enter musician first name:";
    cin>> fName;
    cout<< "Enter musician last name:";
    cin>> lName;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> Date1;
    cout << "Please enter finish date (yyyy-mm-dd)" << endl;
    cin >> Date2;
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    
    
    PreparedStatement *state = connection->prepareStatement("SELECT count(*) from (SELECT distinct Albums_ID from songsalbumtable where Song_ID in (SELECT ID_Song FROM songtable WHERE Record_Date between '"+Date1+"' AND '"+Date2+"' AND ID_Song in (SELECT songid FROM musicinsongtable WHERE musicinsong_id in (SELECT Musician_ID FROM musiciantable WHERE Musician_FName='"+fName+"' AND Musician_LName='"+lName+"'))))A;");
    
    ResultSet *res = state->executeQuery();
    res->first();
    cout<<"The number of albums is:" <<res->getUInt(1);
    cout << endl<<endl;
    delete connection;
    delete state;
    delete res;
}

void Aviel_DB::query4 () {
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    Statement *stmt = connection->createStatement();
    ResultSet *res = stmt->executeQuery("SELECT Instrument_Name FROM instrumenttable where  ID_Instrument in (SELECT Instrument_ID from manufacinstrutable where ID_ManufacInstru in (select Play_ManufacInstruID from (SELECT Play_ManufacInstruID,count(*) from playinstrumenttable GROUP BY Play_ManufacInstruID ORDER BY count(*) DESC limit 1)A))");
    res->first();
    cout<<"The most popular instrument is: "<< res->getString("instrument_name");
    cout<< endl<<endl;
    delete connection;
    delete stmt;
    delete res;
}

void Aviel_DB::query5 () {
    string albumName;
    cout<< "Enter Album Name:";
    cin>> albumName;
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    
    PreparedStatement *state = connection->prepareStatement("SELECT Instrument_Name FROM instrumenttable where  ID_Instrument in (SELECT Instrument_ID from manufacinstrutable where ID_ManufacInstru in (SELECT distinct Play_ManufacInstruID FROM playinstrumenttable where Play_SongID IN (SELECT Song_ID from songsalbumtable where Albums_ID= (SELECT ID_Album FROM albumtable where Album_Name='"+albumName+"'))));");
    
    ResultSet *res = state->executeQuery();
    res->beforeFirst();
    int count = 1;
    cout<<"List of all instruments in album " << albumName <<" :"<<endl;
    while(res->next()){
        cout<<count<<". " << res->getString("instrument_name")<<endl;
        count++;
    }
    delete connection;
    delete state;
    delete res;
    
}


void Aviel_DB::query6 () {
    string Date1, Date2;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> Date1;
    cout << "Please enter finish date (yyyy-mm-dd)" << endl;
    cin >> Date2;
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    PreparedStatement *state = connection->prepareStatement("select Producer_FName,Producer_LName from producertable where ID_Producer in (select Producer_ID from (select Producer_ID,count(*) from produced_by where Album_ID in(select ID_Album from albumtable where Start_Date>'"+Date1+"' AND Finish_Date <'"+Date2+"') group by Producer_ID ORDER BY COUNT(*) DESC LIMIT 1)a)");
    
    ResultSet *res = state->executeQuery();
    res->first();
    cout<<"The most Productive Producer is: "<<res->getString("Producer_FName")<<" "<< res->getString("Producer_LName");
    cout<< endl<<endl;
    delete connection;
    delete state;
    delete res;
}

void Aviel_DB::query7 () {
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    Statement *stmt = connection->createStatement();
    ResultSet *res = stmt->executeQuery("select Manufacturer_Name from manufacturetable where ID_Manufacturer in (select Manufacturer_ID from (select Manufacturer_ID,count(*) from  playinstrumenttable INNER JOIN manufacinstrutable ON playinstrumenttable.Play_ManufacInstruID=manufacinstrutable.ID_ManufacInstru GROUP BY Manufacturer_ID ORDER BY count(*) DESC LIMIT 1)a)");
    res->first();
    cout<<"The most popular manufacturer is: "<< res->getString("manufacturer_name");
    cout<< endl<<endl;
    delete connection;
    delete stmt;
    delete res;
}

void Aviel_DB::query8 () {
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    Statement *stmt = connection->createStatement();
    ResultSet *res = stmt->executeQuery("select count(*) from(select distinct musicinsong_id from musicinsongtable)a");
    res->first();
    cout<<"The number of Musician: "<< res->getUInt(1);
    cout<< endl<<endl;
    delete connection;
    delete stmt;
    delete res;
}

void Aviel_DB::query9 () {
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    Statement *stmt = connection->createStatement();
    ResultSet *res = stmt->executeQuery("select Musician_FName, Musician_LName FROM musiciantable where Musician_ID in(SELECT musicinsong_id from((SELECT musicinsong_id,sum(popular) from(SELECT * FROM(select songid as id,(count(*)-1) as popular from musicinsongtable GROUP BY songid) as A INNER JOIN musicinsongtable ON A.id = musicinsongtable.songid) AS B group by musicinsong_id)  ORDER BY sum(popular) DESC LIMIT 1)C);");
    res->first();
    cout<<"The collaborative musician: "<< res->getString("musician_fname")<<" " <<res->getString("musician_lname");
    cout<< endl<<endl;
    delete connection;
    delete stmt;
    delete res;
}

void Aviel_DB::query10 () {
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    Statement *stmt = connection->createStatement();
    ResultSet *res = stmt->executeQuery("SELECT song_genre,count(*) from songtable GROUP BY song_genre ORDER BY count(*) DESC limit 1");
    res->first();
    cout<<"The most popular genre is: "<< res->getString("song_genre");
    cout<< endl<<endl;
    delete connection;
    delete stmt;
    delete res;
}

void Aviel_DB::query11 () {
    string Date1, Date2;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> Date1;
    cout << "Please enter finish date (yyyy-mm-dd)" << endl;
    cin >> Date2;
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    PreparedStatement *state = connection->prepareStatement("SELECT Tech_FName,Tech_LName from techtable where ID_Tech in (SELECT song_techid from ((SELECT song_techid,count(*) from songtable where record_date between '"+Date1+"' and '"+Date2+"' group by song_techid) ORDER BY count(*) DESC LIMIT 1)A);");
    //    state->setString(1, Date1);
    //    state->setString(2, Date2);
    ResultSet *res = state->executeQuery();
    res->first();
    cout<<"The most Prodective technician is: "<<res->getString("Tech_FName")<<" "<< res->getString("Tech_LName");
    cout<< endl<<endl;
    delete connection;
    delete state;
    delete res;
}

void Aviel_DB::query12 () {
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    Statement *stmt = connection->createStatement();
    ResultSet *res = stmt->executeQuery("SELECT Album_Name FROM albumtable order by Finish_Date ASC LIMIT 1");
    res->first();
    cout<<"The first album recorded is: "<< res->getString("album_name");
    cout<< endl<<endl;
    delete connection;
    delete stmt;
    delete res;
}

void Aviel_DB::query13 () {
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    Statement *stmt = connection->createStatement();
    ResultSet *res = stmt->executeQuery("select Song_Name from songtable where ID_Song IN (SELECT Song_ID from songsalbumtable group by Song_ID HAVING count(*)>1);");
    res->beforeFirst();
    int count = 1;
    if (res == NULL){
        cout << "There is no song that are in more than one album" << endl;
    }
    
    cout<<"List of all song that are in more than one album:"<<endl;
    while(res->next()){
        cout<<count<<". " << res->getString("song_name")<<endl;
        count++;
    }
    
    cout<< endl<<endl;
    delete connection;
    delete stmt;
    delete res;
}

void Aviel_DB::query14 () {
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    Statement *stmt = connection->createStatement();
    ResultSet *res = stmt->executeQuery("select Tech_FName,Tech_LName from techtable where ID_Tech in (SELECT distinct Song_TechID FROM(SELECT Song_TechID,Albums_ID FROM songtable INNER JOIN songsalbumtable ON songsalbumtable.Song_ID = songtable.ID_Song)B WHERE Albums_ID in (SELECT Albums_ID FROM (SELECT Albums_ID,count(*) as producerNum from (SELECT distinct Song_TechID,Albums_ID FROM songtable INNER JOIN songsalbumtable ON songsalbumtable.Song_ID = songtable.ID_Song)A GROUP BY Albums_ID)A where producerNum=1)) ;");
    res->beforeFirst();
    int count = 1;
    cout<<"list of technicians  who participated in the recording of an entire album:"<<endl;
    while(res->next()){
        cout<<count<<". " << res->getString("tech_fname")<<" " <<res->getString("tech_lname")<<endl;
        count++;
    }
    cout<< endl<<endl;
    delete connection;
    delete stmt;
    delete res;
}

void Aviel_DB::query15() {
    Connection *connection = driver->connect(connection_properties);
    connection->setSchema(Aviel_DB_NAME);
    Statement *stmt = connection->createStatement();
    ResultSet *res = stmt->executeQuery("select Musician_FName,Musician_LName from musiciantable WHERE Musician_ID IN (SELECT musicinsong_id from ((SELECT musicinsong_id,COUNT(*) from(SELECT distinct Song_Genre,musicinsong_id FROM songtable INNER JOIN musicinsongtable ON musicinsongtable.songid = songtable.ID_Song)AS B group by musicinsong_id) ORDER BY COUNT(*) DESC LIMIT 1)A);");
    res->first();
    cout<<"The most versatile musician is: "<< res->getString("musician_fname")<<" " <<res->getString("musician_lname");
    cout<< endl<<endl;
    delete connection;
    delete stmt;
    delete res;
}

