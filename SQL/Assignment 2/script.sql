/* Roni Jack Vituli - 315369967
    Boaz Biton - 204385413
*/

SET SERVEROUTPUT ON;

------------------------------------------------------------------------------------------------A------------------------------------------------------------------------------------------------------------------------------------------------

CREATE OR REPLACE TRIGGER  TrigRecords 
    AFTER INSERT ON Competitions 
    FOR EACH ROW
    WHEN(NEW.RECORD = 'WR' or NEW.RECORD = 'OR'  or NEW.RECORD = 'NR')
    BEGIN
        UPDATE sportsmen s Set  s.countofrecords = s.countofrecords + 1 where :new.fname = s.fname and :new.lname = s.lname; 
    END TrigRecords;
    /

------------------------------------------------------------------------------------------------B------------------------------------------------------------------------------------------------------------------------------------------------


DECLARE 
    bch competitions.branch%type;
    sna competitions.sname%type;
    CURSOR myCursor(sna VARCHAR2, bch VARCHAR2) IS
                    SELECT  c.fname, c.lname, c.gender, c.takesplace, c.rank, c.record
                    FROM competitions c
                    WHERE c.sname = sna and c.branch = bch;
     some_row  myCursor%ROWTYPE;
                    
BEGIN
    sna := '&SNAME';
    bch := '&BRANCH';
    dbms_output.put_line('This Report for ' || sna ||' ' || bch || ':');
    open myCursor(sna,bch);
    LOOP
        FETCH myCursor INTO some_row;
        EXIT WHEN myCursor%NOTFOUND;
        DBMS_OUTPUT.put_line(' ');
        dbms_output.put(some_row.fname);
        dbms_output.put(' | ');
        dbms_output.put(some_row.lname);
        dbms_output.put(' | ');
        dbms_output.put(some_row.gender);
        dbms_output.put(' | ');
        dbms_output.put(some_row.takesplace);
        dbms_output.put(' | ');
        dbms_output.put(some_row.rank);
        dbms_output.put(' | ');
        dbms_output.put(some_row.record);
    END LOOP;
    close myCursor;
END;
    /
------------------------------------------------------------------------------------------------C------------------------------------------------------------------------------------------------------------------------------------------------

DECLARE 
    name_country sportsmen.country%type;
    count_country NUMBER;
    num1 NUMBER;
    INVALID_STATUS exception;
BEGIN
     name_country := '&COUNTRY';
    Select count(s.country) into count_country
    from Sportsmen s
    where s.country = name_country;
    IF (count_country > 0) THEN
        num1 := CountRanks(name_country);
        DBMS_OUTPUT.PUT_LINE(name_country || ' | ' || num1);
    ELSE 
        RAISE INVALID_STATUS;
    END IF;
    EXCEPTION
    WHEN INVALID_STATUS THEN
         DBMS_OUTPUT.PUT_LINE(name_country || ' COUNTRY NOT EXSITS!');
END;
/

CREATE OR REPLACE FUNCTION CountRanks(name_country VARCHAR2) RETURN NUMBER IS
    countRank NUMBER;
    country_rank competitions%rowtype;
    Cursor myCursor(cty VARCHAR2) IS 
                select DISTINCT s.country, c.rank
                from sportsmen s, competitions c
                where s.country = cty and s.fname = c.fname and s.lname = c.lname; 
BEGIN 
    countRank := 0;
    for eh IN myCursor(name_country)
    loop
        if eh.rank >= 1 and eh.rank <= 10 then
            countRank := countRank + 1;
        end if;
    end loop;
    return countRank;
END CountRanks;



------------------------------------------------------------------------------------------------D------------------------------------------------------------------------------------------------------------------------------------------------
BEGIN
 ViewToday('01/09/2021 12:00');
END;
/


CREATE OR REPLACE PROCEDURE ViewToday( d1 IN DATE) AS
  Cursor myCursor(d1 DATE) IS
                SELECT c.sname, c.branch, c.gender, c.record
                FROM Competitions c
                where c.takesplace = d1 and (c.record = 'WR' OR c.record = 'OR');
  
BEGIN 
  FOR ech IN myCursor(d1)
  LOOP
    DBMS_OUTPUT.put_line(ech.sname || ' | ' || ech.branch || ' | ' || ech.gender || ' | ' || ech.record );
  END LOOP;
END ViewToday;
/
