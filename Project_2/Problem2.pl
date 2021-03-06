
%Problem 2

%Facts Given
occupation(joe,oral_surgeon).
occupation(sam,patent_laywer).
occupation(bill,trial_laywer).
occupation(cindy,investment_banker).
occupation(joan,civil_laywer).
occupation(len,plastic_surgeon).
occupation(lance,heart_surgeon).
occupation(frank,brain_surgeon).
occupation(charlie,plastic_surgeon).
occupation(lisa,oral_surgeon).

address(joe,houston).
address(sam,pittsburgh).
address(bill,dallas).
address(cindy,omaha).
address(joan,chicago).
address(len,college_station).
address(lance,los_angeles).
address(frank,dallas).
address(charlie,houston).
address(lisa,san_antonio).

salary(joe,50000).
salary(sam,150000).
salary(bill,200000).
salary(cindy,140000).
salary(joan,80000).
salary(len,70000).
salary(lance,650000).
salary(frank,85000).
salary(charlie,120000).
salary(lisa,190000).

%New Sity-State relations
state(houston,texas).
state(san_antonio,texas).
state(college_station, texas).
state(dallas,texas).

%Surgeon
doctorCat(oral_surgeon, surgeon).
doctorCat(heart_surgeon, surgeon).
doctorCat(plastic_surgeon, surgeon).
doctorCat(brain_surgeon, surgeon).

%Find all the surgeons who live in texas and make over$100,00/yr
%!Params are
% OC - occupation Catergory - surgeon
% S - State of residence (texas)
% A - Salary Amount( 100,000)
query(X,OC,S,A):-
    occupation(X,Y),doctorCat(Y,OC),
    address(X,Add),state(Add,S),
    salary(X,Sal),Sal>A.



