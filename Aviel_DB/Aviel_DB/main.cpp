/* Aviel Dagan 203345061 */

#include <iostream>
#include "Aviel_DB.h"
using namespace std;

int main(int argc, const char * argv[]) {
    bool flag = true;
    int n;
    Aviel_DB& Aviel_DBAviel = Aviel_DB::getInstance();
    while(flag) {
        cout<<"Please choose an option and press ENTER:" << endl;
        cout<<"1. Show the number of albums that was recorded between 2 dates." << endl;
        cout<<"2. Show how much diffrent songs was record by a musician between 2 dates." << endl;
        cout<<"3. Show the number of diffrenet albums that a musician participated between 2 dates." << endl;
        cout<<"4. Show the most popular musical instrument." << endl;
        cout<<"5. Show the list of instruments in an album." << endl;
        cout<<"6. Show the most productive producer between 2 dates." << endl;
        cout<<"7. Show the most popular musicial instrument manufacturer." << endl;
        cout<<"8. Show the number of musicians that recorded through all years. " << endl;
        cout<<"9. Show the musician that collaborated with the most other musicians." << endl;
        cout<<"10. Show the most popular genre." << endl;
        cout<<"11. Show the technician that recorded the most number of songs betweeen 2 dates." << endl;
        cout<<"12. Show the first album that was recorded in the studio." << endl;
        cout<<"13. Show the list of songs that are in 2 or more albums." << endl;
        cout<<"14. Show the list of technicians who participated in the recording of an entire album." << endl;
        cout<<"15. Show the most versatile musician." << endl << endl;
        cout<<"0. Exit"<<endl;
        
        cin >> n;
        switch (n) {
            case 1: {
                Aviel_DBAviel.query1();
                break;
            }
            case 2: {
                Aviel_DBAviel.query2();
                break;
            }
            case 3: {
                Aviel_DBAviel.query3();
                break;
            }
            case 4: {
                Aviel_DBAviel.query4();
                break;
            }
            case 5: {
                Aviel_DBAviel.query5();
                break;
            }
            case 6: {
                Aviel_DBAviel.query6();
                break;
            }
            case 7: {
                Aviel_DBAviel.query7();
                break;
            }
            case 8: {
                Aviel_DBAviel.query8();
                break;
            }
            case 9: {
                Aviel_DBAviel.query9();
                break;
            }
            case 10: {
                Aviel_DBAviel.query10();
                break;
            }
            case 11: {
                Aviel_DBAviel.query11();
                break;
            }
            case 12: {
                Aviel_DBAviel.query12();
                break;
            }
            case 13: {
                Aviel_DBAviel.query13();
                break;
            }
            case 14: {
                Aviel_DBAviel.query14();
                break;
            }
            case 15: {
                Aviel_DBAviel.query15();
                break;
            }
            case 0: {
                cout << "The End" << endl << endl;
                flag = false;
                break;
            }
            default:
                cout << "Wrong option number, please choose another number." << endl << endl;
                break;
        }
    }
    return 0;
}
