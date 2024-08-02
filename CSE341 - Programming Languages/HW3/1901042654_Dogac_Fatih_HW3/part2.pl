flight(istanbul,izmir,2).
flight(istanbul,ankara,1).
flight(istanbul,rize,4).
flight(izmir,ankara,6).
flight(izmir,antalya,2).
flight(antalya,erzincan,3).
flight(antalya,diyarbakir,4).
flight(diyarbakir,ankara,8).
flight(ankara,van,4).
flight(ankara,rize,5).
flight(van,gaziantep,3).
flight(erzincan,canakkale,6).

route(X,Y,C) :- route1(X,Y,C,[]).

route1(X,Y,C,V) :-  ( flight(X,A,C1) ; flight(A,X,C1) ), % Arrows are bidirectional.
                    \+ member(A,V) ,                     % Already visited
                    ( Y = A, C is C1 ; route1(A,Y,C2,[X|V]) , C is C1+C2) , % Target (Y) is already reached or not yet.
                     nl , write(A + X + V).                                 % writing path (but reverse order )