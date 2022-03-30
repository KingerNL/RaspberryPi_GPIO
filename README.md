# Hva_Raspberry

This is a little project in did where i show you how to connect hardware to your Raspberry Pi with the help of a library called: Bcm2835,
i used this library over some more high level ones like WiringPi because you just loose track of what the hell your doing. It's like programming on an Arduino, 
not that you can't use the library for my application. Also i acknowledge the fact that this code isn't optimally made. It never my intention to make this high
end software that would be used by billions. It's for a niche group of people wondering how to use the GPIO pins on your Raspberry without changing the C++ language to much.
That said, this can easily be written in C, with a couple of changes. For instance the Threating library is c++ only, you can use the pthreads library for that.

All the comments are in Dutch, sorry if you thought it would be an easy read. Don't know if i said this already, but all the Library's u need can be found in the **windows.hpp** folder. It's in the comments of main too, you can find there every command you need to run too. I used an Imager for all the correct settings. So if you want that one, just msg me. Ohh, you made it trough the end eh? here are the correct GPIO pins corresponding with the bcm2835 library pins as your reward (it's also in the **hardware.hpp** file):

![image](https://user-images.githubusercontent.com/67836542/160856202-260872f1-c30e-4220-9019-f7e6564b865d.png)


___

At last i want to creddit some people in helping me with the code, maybe i look smart but I couldn't have done this without some people, so here it goes:

- [Casual Coder](https://www.youtube.com/channel/UCwA85g9HuIgg0SSjX59p0YQ) For learning more about ncurses, he has a great video on building snake into your terminal.
- [The Cherno](https://www.youtube.com/c/TheChernoProject) For learning more about the basic concepts of c++, great channel to learn more about C++.
- [Saldina Nurak](https://www.youtube.com/channel/UCl5-BV9aRaeDVohpE4sqJiQ) Also for basic concepts on c++, easy to follow and has great video's on threats, basic file structures and more.
- Edwin Boer. He is my teacher and helped me a ton with basic understanding of c++ & general computer logic. Can't thank him enough.
