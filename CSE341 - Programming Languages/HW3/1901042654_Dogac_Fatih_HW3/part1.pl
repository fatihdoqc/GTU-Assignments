%
%       Fatih Doğaç 
%

:-dynamic(student/3).
:-dynamic(room/3).
:-dynamic(course/7).


% room(id , capacity , [8,9,10,11,12,13,14,15,16] open hours, equipment)

room(z23 , 15 , [projector , hcapped]).
room(z06 , 10 , [hcapped]).
room(z10 , 10 , [projector]).
room(z04 , 5 , []).

% course(id , instructor , capacity , [class hours] , room_id , number of student , [special needs of equipment])

course(cse341 , genc , 10 , [8,9,10,11] , z23 , 8 , [projector]).
course(cse343 , kalkan , 5 , [12,13] , z10 , 4 , [projector , hcapped]).
course(cse321 , gozupek , 6 , [10,11] , z10 , 5 , [hcapped]).
course(cse331 , bayrakci , 10 , [14,15,16] , z06 , 8 , []).

% instructor( id , courses taught by this instructor , [preferences] )

instructor(genc , [cse341] , [projector]).
instructor(kalkan , [cse343] , [projector , hcapped]).
instructor(gozupek , [cse321] , [hcapped]).
instructor(bayrakci , [cse331] , []).

% student( id , courses taken , handicapped info)

student(1,[cse341,cse343,cse331],_).
student(2,[cse341,cse343],_).
student(3,[cse341,cse331],hcapped).
student(4,[cse341],_).
student(5,[cse331],_).
student(6,[cse321,cse343,cse331],hcapped).
student(7,[cse321,cse343],_).
student(8,[cse341],hcapped).
student(9,[cse341],_).
student(10,[cse341],_).
student(11,[cse341],_).
student(12,[cse343,cse321,cse341,cse331],hcapped).
student(13,[cse343,cse321],_).
student(14,[cse343,cse321],_).
student(15,[cse343,cse321],hcapped).


% simplicating the occupancy informations of rooms
% occupancy( course id , room , [hours]).

occupancy(cse341 , z23 , [8,9,10,11]).
occupancy(cse343 , z23 , [12,13,14]).
occupancy(cse321 , z10 , [10,11]).
occupancy(cse331 , z06 , [14,15,16]).


% >>>>>>>>>>>>>>>>>>>>>>RULES

addStudent(ID , CourseList , HCAP) :- assertz(student(ID , CourseList , HCAP)).
addRoom(ID , CAP , EQ) :- assertz(room(ID , CAP , EQ)).
addCourse(ID , INSTR , CAP , HOURS , ROOM_ID , NUMOFSTUDENT,EQ) :- assertz(course(ID , INSTR , CAP , HOURS , ROOM_ID , NUMOFSTUDENT,EQ)).

% Finds out if there are at least one number in L1 exist in L2 too. 
match_list(L1,L2) :- member(X,L1) , member(X,L2);
                     L1 = []; L2 = [].


% conflict(course id_1 , course id_2 ).

conflict(A,B) :- occupancy(A , _ , H1) , occupancy(B , _ , H2) , match_list(H1,H2).


% assign(course_id , room_id ) checks if assigning a room to a course is possible

assign(C , R ) :-   course( C , _ , CAPC , _ , _ , _ , EQC ) , % course capacity and equipment infos
                    room(   R , CAPR , EQR),                   % room capacity and equipment infos
                    CAPR >= CAPC,                              % checking if the capacity enough
                    match_list(EQR , EQC) .                    % checking if the equipments exists in the room.


% Enroll a student to a course.

enrollStudent( ST , COURSE) :-  student( ST , CourseList , HCap),
                                course( COURSE , _ , CAP , _ , _ , CURR , EQC),
                                \+ checkAllConflicts(COURSE , CourseList),
                                ( HCap = hcapped -> member(hcapped , EQC) ), 
                                    % If the course is for handicapped then no need to check if the room is, 
                                    % because course will be checked in assign/2 part.
                                CURR < CAP.


% checks if a course conflicts with another course of a student.
checkAllConflicts(COURSE , [HEAD | TAIL]) :- conflict(COURSE , HEAD) ; checkAllConflicts(COURSE , TAIL).