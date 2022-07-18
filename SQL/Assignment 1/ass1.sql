--315369967 RONI_JACK_VITULI
--204385413 BOAZ BITTON


------------------------------------a-------------------------------------------
select country, rank, count(country) 
from sportsmen s, competitions c
where s.fname = c.fname and s.lname = c.lname
GROUP BY country, rank;

------------------------------------b-------------------------------------------
select t1.fname,t1.lname,t1.age 
from 
                (select s.fname,s.lname,s.age,c.sname
                from (select fname,lname,age from sportsmen ) s, competitions c 
                where s.fname=c.fname and s.lname=c.lname) t1
group by( t1.fname,t1.lname,t1.age)
having count (t1.sname)>1;

------------------------------------c-------------------------------------------
select DISTINCT s.fname, s.lname,s.age
from sportsmen s, competitions c
where c.fname = s.fname and s.lname = c.lname and c.rank =
ANY ( select MIN(c1.rank)
            from sportsmen s1, competitions c1
           where s1.fname = c1.fname and s1.lname = c1.lname and s.country = s1.country);
            
------------------------------------d-------------------------------------------
select * from competitions;
select sname, branch
from competitions c
where c.record = 'OR' and NOT EXISTS( select sname, branch
                                    from  competitions c2
                                    where c2.sname = c.sname and c2.branch = c.branch and c2.record like 'WR');

--------------------------------------e-----------------------------------------
select s.sname,s.branch,avg(age)
from (
select s.age,c1.sname,c1.branch
from (select fname,lname,age,country from sportsmen ) s, competitions c1
where s.fname=c1.fname and s.lname=c1.lname) s
group by s.sname,s.branch;

------------------------------------f-------------------------------------------
select * from competitions;

select  s.sname 
from (select c1.sname,c1.branch ,s.country
            from (select fname,lname,age,country 
                        from sportsmen ) s, competitions c1
                        where s.fname=c1.fname and s.lname=c1.lname) s
group by s.sname
having count (DISTINCT s.country)<4;
