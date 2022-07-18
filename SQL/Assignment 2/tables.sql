/* Roni Jack Vituli - 315369967
    Boaz Biton - 204385413
*/
CREATE TABLE Sportsmen( 
fname VARCHAR2(100) ,  
lname VARCHAR2(100),
country VARCHAR2(30) NOT NULL,
age NUMBER(2,0) NOT NULL,
gender VARCHAR2(1) CHECK(gender = 'M' or gender = 'F'),
countofrecords NUMBER DEFAULT 0,
PRIMARY KEY(fname, lname));

CREATE TABLE Sports(
sname VARCHAR2(100), 
branch VARCHAR2(100),
team VARCHAR2(3) NOT NULL,  
gender VARCHAR2(1) CHECK(gender = 'M' or gender = 'F'),
PRIMARY KEY(sname, branch, gender));

CREATE TABLE Competitions(
fname VARCHAR2(100),
lname VARCHAR2(100),
sname VARCHAR2(100),
branch VARCHAR2(100),
gender VARCHAR2(1) CHECK(gender = 'M' or gender = 'F'),
takesplace DATE,
rank NUMBER(2,0),
record VARCHAR(2)  CHECK(record = 'WR' or record = 'OR' or record = 'PB' or record = 'NR' or record = 'NULL'),
FOREIGN KEY(fname, lname) REFERENCES Sportsmen(fname,lname),
FOREIGN KEY(sname, branch, gender) REFERENCES Sports(sname, branch, gender),
PRIMARY KEY(fname, lname, sname, branch, gender, takesplace));

