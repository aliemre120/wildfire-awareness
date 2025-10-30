// db.h
#ifndef DB_H
#define DB_H

#include <stdbool.h>

#define DB_PATH "wildfire.db"

typedef struct {
    int  id;
    char datetime[20];   // to add the date and time of the report
    char location[128];  // location description
    char status[16];     // specific status: "active" or "extinguished"
} FireRecord;

//it start the database and create the table if it does not exist
bool db_init(void);

// add a new fire report
int  db_add_fire(const char *location);

// make status extinguished
bool db_extinguish_fire(int id);

// list active fires
void db_list_active(int english);
void db_list_all(int english);

#endif
