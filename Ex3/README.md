in this ex we was asked to design a program which detecet spam messages.
design:
one of the purposes of the ex was to practice iterators and templates.
therefore, we had to implement generic map.
there werent much design decisions because we got the api from the staff and had to imitate stl map.
in the begining, i chosed to save the table in vector of vectors of pairs.
i did it because yoni allow us to choose the bucket as vector<pair>. therefore, it mean that the memory
was not that an issue so i choose to implemt it as vetor of vectors.
after i finished the drill, i understand that is not allowed so i changed my table to array.
another problem i had was iterator. i didnt understand what was the problem but i tried to make the
iterator as class wrapper for vector iterator. it works fine but there were memory leaks in the the
vector.h (stl implemention ) and i didnt figure it out. therefore, i changed the iterator to count by number.
it is not efficient by due to time shortage and the upcomming test i had no time to solve the problem
all and all, cpp is a very important language but hard as hell so i will finish the last exercise readme
with Winston Churchill Quote:

"Now this is not the end. It is not even the beginning of the end. But it is, perhaps, the end of the beginning."

there were no runtime demands


