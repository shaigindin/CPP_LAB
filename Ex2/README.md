cpp_ex2
shai.gindin
301315537
######
in this ex we was asked to design a program which prints fractal by order.
design:
i think one of the purposes of the ex was to practice inheritance and polymorphism.
therefore, it only makes sens to make Fractal an abstract class cause there is no
General Fractal. i think it was a bad design decision to put all the classes (Dust, carpet and
Sieve) inside Fractal however we were told to do so. Therefore, i decided , for educational
purposes, to "hide" the code as we learned in class. i used static function factory that
creates the objects(the difference fractals). i believe a better practice was to make them public
and directly creates them but it was a good practice. another "bad" decision was to use array which
i allocated memory in the heap. dealing with memory in c++ is gives you a headache and i easily
could work with vector instead however i believe it is a good practice to learn work with memory.
in ordered to saves code, i tried to implements most of the code in Fractal.
because fractal had the array pointer (which stored in the heap) all the memory management is there.

there were no runtime demands

